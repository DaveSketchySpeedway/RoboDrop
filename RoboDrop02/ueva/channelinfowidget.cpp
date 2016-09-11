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

#include "channelinfowidget.h"

ChannelInfoWidget::ChannelInfoWidget(int id, int numChan, QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

	oldLabel->setText(QString::number(id));

	for (int i = 0; i < numChan; i++)
	{
		newBox->insertItem(i, QString::number(i));
	}
	newBox->setCurrentIndex(id);

	directionBox->insertItem(0, "^");
	directionBox->insertItem(1, "v");
	directionBox->insertItem(2, "<");
	directionBox->insertItem(3, ">");
	directionBox->setCurrentIndex(0);


}


