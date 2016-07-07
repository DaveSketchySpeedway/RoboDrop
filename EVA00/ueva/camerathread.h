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


#ifndef CAMERATHREAD_H
#define CAMERATHREAD_h

#include <QtGui >
#include <QImage > 
#include <QThread >
#include <QMutex >
#include "zyla.h"

class CameraThread : public QThread
{
	Q_OBJECT

public:
	CameraThread(QObject *parent = 0);
	~CameraThread();

	void getCurrentImage(QImage &image);
	void addCamera();
	void deleteCamera();
	QMap<QString, QString> defaultSettings();
	QMap<QString, QString> getSettings();
	void setSettings(QMap<QString, QString> &s);
	void startCamera(const int &Ts);
	void stopCamera();

signals:

protected:
	void run();

private:
	Zyla *camera;
	ZylaSettings settings;
	int cameraConnected;
	int cameraAcquiring;
	QMutex mutex;
	QImage currentImage;

	private slots:


};



#endif