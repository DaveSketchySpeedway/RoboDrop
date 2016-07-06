/*
Copyright 2016 David Wong

This file is part of uEVA. https://github.com/DaveSketchySpeedway/uEva

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
#include <QtGui>
#include <iostream>
#include <map>
#include <string>
using namespace std;

struct ZylaSettings
{
	ZylaSettings();
	~ZylaSettings();

	void print();
	void collapse();
	void expand();

	QMap<QString, QString> allMap;

	map<AT_WC*, AT_BOOL> boolMap;
	map<AT_WC*, AT_BOOL>::iterator boolMapIterator;
	map<AT_WC*, AT_64> intMap;
	map<AT_WC*, AT_64>::iterator intMapIterator;
	map<AT_WC*, double> floatMap;
	map<AT_WC*, double>::iterator floatMapIterator;
	map<AT_WC*, AT_WC*> enumMap;
	map<AT_WC*, AT_WC*>::iterator enumMapIterator;
};

class Zyla
{
public:
	Zyla(int i);
	~Zyla();


	void get(ZylaSettings &s);
	void set(ZylaSettings &s);
	void start();
	void end();


protected:




private:
	int cameraIndex;
	int returnCode;
	AT_H handle;

};






#endif