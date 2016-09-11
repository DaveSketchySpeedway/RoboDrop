/*
Copyright 2016 David Wong

This file is part of RoboDrop from the uEVA project. https://github.com/DaveSketchySpeedway/uEVA

RoboDrop is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

RoboDrop is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with RoboDrop. If not, see <http://www.gnu.org/licenses/>
*/

#include "camerathread.h"

CameraThread::CameraThread(QObject *parent)
	: QThread(parent)
{
	mutex.lock();
	settings = ZylaSettings();
	cameraConnected = 0;
	cameraAcquiring = 0;
	currentImage = cv::Mat(0, 0, CV_16UC1);
	mutex.unlock();
}

CameraThread::~CameraThread()
{
	mutex.lock();
	deleteCamera();
	mutex.unlock();
}

void CameraThread::getCurrentImage(cv::Mat &image)
{
	mutex.lock();
	//// make 8 bit clone out of 16 bit 
	currentImage.convertTo(image, CV_8UC1, 0.00390625); // alpha = 1 / (2^16 / 2^8)
	//currentImage = Mat(0, 0, CV_16UC1); // test if converTo does cloning
	//image = currentImage.clone(); // test speed 16 bit vs 8 bit
	mutex.unlock();
}

void CameraThread::addCamera()
{
	mutex.lock();
	camera = new Zyla(0);
	cameraConnected = 1;
	mutex.unlock();
}

void CameraThread::deleteCamera()
{
	mutex.lock();
	delete camera;
	cameraConnected = 0;
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
	if (cameraConnected)
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
	if (cameraConnected)
	{
		settings.allMap = s;
		settings.expand();
		settings.print();
		camera->set(settings);
	}
	mutex.unlock();
}

void CameraThread::startCamera(const int &Ts)
{
	mutex.lock();
	camera->start(Ts);
	cameraAcquiring = 1;
	mutex.unlock();
}

void CameraThread::stopCamera()
{
	mutex.lock();
	camera->stop();
	cameraAcquiring = 0;
	currentImage = cv::Mat(0, 0, CV_16UC1);
	mutex.unlock();
}

void CameraThread::run()
{
	forever
	{
		mutex.lock();
		if (cameraAcquiring)
		{
			camera->process(currentImage);
			//qDebug() <<
			//	currentImage.total() << " " <<
			//	currentImage.type() << " " << // 0 means CV_8U
			//	currentImage.rows << " " <<
			//	currentImage.cols << " " <<
			//	currentImage.isContinuous() << endl;;
		}
		mutex.unlock();
	}
}