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
	void setCalib(double micronLength);
	void setBkgd();
	void separateChannels(int &numChan);
	void sortChannels(std::map<std::string, std::vector<int> > &channelInfo);
	void loadCtrl(std::string fileName,
		int *numState, int *numIn, int *numOut, int *numCtrl, double *ctrlTs);
	void initCtrl();
	void resetCtrl();

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
	std::vector<UevaCtrl> ctrls;
	std::vector<int> activatedChannels;
	double micronPerPixel;
	cv::Mat bkgd;
	cv::Mat dropletMask;
	cv::Mat markerMask;
	cv::Mat allChannels;
	std::vector<std::vector<cv::Point_<int>>> channelContours;
	std::vector<UevaChannel> channels;
	QVector<qreal> estimates;
	QVector<qreal> measures;
	QVector<qreal> references;
	QVector<qreal> states;
	QVector<qreal> integralStates;
	QVector<qreal> commands;
	QVector<qreal> measureOffsets;
	QVector<qreal> referenceOffsets;

	//// NON PERSISTANT VARIABLES
	bool needReset;
	bool needInactivateAll;
	int vacancy;
	std::vector<int> desiredChannels;
	cv::Mat allDroplets;
	cv::Mat allMarkers;
	std::vector<std::vector< cv::Point_<int> >> dropletContours;
	std::vector<std::vector< cv::Point_<int> >> markerContours;
	std::vector<UevaDroplet> droplets;
	std::vector<UevaMarker> markers;
	cv::Mat x;
	cv::Mat z;
	cv::Mat u;
	cv::Mat y_est;
	cv::Mat y;
	cv::Mat r;
	cv::Mat x_new;
	cv::Mat z_new;
	cv::Mat u_new;


	//// CONVENIENT PARAMETERS
	enum EngineConstants
	{
		LOW_VALUE = 0,
		MID_VALUE = 127,
		HIGH_VALUE = 255,
	};
	cv::Mat structuringElement;
	cv::Point_<int> seed;
	int floodFillReturn;
	cv::Scalar_<int> lineColor;
	int lineThickness;
	int lineType;
	double fontScale;
	cv::Point_<int> anchor;
	cv::Moments mom;
	cv::Rect rect;
	cv::Point_<int> mousePressLeft;
	cv::Point_<int> mousePressRight;
	cv::Point_<int> mousePressPrevious;
	cv::Point_<int> mousePressCurrent;

	private slots:

};



#endif
