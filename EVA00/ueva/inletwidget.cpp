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

#include "inletwidget.h"

InletWidget::InletWidget(
	int pumpId, int transducerId, int limit, QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

	label->setText(tr("P%1 T%2")
		.arg(QString::number(pumpId))
		.arg(QString::number(transducerId)));

	slider->setMaximum(limit);
	spinBox->setMaximum(limit);
	
}


