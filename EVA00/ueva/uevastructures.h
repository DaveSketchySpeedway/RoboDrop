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
#include <fstream>
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;



struct UevaSettings
{
	UevaSettings();

	QVector<QVector<int>> inletInfo;
	QVector<qreal> inletRequests;
	enum FlagValues
	{
		MASK_MAKING = 1,
		CHANNEL_CUTTING = 2,
		HIGHLIGHTING = 4,
		PUMP_ON = 8,
		IMGPROC_ON = 16,
		CTRL_ON = 32,
	};
	int flag;
};



struct UevaData
{
	UevaData();

	void headerToFile() const;
	void writeToFile() const;

	static ofstream fileStream;
	static QTime startTime;

	Mat image;
	QMap<QString, QVector<qreal>> map;
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

	static int numPlantState;
	static int numPlantInput;
	static int numPlantOutput;
	static double samplePeriod;

	int uncoUnob;
	Mat outputIdx;
	Mat stateIdx;
	Mat A;
	Mat B;
	Mat C;
	Mat D;
	Mat K1; 
	Mat K2;
	Mat H;
};



Q_DECLARE_METATYPE(UevaSettings)
Q_DECLARE_METATYPE(UevaData)
Q_DECLARE_METATYPE(UevaBuffer)
Q_DECLARE_METATYPE(UevaCtrl)

#endif