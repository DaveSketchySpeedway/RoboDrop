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

#include "setup.h"

Setup::Setup(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	setWindowFlags(Qt::Window);

	//// CAMERA
	connect(connectCameraButton, SIGNAL(clicked()),
		parent, SLOT(connectCamera()));
	connect(setCameraButton, SIGNAL(clicked()),
		parent, SLOT(setCamera()));
	connect(cameraButton, SIGNAL(clicked()),
		parent, SLOT(cameraOnOff()));
	connect(getCameraButton, SIGNAL(clicked()),
		parent, SLOT(getCamera()));


	cameraTree->setColumnCount(2);
	cameraTree->header()->resizeSection(0, 300);
	cameraTree->setSortingEnabled(true);
	cameraTree->setHeaderLabels(QStringList() <<
		tr("Setting") <<
		tr("Value"));

	//// PUMP
	connect(addPumpButton, SIGNAL(clicked()),
		this, SLOT(addPump()));
	connect(clearPumpButton, SIGNAL(clicked()),
		this, SLOT(clearPump()));
	connect(getPumpButton, SIGNAL(clicked()),
		parent, SLOT(getPump()));
	connect(setPumpButton, SIGNAL(clicked()),
		parent, SLOT(setPump()));

	pumpTree->setColumnCount(4);
	pumpTree->setSortingEnabled(false);
	pumpTree->setHeaderLabels(QStringList() <<
		tr("Pump") <<
		tr("Transducer") <<
		tr("Inlet Index") <<
		tr("Limit (mbar)"));

	//// IMGPROC
	connect(calibButton, SIGNAL(clicked()),
		parent, SLOT(setCalib()));
	connect(bkgdButton, SIGNAL(clicked()),
		parent, SLOT(setBkgd()));
	connect(maskButton, SIGNAL(clicked()),
		parent, SLOT(maskOnOff()));
	connect(channelButton, SIGNAL(clicked()),
		parent, SLOT(channelOnOff()));
	connect(sepSortButton, SIGNAL(clicked()),
		parent, SLOT(sepSortOnOff()));
	
	connect(thresholdSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(maskSetup()));
	connect(blockSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(maskSetup()));
	connect(openSizeSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(maskSetup()));
	connect(erodeSizeSlider, SIGNAL(valueChanged(int)),

		parent, SLOT(channelSetup()));
	connect(cutThicknessSlider, SIGNAL(valueChanged(int)),
		parent, SLOT(channelSetup()));


	//// CTRL
	connect(loadCtrlButton, SIGNAL(clicked()),
		parent, SLOT(loadCtrl()));
	connect(timerIntervalButton, SIGNAL(clicked()),
		parent, SLOT(changeTimerInterval()));
}

Setup::~Setup()
{

}

void Setup::createChannelInfoWidgets(int numChan)
{
	for (int i = 0; i < numChan; i++)
	{
		ChannelInfoWidget *channelInfoWidget = new ChannelInfoWidget(i, numChan, this);
		channelInfoWidgets.push_back(channelInfoWidget);
		sepSortLayout->addWidget(channelInfoWidget);
	}
}

void Setup::deleteChannelInfoWidgets(map<string, vector<int> > &channelInfo)
{
	vector<int> newIndices;
	vector<int> directions;
	foreach(ChannelInfoWidget *channelInfoWidget, channelInfoWidgets)
	{
		newIndices.push_back(channelInfoWidget->newBox->currentIndex());
		directions.push_back(channelInfoWidget->directionBox->currentIndex());
		sepSortLayout->removeWidget(channelInfoWidget);
		delete channelInfoWidget;
	}
	channelInfoWidgets.clear();

	channelInfo["newIndices"] = newIndices;
	channelInfo["directions"] = directions;
}

void Setup::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape)
	{
		this->hide();
	}
}

void Setup::addPump()
{
	AddPumpDialog dialog(this);
	if (dialog.exec())
	{
		QTreeWidgetItem *p, *c;

		// count existing 
		int numPump = pumpTree->topLevelItemCount();
		int numTransducer = 0;
		for (int i = 0; i < numPump; i++)
		{
			p = pumpTree->topLevelItem(i);
			numTransducer += p->childCount();
		}

		// add new
		p = new QTreeWidgetItem(pumpTree);
		QString pumpType = dialog.pumpTypeCombo->currentText();
		QString pumpSn = dialog.pumpSnEdit->text();
		QString limit;
		if (pumpType == "ez")
		{
			limit.setNum(2000);
		}
		else if (pumpType == "8c")
		{
			limit.setNum(1000);
		}
		p->setText(0, pumpType);
		p->setText(1, pumpSn);
		for (int i = 0; i < dialog.numTransducerSpin->value(); i++)
		{
			QString pstr;
			QString cstr;
			c = new QTreeWidgetItem(p);
			c->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);
			c->setText(0, pstr.setNum(numPump));
			c->setText(1, cstr.setNum(i+1));
			c->setText(2, cstr.setNum(numTransducer + i));
			c->setText(3, limit);
		}
		
		// show
		pumpTree->expandItem(p);
	}
}

void Setup::clearPump()
{
	while (int numItem = pumpTree->topLevelItemCount())
	{
		delete pumpTree->takeTopLevelItem(numItem - 1);
	}
}
