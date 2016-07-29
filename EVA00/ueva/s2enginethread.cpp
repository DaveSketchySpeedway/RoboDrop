/*
Copyright 2016 David Wong

This file is part of uEVA. https://github.com/DaveSketchySpeedway/uEVA

uEVA is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

uEVA is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with uEva. If not, see <http://www.gnu.org/licenses/>
*/

#include "s2enginethread.h"

S2EngineThread::S2EngineThread(QObject *parent)
	: QThread(parent)
{
	mutex.lock();
	idle = true;
	mutex.unlock();
}

S2EngineThread::~S2EngineThread()
{
	mutex.lock();

	mutex.unlock();
}

//// THREAD OPERATIONS

void S2EngineThread::setSettings(const UevaSettings &s)
{
	mutex.lock();
	settings = s;
	mutex.unlock();
}

void S2EngineThread::setData(const UevaData &d)
{
	mutex.lock();
	data = d;
	mutex.unlock();
}

void S2EngineThread::wake()
{
	mutex.lock();
	idle = false;
	mutex.unlock();
}

//// SINGLE TIME
void S2EngineThread::setCalib(double micronLength)
{
	mutex.lock();

	if (!settings.mouseLines.empty())
	{
		QLine mouseLine = settings.mouseLines[0];
		double pixelLength = std::sqrt(
			std::pow((double)mouseLine.dx(), 2.0) + std::pow((double)mouseLine.dy(), 2.0));
		micronPerPixel = micronLength / pixelLength;
		qDebug() << "micronPerPixel = " << micronPerPixel << endl;
	}

	mutex.unlock();
}

void S2EngineThread::setBkgd()
{
	mutex.lock();

	bkgd = data.rawGray.clone();
	qDebug() << "New Background" << endl;

	mutex.unlock();
}

void S2EngineThread::separateChannels(int &numChan)
{
	CV_Assert(!allChannels.empty());
	channelContours.clear();
	channels.clear();
	// find all channel contours
	cv::findContours(allChannels, channelContours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	numChan = channelContours.size();
	// seprate into vector of UevaChannel
	for (int i = 0; i < numChan; i++)
	{
		UevaChannel channel;
		channel.index = i;
		channel.mask = contour2Mask(channelContours[i], allChannels.size());
		channels.push_back(channel);
	}
}

void S2EngineThread::sortChannels(std::map<std::string, std::vector<int> > &channelInfo)
{
	CV_Assert(channelInfo["newIndices"].size() == channels.size());
	// fill info
	for (int i = 0; i < channels.size(); i++)
	{
		channels[i].index = channelInfo["newIndices"][i];
		channels[i].direction = channelInfo["directions"][i];
	}
	// sort
	std::sort(channels.begin(), channels.end(),
		[](const UevaChannel &a, const UevaChannel &b)
	{
		return a.index < b.index;
	});
	// update channel contours after sort
	channelContours.clear();
	for (int i = 0; i < channels.size(); i++)
	{
		channelContours.push_back(mask2Contour(channels[i].mask));
	}
}

void S2EngineThread::loadCtrl(std::string fileName,
	int *numState, int *numIn, int *numOut, int *numCtrl, double *ctrlTs)
{
	mutex.lock();

	ctrls.clear();
	cv::FileStorage fs(fileName, cv::FileStorage::READ);
	*numCtrl = (int)fs["numCtrl"];
	*ctrlTs = (double)fs["samplePeriod"];
	*numState = (int)fs["numPlantState"];
	*numIn = (int)fs["numPlantInput"];
	*numOut = (int)fs["numPlantOutput"];
	UevaCtrl::samplePeriod = (double)fs["samplePeriod"];
	UevaCtrl::numPlantState = (int)fs["numPlantState"];
	UevaCtrl::numPlantInput = (int)fs["numPlantInput"];
	UevaCtrl::numPlantOutput = (int)fs["numPlantOutput"];

	for (int i = 0; i < *numCtrl; i++)
	{
		std::string ctrlName = "ctrl" + std::to_string(i);
		cv::FileNode c = fs[ctrlName];
		UevaCtrl ctrl;

		ctrl.uncoUnob = (int)c["uncoUnob"];
		c["outputIdx"] >> ctrl.outputIndices;
		c["stateIdx"] >> ctrl.stateIndices;
		c["A"] >> ctrl.A;
		c["B"] >> ctrl.B;
		c["C"] >> ctrl.C;
		c["D"] >> ctrl.D;
		c["K1"] >> ctrl.K1;
		c["K2"] >> ctrl.K2;
		c["H"] >> ctrl.H;

		ctrls.push_back(ctrl);

		std::cerr << "controller " << ctrlName << std::endl;
		std::cerr << "unco unob " << ctrl.uncoUnob << std::endl;
		std::cerr << "output index " << ctrl.outputIndices << std::endl;
		std::cerr << "state index " << ctrl.stateIndices << std::endl;
		//std::cerr << "A " << ctrl.A << std::endl;
		//std::cerr << "B " << ctrl.B << std::endl;
		//std::cerr << "C " << ctrl.C << std::endl;
		//std::cerr << "D " << ctrl.D << std::endl;
		//std::cerr << "K1 " << ctrl.K1 << std::endl;
		//std::cerr << "K2 " << ctrl.K2 << std::endl;
		//std::cerr << "H " << ctrl.H << std::endl;
		std::cerr << std::endl;
	}
	fs.release();

	mutex.unlock();
}

void S2EngineThread::initCtrl()
{
	estimates = QVector<qreal>(UevaCtrl::numPlantOutput, 0.0);
	measures = QVector<qreal>(UevaCtrl::numPlantOutput, 0.0);
	references = QVector<qreal>(UevaCtrl::numPlantOutput, 0.0);
	states = QVector<qreal>(UevaCtrl::numPlantState, 0.0);
	integralStates = QVector<qreal>(UevaCtrl::numPlantOutput, 0.0);
	commands = QVector<qreal>(UevaCtrl::numPlantInput, 0.0);
	measureOffsets = QVector<qreal>(UevaCtrl::numPlantOutput, 0.0);
	referenceOffsets = QVector<qreal>(UevaCtrl::numPlantOutput, 0.0);
	// open to close loop transition
	for (int i = 0; i < commands.size(); i++)
	{
		commands[i] = double(settings.inletRequests[i]);
	}
}

void S2EngineThread::resetCtrl()
{
	activatedChannels.clear();

	estimates.clear();
	measures.clear();
	references.clear();
	states.clear();
	integralStates.clear();
	commands.clear();
	measureOffsets.clear();
	referenceOffsets.clear();
}



//// CONTINUOUS
void S2EngineThread::run()
{
	forever
	{
		if (!idle)
		{
			mutex.lock();
			//QTime entrance = QTime::currentTime();
			data.map["inletWrite"] = settings.inletRequests;

			//// MASK MAKING
			if (settings.flag & UevaSettings::MASK_MAKING)
			{
				CV_Assert(!bkgd.empty());
				// detect walls with adaptive threshold (most time consuming)
				cv::adaptiveThreshold(bkgd, dropletMask,
					HIGH_VALUE,
					cv::ADAPTIVE_THRESH_GAUSSIAN_C,
					cv::THRESH_BINARY_INV,
					settings.maskBlockSize,
					settings.maskThreshold); 
				// flood base on user seed point
				if ((settings.mouseLines[0].x1() >= 0) &&
					(settings.mouseLines[0].x1() < dropletMask.cols) &&
					(settings.mouseLines[0].y1() >= 0) &&
					(settings.mouseLines[0].y1() < dropletMask.rows))
				{
					seed.x = settings.mouseLines[0].x1();
					seed.y = settings.mouseLines[0].y1();
				}
				floodFillReturn = cv::floodFill(dropletMask, seed, MID_VALUE);
				// eliminate noise and wall by morphological opening (second most time consuming)
				//morphologyEx(dropletMask, dropletMask, cv::MORPH_OPEN, structuringElement);
				structuringElement = cv::getStructuringElement(cv::MORPH_RECT,
					cv::Size_<int>(settings.maskOpenSize + 3, settings.maskOpenSize + 3));
				cv::erode(dropletMask, dropletMask, structuringElement);
				structuringElement = cv::getStructuringElement(cv::MORPH_RECT,
					cv::Size_<int>(settings.maskOpenSize, settings.maskOpenSize));
				cv::dilate(dropletMask, dropletMask, structuringElement);
				// draw
				cv::cvtColor(dropletMask, data.drawnBgr, CV_GRAY2BGR);
				cv::cvtColor(data.drawnBgr, data.drawnRgb, CV_BGR2RGB);
			}
			
			//// CHANNEL CUTTING
			else if (settings.flag & UevaSettings::CHANNEL_CUTTING)
			{
				CV_Assert(!dropletMask.empty());
				// further erode to get thinner mask
				structuringElement = cv::getStructuringElement(cv::MORPH_RECT,
					cv::Size_<int>(settings.channelErodeSize, settings.channelErodeSize));
				cv::erode(dropletMask, markerMask, structuringElement);
				// cut into channels
				allChannels = markerMask.clone();
				for (int i = 1; i < settings.mouseLines.size(); i++)
				{
					cv::Point_<int> pt1 = cv::Point_<int>(
						settings.mouseLines[i].x1(),
						settings.mouseLines[i].y1());
					cv::Point_<int> pt2 = cv::Point_<int>(
						settings.mouseLines[i].x2(),
						settings.mouseLines[i].y2());
					cv::line(allChannels, pt1, pt2, cv::Scalar(0), settings.channelCutThickness);
				}
				// draw
				cv::Mat drawn;
				cv::add(dropletMask, allChannels, drawn);
				cv::cvtColor(drawn, data.drawnBgr, CV_GRAY2BGR);
				cv::cvtColor(data.drawnBgr, data.drawnRgb, CV_BGR2RGB);
			}
			else
			{	
				//// IMGPROC
				if (settings.flag & UevaSettings::IMGPROC_ON)
				{
					CV_Assert(!bkgd.empty());
					CV_Assert(!dropletMask.empty());
					CV_Assert(!markerMask.empty());
					// background subtraction to get markers (droplets edges)
					cv::absdiff(data.rawGray, bkgd, allMarkers);
					cv::threshold(allMarkers, allMarkers,
						settings.imgprogThreshold,
						HIGH_VALUE,
						cv::THRESH_BINARY);
					// flood and complement to get droplets (droplets internal)
					allDroplets = allMarkers.clone();
					seed = cv::Point(0, 0);
					floodFillReturn = cv::floodFill(allDroplets,
						seed,
						HIGH_VALUE,
						0, cv::Scalar_<int>(0), cv::Scalar_<int>(0),
						cv::FLOODFILL_FIXED_RANGE);
					allDroplets = HIGH_VALUE - allDroplets;
					// combine edges and internals to get whole droplets 
					cv::bitwise_or(allMarkers, allDroplets, allDroplets);
					// Exclude noise with masks
					cv::bitwise_and(allMarkers, markerMask, allMarkers);
					cv::bitwise_and(allDroplets, dropletMask, allDroplets);
					// polish droplets with erosion
					structuringElement = cv::getStructuringElement(cv::MORPH_RECT,
						cv::Size_<int>(settings.imgprogErodeSize, settings.imgprogErodeSize));
					cv::erode(allDroplets, allDroplets, structuringElement);
					// find countours
					dropletContours.clear();
					markerContours.clear();
					cv::findContours(allMarkers, markerContours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
					cv::findContours(allDroplets, dropletContours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
					//cv::findContours(allDroplets, dropletContours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
					// filter contours base on size	
					bigPassFilter(markerContours, settings.imgprogContourSize);
					bigPassFilter(dropletContours, settings.imgprogContourSize);
					// controller preparation
					for (int i = 0; i < channels.size(); i++)
					{
						channels[i].previousMarkerIndices.clear();
						channels[i].previousMarkerIndices = channels[i].currentMarkerIndices;
						channels[i].currentMarkerIndices.clear();
					}
					needInactivateAll = false;
					needReset = false;
					desiredChannels.clear();
					vacancy = settings.ctrlAutoCatch - activatedChannels.size();
					mousePressLeft.x = settings.leftPressPosition.x();
					mousePressLeft.y = settings.leftPressPosition.y();
					mousePressRight.x = settings.rightPressPosition.x();
					mousePressRight.y = settings.rightPressPosition.y();
					mousePressPrevious.x = settings.leftPressMovement.x1();
					mousePressPrevious.y = settings.leftPressMovement.y1();
					mousePressCurrent.x = settings.leftPressMovement.x2();
					mousePressCurrent.y = settings.leftPressMovement.y2();
					mousePressDisplacement = mousePressCurrent - mousePressPrevious;
					haveDirectReference = false;
					dr = 0;
					// vector of marker
					markers.clear();
					UevaMarker::imageSize = allMarkers.size();
					UevaMarker::sortRatio = settings.imgprogSortRatio;
					for (int i = 0; i < markerContours.size(); i++)
					{
						mom = cv::moments(markerContours[i]);
						UevaMarker marker;
						marker.type = 0;
						marker.centroid.x = mom.m10 / mom.m00;
						marker.centroid.y = mom.m01 / mom.m00;
						marker.rect = cv::Rect_<int>(
							marker.centroid.x - settings.ctrlMarkerSize / 2,
							marker.centroid.y - settings.ctrlMarkerSize / 2,
							settings.ctrlMarkerSize,
							settings.ctrlMarkerSize);
						markers.push_back(marker);
					}
					// sort markers to fake continuity
					std::sort(markers.begin(), markers.end(),
						[](const UevaMarker &a, const UevaMarker &b)
					{
						double sizeOfA =
							(double)a.centroid.x / (double)a.imageSize.width * (double)a.sortRatio +
							(double)a.centroid.y / (double)a.imageSize.height;
						double sizeOfB =
							(double)b.centroid.x / (double)b.imageSize.width * (double)b.sortRatio +
							(double)b.centroid.y / (double)b.imageSize.height;
						return sizeOfA < sizeOfB;
					});
					// link markers with channels after sort
					for (int i = 0; i < markers.size(); i++)
					{
						for (int j = 0; j < channels.size(); j++)
						{
							if (isPointInMask(markers[i].centroid, channels[j].mask))
							{
								markers[i].accomodatingChannelIndex = j;
								channels[j].currentMarkerIndices.push_back(i);
							}
						}
					}
					// vector of droplet
					droplets.clear();
					for (int i = 0; i < dropletContours.size(); i++)
					{
						UevaDroplet droplet;
						droplet.mask = contour2Mask(dropletContours[i], allDroplets.size());
						int maxOverlap = 0;
						for (int j = 0; j < channels.size(); j++)
						{
							int overlap = masksOverlap(droplet.mask, channels[j].mask);
							if (overlap > maxOverlap)
							{
								maxOverlap = overlap;
								droplet.accomodatingChannelIndex = j;
							}
						}
						// make marker if neck is detected
						droplet.kinkIndex = detectKink(dropletContours[i], settings.imgprocConvexSize);
						if (droplet.kinkIndex >= 0)
						{
							float neck;
							droplet.neckIndex = detectNeck(dropletContours[i], droplet.kinkIndex, neck,
								settings.imgprocPersistence);
							if (droplet.neckIndex >= 0)
							{
								UevaMarker marker;
								marker.type = 1;
								marker.value = (double)neck;
								mom = moments(dropletContours[i]);
								marker.centroid.x = mom.m10 / mom.m00;
								marker.centroid.y = mom.m01 / mom.m00;
								marker.rect = cv::Rect_<int>(
									marker.centroid.x - settings.ctrlMarkerSize / 2,
									marker.centroid.y - settings.ctrlMarkerSize / 2,
									settings.ctrlMarkerSize,
									settings.ctrlMarkerSize);
								if (droplet.accomodatingChannelIndex != -1)
								{
									marker.accomodatingChannelIndex = droplet.accomodatingChannelIndex;
									channels[marker.accomodatingChannelIndex].currentMarkerIndices.push_back(markers.size());
								}
								markers.push_back(marker);
							}
						}
						droplets.push_back(droplet);
					}
					if (UevaDroplet::fileStream.is_open())
					{
						UevaDroplet::fileStream << std::endl;
					}
					// user change marker
					for (int i = 0; i < channels.size(); i++)
					{
						for (int j = 0; j < channels[i].currentMarkerIndices.size(); j++)
						{
							if (mousePressLeft.inside(
								markers[channels[i].currentMarkerIndices[j]].rect))
							{
								// user try to select different marker in already active channel
								if (channels[i].selectedMarkerIndex != -1)
								{
									//cerr << "ch " << i << " select " << channels[i].selectedMarkerIndex << endl;////
									channels[i].selectedMarkerIndex = channels[i].currentMarkerIndices[j];
									needReset = 1;
								}
								// user try to select marker in inactive channel
								else
								{
									desiredChannels = activatedChannels;
									desiredChannels.push_back(i);
									if (isCombinationPossible(desiredChannels, ctrls))
									{
										//cerr << "ch " << i << " select " << channels[i].selectedMarkerIndex << endl;////
										activatedChannels = desiredChannels;
										channels[i].selectedMarkerIndex = channels[i].currentMarkerIndices[j];
										needReset = 1;
										vacancy--;
									}
								}
							}
							// user release marker
							if (mousePressRight.inside(
								markers[channels[i].currentMarkerIndices[j]].rect))
							{
								if (channels[i].selectedMarkerIndex == channels[i].currentMarkerIndices[j])
								{
									//cerr << "ch " << i << " release " << channels[i].selectedMarkerIndex << endl;////
									channels[i].selectedMarkerIndex = -1;
									deleteFromCombination(activatedChannels, i);
									needReset = 1;
									vacancy++;
								}
							}
						}
					}
					// inactivate all channels when marker appear or diappear due to flow
					for (int i = 0; i < channels.size(); i++)
					{
						if (channels[i].currentMarkerIndices != channels[i].previousMarkerIndices)
						{
							needInactivateAll = true;
						}
					}
					if (needInactivateAll)
					{
						for (int i = 0; i < channels.size(); i++)
						{
							if (channels[i].selectedMarkerIndex != -1)
							{
								//cerr << "ch " << i << " release " << channels[i].selectedMarkerIndex << endl;
								channels[i].selectedMarkerIndex = -1;
								deleteFromCombination(activatedChannels, i);
							}
						}
						needReset = 1;
						vacancy = settings.ctrlAutoCatch;
					}
					// auto catch marker
					for (int i = 0; i < channels.size(); i++)
					{
						if (vacancy > 0 &&
							channels[i].selectedMarkerIndex == -1 &&
							channels[i].currentMarkerIndices.size() > 0)
						{
							desiredChannels = activatedChannels;
							desiredChannels.push_back(i);
							if (isCombinationPossible(desiredChannels, ctrls))
							{
								//cerr << "ch " << i << " select " << channels[i].selectedMarkerIndex << endl;
								activatedChannels = desiredChannels;
								channels[i].selectedMarkerIndex = channels[i].currentMarkerIndices[0];
								needReset = 1;
								vacancy--;
							}
						}
					}
				}
				//// CTRL
				if (settings.flag & UevaSettings::CTRL_ON)
				{
					if (activatedChannels.size() > 0)
					{
						x = cv::Mat(ctrls[UevaCtrl::index].stateIndices.rows, 1, CV_64FC1, cv::Scalar(0.0));
						z = cv::Mat(ctrls[UevaCtrl::index].outputIndices.rows, 1, CV_64FC1, cv::Scalar(0.0));
						u = cv::Mat(UevaCtrl::numPlantInput, 1, CV_64FC1, cv::Scalar(0.0));
						y_est = cv::Mat(ctrls[UevaCtrl::index].outputIndices.rows, 1, CV_64FC1, cv::Scalar(0.0));
						y = cv::Mat(ctrls[UevaCtrl::index].outputIndices.rows, 1, CV_64FC1, cv::Scalar(0.0));
						r = cv::Mat(ctrls[UevaCtrl::index].outputIndices.rows, 1, CV_64FC1, cv::Scalar(0.0));
						x_new = cv::Mat(ctrls[UevaCtrl::index].stateIndices.rows, 1, CV_64FC1, cv::Scalar(0.0));
						z_new = cv::Mat(ctrls[UevaCtrl::index].outputIndices.rows, 1, CV_64FC1, cv::Scalar(0.0));
						u_new = cv::Mat(UevaCtrl::numPlantInput, 1, CV_64FC1, cv::Scalar(0.0));
						// check in
						if (!needReset)
						{
							for (int i = 0; i < ctrls[UevaCtrl::index].stateIndices.rows; i++)
							{
								x.at<double>(i) = states[ctrls[UevaCtrl::index].stateIndices.at<uchar>(i)];
							}
							for (int i = 0; i < ctrls[UevaCtrl::index].outputIndices.rows; i++)
							{
								r.at<double>(i) = references[ctrls[UevaCtrl::index].outputIndices.at<uchar>(i)];
							}
						}
						for (int i = 0; i < ctrls[UevaCtrl::index].outputIndices.rows; i++)
						{
							z.at<double>(i) = integralStates[ctrls[UevaCtrl::index].outputIndices.at<uchar>(i)];
						}
						for (int i = 0; i < UevaCtrl::numPlantInput; i++)
						{
							u.at<double>(i) = commands[i];
						}
						// estimate output
						y_est = ctrls[UevaCtrl::index].C * x + ctrls[UevaCtrl::index].D * u;
						// direct reference
						for (int i = 0; i < activatedChannels.size(); i++)
						{
							UevaChannel channel = channels[activatedChannels[i]];
							UevaMarker marker = markers[channel.selectedMarkerIndex];
							if (mousePressPrevious.inside(marker.rect) && mousePressCurrent.inside(marker.rect))
							{
								haveDirectReference = true;
								dr = scaleInterface(mousePressDisplacement, channel.direction, micronPerPixel);
								r.at<double>(i) += dr;
							}
						}
						// linked reference
						if (haveDirectReference)
						{
							for (int i = 0; i < activatedChannels.size(); i++)
							{
								if (settings.linkChannels[activatedChannels[i]])
								{
									if (settings.inverseLinkChannels[activatedChannels[i]])
									{
										r.at<double>(i) += dr;
									}
									else
									{
										r.at<double>(i) -= dr;
									}
								}
							}
						}
						// measurement
						for (int i = 0; i < activatedChannels.size(); i++)
						{
							UevaChannel channel = channels[activatedChannels[i]];
							UevaMarker marker = markers[channel.selectedMarkerIndex];
							if (marker.type == 1) // neck
							{
								
							}
							else // interface
							{
								y.at<double>(i) = scaleInterface(marker.centroid, channel.direction, micronPerPixel);
							}
							if (needReset)
							{
								measureOffsets[activatedChannels[i]] = y.at<double>(i);
							}
							y.at<double>(i) -= measureOffsets[activatedChannels[i]];
						}
						// estimate states
						x_new = ctrls[UevaCtrl::index].A * x +
							ctrls[UevaCtrl::index].B * u +
							ctrls[UevaCtrl::index].H * (y - y_est);
						z_new = z + UevaCtrl::samplePeriod * (y - r);
						// calculate command
						u_new -= ctrls[UevaCtrl::index].K1 * x_new + ctrls[UevaCtrl::index].K2 * z_new;
						// check out
						for (int i = 0; i < ctrls[UevaCtrl::index].outputIndices.rows; i++)
						{
							uchar outputIndex = ctrls[UevaCtrl::index].outputIndices.at<uchar>(i);
							estimates[outputIndex] = y_est.at<double>(i);
							measures[outputIndex] = y.at<double>(i);
							references[outputIndex] = r.at<double>(i);
							integralStates[outputIndex] = z_new.at<double>(i);
						}
						for (int i = 0; i < ctrls[UevaCtrl::index].stateIndices.rows; i++)
						{
							uchar stateIndex = ctrls[UevaCtrl::index].stateIndices.at<uchar>(i);
							states[stateIndex] = x_new.at<double>(i);
						}
						for (int i = 0; i < UevaCtrl::numPlantInput; i++)
						{
							commands[i] = u_new.at<double>(i);
						}
						// data acquisition
						data.map["ctrlEstimate"] = estimates;
						data.map["ctrlMeasure"] = measures;
						data.map["ctrlReference"] = references;
						data.map["ctrlState"] = states;
						data.map["ctrlIntegraState"] = integralStates;
						data.map["ctrlCommand"] = commands;
						data.map["ctrlMeasureOffset"] = measureOffsets;
						data.map["ctrlReferenceOffset"] = referenceOffsets;
						// command pumps
						for (int i = 0; i < commands.size(); i++)
						{
							data.map["inletWrite"][i] += commands[i];
						}
						// debug
						std::cerr << " activated channels: ";
						for (int k = 0; k < activatedChannels.size(); k++)
							std::cerr << activatedChannels[k] << " ";
						std::cerr << std::endl;
						std::cerr << std::fixed << std::setprecision(5);
						std::cerr << "x     " << x.t() << std::endl;
						std::cerr << "z     " << z.t() << std::endl;
						std::cerr << "u     " << u.t() << std::endl;
						std::cerr << "y_est " << y_est.t() << std::endl;
						std::cerr << "y     " << y.t() << std::endl;
						std::cerr << "r     " << r.t() << std::endl;
						std::cerr << "x_new " << x_new.t() << std::endl;
						std::cerr << "z_new " << z_new.t() << std::endl;
						std::cerr << "u_new " << u_new.t() << std::endl;
						std::cerr << std::endl;
					}
				}

				//// DRAW
				if (!data.rawGray.empty())
				{
					cv::cvtColor(data.rawGray, data.drawnBgr, CV_GRAY2BGR);
					// draw channel contour
					if (settings.flag & UevaSettings::DRAW_CHANNEL)
					{
						lineColor = cv::Scalar(255, 255, 255); // white
						lineThickness = CV_FILLED; 
						lineType = 8;
						cv::drawContours(data.drawnBgr, channelContours, -1,
							lineColor, lineThickness, lineType);
					}
					// draw droplet contour
					if (settings.flag & UevaSettings::DRAW_DROPLET)
					{
						lineColor = cv::Scalar(255, 0, 255); // magenta
						lineThickness = 1;
						lineType = 8;
						cv::drawContours(data.drawnBgr, dropletContours, -1,
							lineColor, lineThickness, lineType);
					}
					// draw marker contour
					if (settings.flag & UevaSettings::DRAW_MARKER)
					{
						lineColor = cv::Scalar(255, 255, 0); // cyan
						lineThickness = 1;
						lineType = 8;
						cv::drawContours(data.drawnBgr, markerContours, -1,
							lineColor, lineThickness, lineType);
					}
					// draw kink and neck
					if (settings.flag & UevaSettings::DRAW_NECK)
					{
						lineColor = cv::Scalar(0, 255, 255); // yellow
						lineThickness = 3;
						lineType = 8;
						for (int i = 0; i < droplets.size(); i++)
						{
							if (droplets[i].kinkIndex >= 0 && droplets[i].neckIndex >= 0)
							{
								cv::line(data.drawnBgr,
									dropletContours[i][droplets[i].kinkIndex],
									dropletContours[i][droplets[i].neckIndex],
									lineColor, lineThickness, lineType);
								//cv::circle(data.drawnBgr,
								//	dropletContours[i][droplets[i].kinkIndex],
								//	10, lineColor, lineThickness, lineType);
							}
						}
					}
					// draw channel text
					for (int i = 0; i < channels.size(); i++)
					{
						std::string dir;
						switch (channels[i].direction)
						{
						case 0:
						{
							if (settings.inverseLinkChannels[i])
								dir = "(v)";
							else
								dir = "^";
							break;
						}
						case 1:
						{
							if (settings.inverseLinkChannels[i])
								dir = "(^)";
							else
								dir = "v";
							break;
						}
						case 2:
						{
							if (settings.inverseLinkChannels[i])
								dir = "(>)";
							else
								dir = "<";
							break;
						}
						case 3:
						{
							if (settings.inverseLinkChannels[i])
								dir = "(<)";
							else
								dir = ">";
							break;
						}
						}
						if (settings.linkChannels[i])
						{
							fontScale = 1;
							lineColor = cv::Scalar(0, 0, 255); // red
						}
						else
						{
							fontScale = 0.8;
							lineColor = cv::Scalar(255, 255, 255); // white
						}
						std::ostringstream oss;
						oss << "CH" << i << " " << dir;
						std::string str = oss.str();
						rect = cv::boundingRect(channelContours[i]);
						anchor.x = rect.x + 60; // offset right from leftmost
						mom = cv::moments(channelContours[i]);
						anchor.y = mom.m01 / mom.m00 - 30; // offset up from center
						lineThickness = 1;
						lineType = 8;
						cv::putText(data.drawnBgr, str, anchor,
							cv::FONT_HERSHEY_SIMPLEX, fontScale, lineColor, lineThickness, lineType);
						// draw occupying markers
						for (int j = 0; j < channels[i].currentMarkerIndices.size(); j++)
						{
							if (channels[i].currentMarkerIndices[j] == channels[i].selectedMarkerIndex)
							{
								lineColor = cv::Scalar(255, 0, 0); // blue if selected 
							}
							else if (markers[channels[i].currentMarkerIndices[j]].type == 1)
							{
								lineColor = cv::Scalar(0, 255, 255); // yellow if neck not selected
							}
							else
							{
								lineColor = cv::Scalar(255, 255, 0); // cyan if not selected
							}
							lineThickness = 1;
							lineType = 8;
							cv::rectangle(data.drawnBgr,
								markers[channels[i].currentMarkerIndices[j]].rect,
								lineColor, lineThickness, lineThickness);
						}
					}
					cv::cvtColor(data.drawnBgr, data.drawnRgb, CV_BGR2RGB);
				}
			}

			emit engineSignal(data);
			idle = true;
			//QTime exit = QTime::currentTime();
			//int ms = entrance.msecsTo(exit);
			//qDebug() << "engine used (ms)" << ms;
			mutex.unlock();
		}
	}
}

