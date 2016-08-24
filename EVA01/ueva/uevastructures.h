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

#ifndef UEVASTRUCTURES_H
#define UEVASTRUCTURES_H

#include <QtGui >
#include <string>
#include <sstream>
#include <fstream>
#include "opencv2/core.hpp"

struct UevaSettings
{
	UevaSettings();

	enum FlagValues
	{
		MASK_MAKING = 1,
		CHANNEL_CUTTING = 2,
		CAMERA_ON = 4,
		PUMP_ON = 8,
		IMGPROC_ON = 16,
		CTRL_ON = 32,
		DRAW_CHANNEL = 64,
		DRAW_DROPLET = 128,
		DRAW_MARKER = 256,
		DRAW_NECK = 512,
		RECORD_DATA = 1024,
		RECORD_RAW = 2048,
		RECORD_DRAWN = 4096,
	};
	int flag;

	QVector<QVector<int>> inletInfo;
	QVector<qreal> inletRequests;
	QVector<bool> linkRequests;
	QVector<bool> inverseLinkRequests;
	QVector<bool> autoCatchRequests;
	QVector<bool> useNeckRequests;

	QVector<QLine> mouseLines;
	QPoint rightPressPosition;
	QPoint leftPressPosition;
	QLine leftPressMovement;
	
	int maskBlockSize;
	int maskThreshold;
	int maskOpenSize;
	int channelErodeSize;
	int channelCutThickness;

	int imgprogThreshold;
	int imgprogErodeSize;
	int imgprogContourSize;
	int imgprogTrackTooFar;
	int imgprocConvexSize;
	int imgprocPersistence;
	int ctrlModelCov;
	int ctrlDisturbanceCov;
	int ctrlMarkerSize;
	int ctrlAutoHorzExcl;
	int ctrlAutoVertExcl;

};

struct UevaData
{
	UevaData();

	void headerToFile() const;
	void writeToFile() const;

	cv::Mat rawGray;
	cv::Mat drawnBgr;
	cv::Mat drawnRgb;
	QMap<QString, QVector<qreal>> map;

	static std::ofstream fileStream;
	static QTime startTime;
};

struct UevaBuffer
{
	UevaBuffer();

	void write(const UevaData &d);

	int index;
	int size;
	QMap<QString, QVector<QVector<qreal>> > map;
};

struct UevaCtrl
{
	UevaCtrl();

	static int index;
	static int numPlantState;
	static int numPlantInput;
	static int numPlantOutput;
	static double samplePeriod;

	int uncoUnob;
	int n;
	int m;
	int p;
	cv::Mat outputIndices;
	cv::Mat stateIndices;
	cv::Mat A;
	cv::Mat B;
	cv::Mat C;
	cv::Mat D;
	cv::Mat K1;
	cv::Mat K2;
	cv::Mat H;
	cv::Mat Ad;
	cv::Mat Bd;
	cv::Mat Cd;
	cv::Mat Wd;
};

struct UevaChannel
{
	UevaChannel();

	void makeChannelText(std::string &str, double &fontScale, cv::Scalar_<int> &lineColor,
		const bool &linkRequest, const bool &inverseLinkRequest);

	int index;
	cv::Mat mask;
	int direction;
	
	int biggestDropletIndex;
	int measuringMarkerIndex;
	int neckDropletIndex;
};

struct UevaDroplet
{
	UevaDroplet();

	cv::Mat mask;
	int kinkIndex;
	int neckIndex;
	float neckDistance;

	static std::ofstream fileStream;
};

struct UevaMarker
{
	UevaMarker();

	int identity;
	cv::Point_<int> centroid;
	cv::Rect_<int> rect;
	
	static int counter;
};

Q_DECLARE_METATYPE(UevaSettings)
Q_DECLARE_METATYPE(UevaData)
Q_DECLARE_METATYPE(UevaBuffer)
Q_DECLARE_METATYPE(UevaCtrl)
Q_DECLARE_METATYPE(UevaChannel)
Q_DECLARE_METATYPE(UevaDroplet)
Q_DECLARE_METATYPE(UevaMarker)

#endif