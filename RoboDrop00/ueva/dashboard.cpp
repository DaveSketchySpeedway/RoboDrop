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
	connect(recordNeckButton, SIGNAL(clicked()),
		parent, SLOT(recordNeckOnOff()));

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
	connect(erodeSizeSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(imgprocSettings()));
	connect(threshSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(imgprocSettings()));
	connect(contourSizeSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(imgprocSettings()));
	connect(sortGridSizeSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(imgprocSettings()));
	connect(sortOrderSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(imgprocSettings()));
	connect(convexSizeSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(imgprocSettings()));
	connect(persistenceSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(imgprocSettings()));

	// ctrl
	connect(ctrlButton, SIGNAL(clicked()),
		parent, SLOT(ctrlOnOff()));
	connect(markerSizeSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(ctrlSettings()));
	connect(autoMarginSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(ctrlSettings()));
	connect(this, SIGNAL(sendAutoCatchRequests(QVector<bool>)),
		parent, SLOT(receiveAutoCatchRequests(QVector<bool>)));
}

Dashboard::~Dashboard()
{

}

void Dashboard::resetInletWidgets(QVector<QVector<int>> inletInfo)
{
	//// DELETE
	foreach(InletWidget *inletWidget, inletWidgets)
	{
		disconnect(inletWidget->slider, SIGNAL(valueChanged(int)),
			this, SLOT(inletRequests()));
		pumpLayout->removeWidget(inletWidget);
		delete inletWidget;
	}
	inletWidgets.clear();

	//// NEW
	for (int i = 0; i < inletInfo.size(); i++)
	{
		InletWidget *inletWidget = new InletWidget(
			inletInfo[i][0],
			inletInfo[i][1], 
			inletInfo[i][3], 
			this);
		connect(inletWidget->slider, SIGNAL(valueChanged(int)),
			this, SLOT(inletRequests()));
		pumpLayout->addWidget(inletWidget);
		inletWidgets.push_back(inletWidget);
	}
	pumpLayout->addStretch();

	//// INITIALIZE
	inletRequests();
}

void Dashboard::resetAutoCatchBox(int numChannel)
{
	//// DELETE
	foreach(QCheckBox *autoCatchBox, autoCatchBoxes)
	{
		disconnect(autoCatchBox, SIGNAL(clicked()),
			this, SLOT(autoCatchRequests()));
		ctrlLayout->removeWidget(autoCatchBox);
		delete autoCatchBox;
	}
	autoCatchBoxes.clear();

	//// NEW
	for (int i = 0; i < numChannel; i++)
	{
		QCheckBox *autoCatchBox = new QCheckBox(QString::number(i), this);
		connect(autoCatchBox, SIGNAL(clicked()),
			this, SLOT(autoCatchRequests()));
		ctrlLayout->addWidget(autoCatchBox);
		autoCatchBoxes.push_back(autoCatchBox);
	}
	ctrlLayout->addStretch();

	//// INITIALIZE
	autoCatchRequests();
}

void Dashboard::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape)
	{
		this->hide();
	}
}

void Dashboard::zeroPump()
{
	foreach (InletWidget *inletWidget, inletWidgets)
	{
		inletWidget->slider->setValue(0);
		inletWidget->spinBox->setValue(0);
	}
}

void Dashboard::inletRequests()
{
	inletValues.clear();
	foreach(InletWidget *inletWidget, inletWidgets)
	{
		inletValues.push_back(inletWidget->slider->value());
	}
	emit sendInletRequests(inletValues);
}

void Dashboard::autoCatchRequests()
{
	autoCatchValues.clear();
	foreach(QCheckBox *autoCatchBox, autoCatchBoxes)
	{
		autoCatchValues.push_back(autoCatchBox->isChecked());
	}
	emit sendAutoCatchRequests(autoCatchValues);
}