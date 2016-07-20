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

void S2EngineThread::loadCtrl(string fileName,
	int *numState, int *numIn, int *numOut, int *numCtrl, double *ctrlTs)
{
	mutex.lock();

	FileStorage fs(fileName, FileStorage::READ);
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
		string ctrlName = "ctrl" + to_string(i);
		FileNode c = fs[ctrlName];
		UevaCtrl ctrl;

		ctrl.uncoUnob = (int)c["uncoUnob"];
		c["outputIdx"] >> ctrl.outputIdx;
		c["stateIdx"] >> ctrl.stateIdx;
		c["A"] >> ctrl.A;
		c["B"] >> ctrl.B;
		c["C"] >> ctrl.C;
		c["D"] >> ctrl.D;
		c["K1"] >> ctrl.K1;
		c["K2"] >> ctrl.K2;
		c["H"] >> ctrl.H;

		cerr << "controller " << ctrlName << endl;
		cerr << "unco unob " << ctrl.uncoUnob << endl;
		cerr << "output index " << ctrl.outputIdx << endl;
		cerr << "state index " << ctrl.stateIdx << endl;
		//cerr << "A " << ctrl.A << endl;
		//cerr << "B " << ctrl.B << endl;
		//cerr << "C " << ctrl.C << endl;
		//cerr << "D " << ctrl.D << endl;
		//cerr << "K1 " << ctrl.K1 << endl;
		//cerr << "K2 " << ctrl.K2 << endl;
		//cerr << "H " << ctrl.H << endl;
		cerr << endl;
	}
	fs.release();

	mutex.unlock();
}

void S2EngineThread::setCalib(double micronLength)
{
	mutex.lock();

	if (!settings.mouseLines.empty())
	{
		QLine mouseLine = settings.mouseLines[0];
		double pixelLength = sqrt(
			pow((double)mouseLine.dx(), 2.0) + pow((double)mouseLine.dy(), 2.0));
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
	// find all channel contours
	channels.clear();
	channelContours.clear();
	findContours(allChannels, channelContours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	numChan = channelContours.size();
	// seprate into vector of UevaChannel
	for (int i = 0; i < numChan; i++)
	{
		vector<vector< Point_<int> >> singleContourVector;
		singleContourVector.push_back(channelContours[i]);
		UevaChannel channel;
		channel.index = i;
		channel.mask = Mat(allChannels.rows, allChannels.cols, CV_8UC1, Scalar_<int>(0));
		drawContours(channel.mask, singleContourVector, -1, Scalar_<int>(255), -1);
		channels.push_back(channel);
	}
}

void S2EngineThread::sortChannels(map<string, vector<int> > &channelInfo)
{
	CV_Assert(channelInfo["newIndices"].size() == channels.size());
	// fill info
	for (int i = 0; i < channels.size(); i++)
	{
		channels[i].index = channelInfo["newIndices"][i];
		channels[i].direction = channelInfo["directions"][i];
	}
	// sort
	sort(channels.begin(), channels.end(),
		[](const UevaChannel &a, const UevaChannel &b)
	{
		return a.index < b.index;
	});
	// update channel contours 
	channelContours.clear();
	for (int i = 0; i < channels.size(); i++)
	{
		vector<vector< Point_<int> >> singleContourVector;
		findContours(channels[i].mask, singleContourVector, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
		channelContours.push_back(singleContourVector[0]);
	}
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

			//// DELETEME
			if (!settings.rightPressPosition.isNull())
			{
				qDebug() << "right clicked at x:" << settings.rightPressPosition.x() <<
					" y:" << settings.rightPressPosition.y();
			}
			if (!settings.leftPressPosition.isNull())
			{
				qDebug() << "left clicked at x:" << settings.leftPressPosition.x() <<
					" y:" << settings.leftPressPosition.y();
			}
			if (!settings.leftPressMovement.isNull())
			{
				qDebug() << "left pressed movement dx:" << settings.leftPressMovement.dx() <<
					" dy:" << settings.leftPressMovement.dy();
			}

			//// MASK MAKING
			if (settings.flag & UevaSettings::MASK_MAKING)
			{
				CV_Assert(!bkgd.empty());
				// detect walls with adaptive threshold (most time consuming)
				adaptiveThreshold(bkgd, dropletMask,
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
				floodFillReturn = floodFill(dropletMask, seed, MID_VALUE);
				// eliminate noise by morphological opening (second most time consuming)
				structuringElement = getStructuringElement(MORPH_RECT,
					Size_<int>(settings.maskOpenSize, settings.maskOpenSize));
				morphologyEx(dropletMask, dropletMask, cv::MORPH_OPEN, structuringElement);
				// draw
				cvtColor(dropletMask, data.drawnBgr, CV_GRAY2BGR);
				cvtColor(data.drawnBgr, data.drawnRgb, CV_BGR2RGB);
			}
			
			//// CHANNEL CUTTING
			else if (settings.flag & UevaSettings::CHANNEL_CUTTING)
			{
				CV_Assert(!dropletMask.empty());
				// further erode to get thinner mask
				structuringElement = getStructuringElement(MORPH_RECT,
					Size_<int>(settings.channelErodeSize, settings.channelErodeSize));
				erode(dropletMask, markerMask, structuringElement);
				// cut into channels
				allChannels = markerMask.clone();
				for (int i = 1; i < settings.mouseLines.size(); i++)
				{
					Point_<int> pt1 = Point_<int>(
						settings.mouseLines[i].x1(),
						settings.mouseLines[i].y1());
					Point_<int> pt2 = Point_<int>(
						settings.mouseLines[i].x2(),
						settings.mouseLines[i].y2());
					line(allChannels, pt1, pt2, Scalar(0), settings.channelCutThickness);
				}
				// draw
				Mat drawn;
				add(dropletMask, allChannels, drawn);
				cvtColor(drawn, data.drawnBgr, CV_GRAY2BGR);
				cvtColor(data.drawnBgr, data.drawnRgb, CV_BGR2RGB);
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
					absdiff(data.rawGray, bkgd, allMarkers); 
					threshold(allMarkers, allMarkers,
						settings.imgprogThreshold,
						HIGH_VALUE,
						cv::THRESH_BINARY);
					// flood and complement to get droplets (droplets internal)
					allDroplets = allMarkers.clone(); 
					seed = Point(0, 0);
					floodFillReturn = floodFill(allDroplets,
						seed, 
						HIGH_VALUE,
						0, Scalar_<int>(0), Scalar_<int>(0),
						FLOODFILL_FIXED_RANGE);
					allDroplets = HIGH_VALUE - allDroplets;
					// combine edges and internals to get whole droplets 
					bitwise_or(allMarkers, allDroplets, allDroplets);
					// clean up noise using masks
					bitwise_and(allMarkers, markerMask, allMarkers);
					bitwise_and(allDroplets, dropletMask, allDroplets);
					// find countours
					dropletContours.clear();
					markerContours.clear();
					findContours(allDroplets, dropletContours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
					findContours(allMarkers, markerContours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
					// filter contours base on size
					dc = dropletContours.begin();
					while (dc != dropletContours.end())
					{
						mom = moments(*dc);
						if (mom.m00 < settings.imgprogContourSize)
						{
							dc = dropletContours.erase(dc);
						}
						else
						{
							dc++;
						}
					}
					mc = markerContours.begin();
					while (mc != markerContours.end())
					{
						mom = moments(*mc);
						if (mom.m00 < settings.imgprogContourSize)
						{
							mc = markerContours.erase(mc);
						}
						else
						{
							mc++;
						}
					}
					// marker centroid

					// channel occuying marker

					// channel occupying droplets

				}

				//// CTRL
				if (settings.flag & UevaSettings::CTRL_ON)
				{
					QThread::msleep(80);
				}

				//// DRAW
				if (!data.rawGray.empty())
				{
					cvtColor(data.rawGray, data.drawnBgr, CV_GRAY2BGR);
					// channel text
					for (int i = 0; i < channels.size(); i++)
					{
						string dir;
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
							lineColor = Scalar(0, 0, 255); // red
						}
						else
						{
							fontScale = 0.8;
							lineColor = Scalar(255, 255, 255); // white
						}
						ostringstream oss;
						oss << "CH" << i << " " << dir;
						string str = oss.str();
						rect = boundingRect(channelContours[i]);
						anchor.x = rect.x + 60; // offset right from leftmost
						mom = moments(channelContours[i]);
						anchor.y = mom.m01 / mom.m00 - 30; // offset up from center
						lineThickness = 1;
						lineType = 8;
						putText(data.drawnBgr, str, anchor,
							FONT_HERSHEY_SIMPLEX, fontScale, lineColor, lineThickness, lineType);
						// for each current marker draw cyan rectangle
						// if isSelected draw red rectangle
					}
					// channel
					if (settings.flag & UevaSettings::DRAW_CHANNEL)
					{
						lineColor = Scalar(255, 255, 255); // white
						lineThickness = CV_FILLED; 
						lineType = 8;
						drawContours(data.drawnBgr, channelContours, -1,
							lineColor, lineThickness, lineType);
					}
					// droplet
					if (settings.flag & UevaSettings::DRAW_DROPLET)
					{
						lineColor = Scalar(255, 0, 255); // magenta
						lineThickness = 1;
						lineType = 8;
						drawContours(data.drawnBgr, dropletContours, -1,
							lineColor, lineThickness, lineType);
					}
					// marker
					if (settings.flag & UevaSettings::DRAW_MARKER)
					{
						lineColor = Scalar(255, 255, 0); // cyan
						lineThickness = 1;
						lineType = 8;
						drawContours(data.drawnBgr, markerContours, -1,
							lineColor, lineThickness, lineType);
					}
					// neck
					if (settings.flag & UevaSettings::DRAW_NECK)
					{

					}
					cvtColor(data.drawnBgr, data.drawnRgb, CV_BGR2RGB);
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

