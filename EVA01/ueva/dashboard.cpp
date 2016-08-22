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
		this, SLOT(zeroInlets()));
	connect(this, SIGNAL(sendInletRequests(QVector<qreal>)),
		parent, SLOT(receiveInletRequests(QVector<qreal>)));

	// imgproc
	connect(imgprocButton, SIGNAL(clicked()),
		parent, SLOT(imgprocOnOff()));
	connect(threshSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(imgprocSettings()));
	connect(erodeSizeSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(imgprocSettings()));
	connect(contourSizeSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(imgprocSettings()));
	connect(trackTooFarSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(imgprocSettings()));
	connect(convexSizeSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(imgprocSettings()));
	connect(persistenceSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(imgprocSettings()));

	// ctrl
	connect(ctrlButton, SIGNAL(clicked()),
		parent, SLOT(ctrlOnOff()));
	connect(modelCovSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(ctrlSettings()));
	connect(disturbanceCovSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(ctrlSettings()));
	connect(markerSizeSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(ctrlSettings()));
	connect(autoHorzExclSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(ctrlSettings()));
	connect(autoVertExclSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(ctrlSettings()));
	connect(this, SIGNAL(sendAutoCatchRequests(QVector<bool>)),
		parent, SLOT(receiveAutoCatchRequests(QVector<bool>)));
	connect(this, SIGNAL(sendUseNeckRequests(QVector<bool>)),
		parent, SLOT(receiveUseNeckRequests(QVector<bool>)));
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
			this, SLOT(requestInlets()));
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
			this, SLOT(requestInlets()));
		pumpLayout->addWidget(inletWidget);
		inletWidgets.push_back(inletWidget);
	}

	//// INITIALIZE
	requestInlets();
}

void Dashboard::resetAutoCatchBoxes(int numChannel)
{
	//// DELETE
	foreach(QCheckBox *autoCatchBox, autoCatchBoxes)
	{
		disconnect(autoCatchBox, SIGNAL(clicked()),
			this, SLOT(requestAutoCatches()));
		autoCatchLayout->removeWidget(autoCatchBox);
		delete autoCatchBox;
	}
	autoCatchBoxes.clear();

	//// NEW
	for (int i = 0; i < numChannel; i++)
	{
		QCheckBox *autoCatchBox = new QCheckBox(QString::number(i), this);
		connect(autoCatchBox, SIGNAL(clicked()),
			this, SLOT(requestAutoCatches()));
		autoCatchLayout->addWidget(autoCatchBox);
		autoCatchBoxes.push_back(autoCatchBox);
	}

	//// INITIALIZE
	requestAutoCatches();
}

void Dashboard::resetUseNeckBoxes(int numChannel)
{
	//// DELETE
	foreach(QCheckBox *useNeckBox, useNeckBoxes)
	{
		disconnect(useNeckBox, SIGNAL(clicked()),
			this, SLOT(requestUseNecks()));
		useNeckLayout->removeWidget(useNeckBox);
		delete useNeckBox;
	}
	useNeckBoxes.clear();

	//// NEW
	for (int i = 0; i < numChannel; i++)
	{
		QCheckBox *useNeckBox = new QCheckBox(QString::number(i), this);
		connect(useNeckBox, SIGNAL(clicked()),
			this, SLOT(requestUseNecks()));
		useNeckLayout->addWidget(useNeckBox);
		useNeckBoxes.push_back(useNeckBox);
	}

	//// INITIALIZE
	requestUseNecks();
}

void Dashboard::regurgitateInlets(QVector<qreal> values)
{
	for (int i = 0; i < inletWidgets.size(); i++)
	{
		if (i < values.size())
		{
			inletWidgets[i]->slider->setValue(values[i]);
			inletWidgets[i]->spinBox->setValue(values[i]);
		}
	}
}

void Dashboard::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape)
	{
		this->hide();
	}
}

void Dashboard::zeroInlets()
{
	foreach (InletWidget *inletWidget, inletWidgets)
	{
		inletWidget->slider->setValue(0);
		inletWidget->spinBox->setValue(0);
	}
}

void Dashboard::requestInlets()
{
	inletValues.clear();
	foreach(InletWidget *inletWidget, inletWidgets)
	{
		inletValues.push_back(inletWidget->slider->value());
	}
	emit sendInletRequests(inletValues);
}

void Dashboard::requestAutoCatches()
{
	autoCatchValues.clear();
	foreach(QCheckBox *autoCatchBox, autoCatchBoxes)
	{
		autoCatchValues.push_back(autoCatchBox->isChecked());
	}
	emit sendAutoCatchRequests(autoCatchValues);
}

void Dashboard::requestUseNecks()
{
	useNeckValues.clear();
	foreach(QCheckBox *useNeckBox, useNeckBoxes)
	{
		useNeckValues.push_back(useNeckBox->isChecked());
	}
	emit sendUseNeckRequests(useNeckValues);
}