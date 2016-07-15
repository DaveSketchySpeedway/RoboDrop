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

//// CONTINUOUS
void S2EngineThread::run()
{
	forever
	{
		if (!idle)
		{
			mutex.lock();
			data.map["inletWrite"] = settings.inletRequests;

			//// DEFAULT
			if (!(settings.flag & UevaSettings::MASK_MAKING) &
				!(settings.flag & UevaSettings::CHANNEL_CUTTING) &
				!(settings.flag & UevaSettings::HIGHLIGHTING) &
				!(settings.flag & UevaSettings::CTRL_ON) &
				!(settings.flag & UevaSettings::IMGPROC_ON) &
				!data.rawGray.empty())
			{
				cvtColor(data.rawGray, data.drawnBgr, CV_GRAY2BGR);
				cvtColor(data.drawnBgr, data.drawnRgb, CV_BGR2RGB);
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
				structuringElement = getStructuringElement(
					settings.maskOpenShape,
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
				structuringElement = getStructuringElement(
					settings.channelErodeShape,
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

			//// HIGH LIGHTING
			else if (settings.flag & UevaSettings::HIGHLIGHTING)
			{

			}
			else
			{

				//// CTRL
				if (settings.flag & UevaSettings::CTRL_ON)
				{
					QThread::msleep(80);
				}
				
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
						Moments m = moments(*dc);
						if (m.m00 < settings.imgprogContourSize)
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
						Moments m = moments(*mc);
						if (m.m00 < settings.imgprogContourSize)
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

					// draw
					cvtColor(data.rawGray, data.drawnBgr, CV_GRAY2BGR);
					// for each channel draw text white ch1 d1 m0
					// for each occupying marker draw rectangle cyan
					// for each reference marker draw rectangle red
					if (settings.flag & UevaSettings::DRAW_CHANNEL)
					{
					// for each channel draw filled contour	white
					}
					if (settings.flag & UevaSettings::DRAW_DROPLET)
					{
						lineColor = Scalar(255, 0, 255); // magenta
						lineThickness = 1;
						lineType = 8;
						drawContours(data.drawnBgr, dropletContours, -1,
							lineColor, lineThickness, lineType);
					}
					if (settings.flag & UevaSettings::DRAW_MARKER)
					{
						lineColor = Scalar(255, 255, 0); // cyan
						lineThickness = 1;
						lineType = 8;
						drawContours(data.drawnBgr, markerContours, -1,
							lineColor, lineThickness, lineType);
					}
					if (settings.flag & UevaSettings::DRAW_NECK)
					{

					}
					cvtColor(data.drawnBgr, data.drawnRgb, CV_BGR2RGB);
				}
			}


			emit engineSignal(data);
			idle = true;
			mutex.unlock();

		}
	}
}

