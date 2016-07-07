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

#ifndef PUMPTHREAD_H
#define PUMPTHREAD_H

#include <QtGui >
#include <QImage > 
#include <QThread >
#include <QMutex >
#include "structures.h"
#include "mfcs.h"

class PumpThread : public QThread
{
	Q_OBJECT
				
public:
	PumpThread(QObject *parent = 0);
	~PumpThread();

	void setSettings(const UevaSettings &s);
	void setData(const UevaData &d);
	void wake();
	void deletePumps();
	void addPump(const int &sn, const int &ez);

signals:
	void pumpSignal(const UevaData &d);

protected:
	void run();

private:
	UevaSettings settings;
	UevaData data;
	QVector<Mfcs*> pumps;
	bool idle;
	QMutex mutex;

	private slots:

};


#endif