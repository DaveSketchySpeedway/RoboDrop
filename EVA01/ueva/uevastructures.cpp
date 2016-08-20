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

#include "uevastructures.h"



//// SETTINGS
UevaSettings::UevaSettings()
{
	flag = 0;
	for (int i = 0; i < 10; i++) // limited by 0-9 on keyboard
	{
		linkRequests.push_back(false);
		inverseLinkRequests.push_back(false);
	}
}



//// DATA
UevaData::UevaData()
{
	//// PUMP
	QVector<qreal> inletWrite;
	QVector<qreal> inletRead;
	QVector<qreal> inletTime;
	map["inletWrite"] = inletWrite;
	map["inletRead"] = inletRead;
	map["inletTime"] = inletTime;

	//// CTRL
	QVector<qreal> raws;
	QVector<qreal> measures;
	QVector<qreal> estimates;
	QVector<qreal> references;
	QVector<qreal> states;
	QVector<qreal> integralStates;
	QVector<qreal> commands;
	QVector<qreal> measureOffsets;
	QVector<qreal> referenceOffsets;
	map["ctrlRaw"] = raws;
	map["ctrlMeasure"] = measures;
	map["ctrlEstimate"] = estimates;
	map["ctrlReference"] = references;
	map["ctrlState"] = states;
	map["ctrlIntegraState"] = integralStates;
	map["ctrlCommand"] = commands;
}

std::ofstream UevaData::fileStream;
QTime UevaData::startTime;

void UevaData::headerToFile() const
{
	QMapIterator<QString, QVector<qreal>> i(map);

	fileStream << "time" << ",";

	while (i.hasNext())
	{
		i.next();
		if (!i.value().empty())
		{
			for (int j = 0; j < i.value().size(); j++)
				fileStream << i.key().toStdString() << j << ",";
		}
	}

	fileStream << std::endl;
}

void UevaData::writeToFile() const
{
	QMapIterator<QString, QVector<qreal>> i(map);

	QTime now = QTime::currentTime();
	fileStream << (double)startTime.msecsTo(now) / 1000.0 << ",";

	while (i.hasNext())
	{
		i.next();
		if (!i.value().empty())
		{
			for (int j = 0; j < i.value().size(); j++)
				fileStream << i.value()[j] << ",";
		}
	}

	fileStream << std::endl;
}



//// BUFFER
UevaBuffer::UevaBuffer()
{
	index = 0;
	size = 100; // 10 seconds of data
}

void UevaBuffer::write(const UevaData &data)
{
	//// SYNC BUFFER WITH DATA
	int needToSync = 0;
	QMapIterator< QString, QVector<qreal> > d(data.map);
	d.toFront();
	while (d.hasNext())
	{
		d.next();
		if (map[d.key()].size() != d.value().size())
		{
			needToSync = 1;
			break;
		}
	}
	if (needToSync)
	{
		// delete
		QMutableMapIterator< QString, QVector<QVector<qreal>> > b(map);
		b.toFront();
		while (b.hasNext())
		{
			b.next();
			b.value().clear();
		}
		// new
		index = 0;
		QVector<qreal> zeroVector(size, 0.0);
		QVector<QVector<qreal>> zeroMatrix;
		d.toFront();
		while (d.hasNext())
		{
			d.next();
			for (int i = 0; i < d.value().size(); i++)
			{
				zeroMatrix.push_back(zeroVector);
			}
			map[d.key()] = zeroMatrix;
			zeroMatrix.clear();
		}
	}
	//// STORE DATA IN BUFFER
	QMutableMapIterator< QString, QVector<QVector<qreal>> > b(map);
	b.toFront();
	while (b.hasNext())
	{
		b.next();
		for (int i = 0; i < data.map[b.key()].size(); i++)
		{
			b.value()[i][index] = data.map[b.key()][i];
		}
	}
	//// MOVE BUFFER
	if ((++index) == size)
	{
		index = 0;
	}
}



//// CTRL
UevaCtrl::UevaCtrl()
{

}

int UevaCtrl::index = 0;
int UevaCtrl::numPlantState = 0;
int UevaCtrl::numPlantInput = 0;
int UevaCtrl::numPlantOutput = 0;
double UevaCtrl::samplePeriod = 0;



//// CHANNEL
UevaChannel::UevaChannel()
{
	direction = 0;
	biggestDropletIndex = -1;
	measuringMarkerIndex = -1;
	neckDropletIndex = -1;
}



//// DROPLET
UevaDroplet::UevaDroplet()
{
	kinkIndex = -1;
	neckIndex = -1;
}

std::ofstream UevaDroplet::fileStream;



//// MARKER
UevaMarker::UevaMarker()
{

}

int UevaMarker::counter = 0;
