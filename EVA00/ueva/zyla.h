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


#ifndef ZYLA_H
#define ZYLA_H


#include "atcore.h"
#include "atutility.h"
#include "opencv2/core.hpp"
#include <iostream>
#include <QtGui>
#include <map>
#include <vector>
#include <string>

struct ZylaSettings
{
	ZylaSettings();
	~ZylaSettings();

	void print();
	void collapse();
	void expand();

	QMap<QString, QString> allMap;

	std::map<AT_WC*, AT_BOOL> boolMap;
	std::map<AT_WC*, AT_BOOL>::iterator boolMapIterator;
	std::map<AT_WC*, AT_64> intMap;
	std::map<AT_WC*, AT_64>::iterator intMapIterator;
	std::map<AT_WC*, double> floatMap;
	std::map<AT_WC*, double>::iterator floatMapIterator;
	std::map<AT_WC*, AT_WC*> enumMap;
	std::map<AT_WC*, AT_WC*>::iterator enumMapIterator;
};

class Zyla
{
public:
	Zyla(int i);
	~Zyla();


	void get(ZylaSettings &s);
	void set(ZylaSettings &s);
	void start(const int &Ts);
	void stop();
	void process(cv::Mat &image);


protected:




private:
	int cameraIndex;
	int returnCode;
	AT_H handle;
	AT_64 imageSizeBytes;
	AT_64 imageStride;
	AT_64 imageWidth;
	AT_64 imageHeight;
	AT_WC *imageEncode;
	int bufferSize;
	double frameRate;
	int samplePeriod;
	int queueLength;

	AT_64 accumNumFrames; // should last 1.8e17 seconds before overflow
	unsigned char** buffers;
	unsigned char** alignedBuffers;

};






#endif