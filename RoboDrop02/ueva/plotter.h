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

#ifndef PLOTTER_H
#define PLOTTER_H

#include <QtGui >
#include <QDialog>
#include <cstdlib>
#include <time.h>

#include "ui_plotter.h"
#include "uevastructures.h"

class Plotter : public QWidget, public Ui_Plotter
{
	Q_OBJECT

public:
	Plotter(QWidget *parent = 0);
	~Plotter();

	void setPlot(const UevaBuffer &b);

signals:

protected:
	void keyPressEvent(QKeyEvent *event);

private:
	QVector<QColor> colors;
	QVector<Qt::PenStyle> penStyles;
	QVector<QString> penStyleTexts;

	private slots:

};

#endif // PLOTTER_H
