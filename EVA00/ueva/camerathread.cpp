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

#include "camerathread.h"

CameraThread::CameraThread(QObject *parent)
	: QThread(parent)
{
	mutex.lock();
	settings = ZylaSettings();
	hasCamera = 0;
	mutex.unlock();
}

CameraThread::~CameraThread()
{
	mutex.lock();
	deleteCamera();
	mutex.unlock();
}

void CameraThread::run()
{
	forever
	{

		mutex.lock();
		//qDebug() << QThread::currentThreadId << "run";
		mutex.unlock();

	}
}

void CameraThread::addCamera()
{
	mutex.lock();
	camera = new Zyla(0);
	hasCamera = 1;
	mutex.unlock();
}

void CameraThread::deleteCamera()
{
	mutex.lock();
	delete camera;
	hasCamera = 0;
	mutex.unlock();	
}

QMap<QString, QString> CameraThread::defaultSettings()
{
	mutex.lock();
	settings = ZylaSettings();
	mutex.unlock();
	return settings.allMap;
}

QMap<QString, QString> CameraThread::getSettings()
{
	mutex.lock();
	if (hasCamera)
	{
		camera->get(settings);
		settings.collapse();
	}
	mutex.unlock();
	return settings.allMap;
}

void CameraThread::setSettings(QMap<QString, QString> &s)
{
	mutex.lock();
	if (hasCamera)
	{
		settings.allMap = s;
		settings.expand();
		settings.print();
		camera->set(settings);
	}
	mutex.unlock();
}