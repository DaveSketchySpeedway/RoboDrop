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

void S2EngineThread::run()
{
	forever
	{
		if (!idle)
		{
			mutex.lock();

			data.map["inletWrite"] = settings.inletRequests;

			if (settings.flag & UevaSettings::IMGPROC_ON)
			{
				QThread::msleep(80);
				//qDebug() << QThread::currentThreadId() <<
				//	"imgproc on";
			}

			if (settings.flag & UevaSettings::CTRL_ON)
			{
				QThread::msleep(80);
				//qDebug() << QThread::currentThreadId() <<
				//	"ctrl on";
			}

			if (settings.flag & UevaSettings::MASK_MAKING)
			{
				//qDebug() << QThread::currentThreadId() <<
				//	"mask making";
			}

			if (settings.flag & UevaSettings::CHANNEL_CUTTING)
			{
				//qDebug() << QThread::currentThreadId() <<
				//	"channel cutting";
			}

			if (settings.flag & UevaSettings::HIGHLIGHTING)
			{
				//qDebug() << QThread::currentThreadId() <<
				//	"highlighting";
			}

			emit engineSignal(data);
			idle = true;
			mutex.unlock();

		}
	}
}

