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

#include "dashboard.h"

Dashboard::Dashboard(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	setWindowFlags(Qt::Window);

	// record
	connect(recordDataButton, SIGNAL(clicked()),
		parent, SLOT(recordDataOnOff()));
	connect(recordRawButton, SIGNAL(clicked()),
		parent, SLOT(recordRawOnOff()));
	connect(recordDrawnButton, SIGNAL(clicked()),
		parent, SLOT(recordDrawnOnOff()));

	// pump
	connect(pumpButton, SIGNAL(clicked()),
		parent, SLOT(pumpOnOff()));
	connect(zeroPumpButton, SIGNAL(clicked()),
		this, SLOT(zeroPump()));
	connect(this, SIGNAL(sendInletRequests(QVector<qreal>)),
		parent, SLOT(receiveInletRequests(QVector<qreal>)));

	// imgproc
	connect(imgprocButton, SIGNAL(clicked()),
		parent, SLOT(imgprocOnOff()));
	connect(threshSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(imgprocSettings()));
	connect(contourSizeSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(imgprocSettings()));

	// ctrl
	connect(ctrlButton, SIGNAL(clicked()),
		parent, SLOT(ctrlOnOff()));
}

Dashboard::~Dashboard()
{

}

void Dashboard::resetInletWidgets(
	QVector<QVector<int>> inletInfo)
{
	//// DELETE
	foreach(InletWidget *inlet, inlets)
	{
		disconnect(inlet->slider, SIGNAL(valueChanged(int)),
			this, SLOT(inletRequests()));
		pumpLayout->removeWidget(inlet);
		delete inlet;
	}
	inlets.clear();

	//// NEW
	for (int i = 0; i < inletInfo.size(); i++)
	{
		InletWidget *inlet = new InletWidget(
			inletInfo[i][0],
			inletInfo[i][1], 
			inletInfo[i][3], 
			this);
		connect(inlet->slider, SIGNAL(valueChanged(int)),
			this, SLOT(inletRequests()));
		pumpLayout->addWidget(inlet);
		inlets.push_back(inlet);
	}
	pumpLayout->addStretch();
}


void Dashboard::zeroPump()
{
	foreach (InletWidget *inlet, inlets)
	{
		inlet->slider->setValue(0);
		inlet->spinBox->setValue(0);
	}
}

void Dashboard::inletRequests()
{
	inletValues.clear();
	foreach(InletWidget *inlet, inlets)
	{
		inletValues.push_back((inlet->slider->value()));
	}
	emit sendInletRequests(inletValues);
}