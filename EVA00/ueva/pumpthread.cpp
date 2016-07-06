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

#include "pumpthread.h"

PumpThread::PumpThread(QObject *parent)
	: QThread(parent)
{
	mutex.lock();
	idle = true;
	mutex.unlock();
}

PumpThread::~PumpThread()
{
	mutex.lock();
	deletePumps();
	mutex.unlock();
}

void PumpThread::setSettings(const UevaSettings &s)
{
	mutex.lock();
	settings = s;
	mutex.unlock();
}

void PumpThread::setData(const UevaData &d)
{
	mutex.lock();
	data = d;
	mutex.unlock();
}

void PumpThread::wake()
{
	mutex.lock();
	idle = false;
	mutex.unlock();
}

void PumpThread::deletePumps()
{
	mutex.lock();
	foreach(Mfcs* pump, pumps)
	{
		delete pump;
	}
	pumps.clear();
	mutex.unlock();
}

void PumpThread::addPump(const int &sn, const int &ez)
{
	mutex.lock();
	Mfcs *pump = new Mfcs(sn, ez);
	pumps.push_back(pump);
	mutex.unlock();
}

void PumpThread::run()
{
	forever
	{
		if (!idle)
		{
			mutex.lock();

			if (settings.flag & UevaSettings::PUMP_ON)
			{
				for (int i = 0; i < settings.inletInfo.size(); i++)
				{
					//// LIMIT
					if (data.map["inletWrite"][i] > settings.inletInfo[i][3])
					{
						data.map["inletWrite"][i] = settings.inletInfo[i][3];
					}
					//// WRITE
					pumps[settings.inletInfo[i][0]]->command(
						settings.inletInfo[i][1],
						data.map["inletWrite"][i]);
					//// READ
					float p, t;
					pumps[settings.inletInfo[i][0]]->measure(
						settings.inletInfo[i][1],
						&p, &t);
					data.map["inletRead"].push_back(p);
					data.map["inletTime"].push_back(t);
				}
			}

			emit pumpSignal(data);
			idle = true;
			mutex.unlock();
		}
	}
}