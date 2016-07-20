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

#ifndef S2ENGINETHREAD_H
#define S2ENGINETHREAD_H

#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <QtGui >
#include <QImage > 
#include <QThread >
#include <QMutex >
#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

#include "uevastructures.h"
#include "uevafunctions.h"

using namespace std;
using namespace cv;


class S2EngineThread : public QThread
{
	Q_OBJECT

public:
	S2EngineThread(QObject *parent = 0);
	~S2EngineThread();

	//// THREAD OPERATIONS
	void setSettings(const UevaSettings &s);
	void setData(const UevaData &d);
	void wake();

	//// SINGLE TIME 
	void loadCtrl(string fileName,
		int *numState, int *numIn, int *numOut, int *numCtrl, double *ctrlTs);
	void setCalib(double micronLength);
	void setBkgd();
	void separateChannels(int &numChan);
	void sortChannels(map<string, vector<int> > &channelInfo);

signals:
	void engineSignal(const UevaData &d);

protected:

	//// CONTINUOUS 
	void run();

private:
	//// THREAD VARIABLES
	bool idle;
	QMutex mutex;
	UevaSettings settings;
	UevaData data;

	//// PERSISTENT VARIABLES
	vector<UevaCtrl> ctrls;
	vector<int> actualCombination;
	int ctrlIndex;
	double micronPerPixel;
	Mat bkgd;
	Mat dropletMask;
	Mat markerMask;
	Mat allChannels;
	vector<vector<Point_<int>>> channelContours;
	vector<UevaChannel> channels;

	//// NON PERSISTANT VARIABLES
	Mat allDroplets;
	Mat allMarkers;
	vector<vector< Point_<int> >> dropletContours;
	vector<vector< Point_<int> >> markerContours;
	vector<UevaDroplet> droplets;
	vector<UevaMarker> markers;

	//// CONVENIENT PARAMETERS
	enum EngineConstants
	{
		LOW_VALUE = 0,
		MID_VALUE = 127,
		HIGH_VALUE = 255,
	};
	Mat structuringElement;
	Point_<int> seed;
	int floodFillReturn;
	Scalar_<int> lineColor;
	int lineThickness;
	int lineType;
	double fontScale;
	Point_<int> anchor;
	Moments mom;
	Rect rect;
	bool needReset;
	vector<int> desiredCombination;
	int vacancy;
	Point_<int> mousePressLeft;
	Point_<int> mousePressRight;
	Point_<int> mousePressPrevious;
	Point_<int> mousePressCurrent;

	private slots:


};



#endif
