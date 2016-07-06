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

#ifndef PLOTTER_H
#define PLOTTER_H

#include <QtGui >
#include <QDialog>
#include <cstdlib>
#include <time.h>

#include "ui_plotter.h"
#include "structures.h"

class Plotter : public QWidget, public Ui_Plotter
{
	Q_OBJECT

public:
	Plotter(QWidget *parent = 0);
	~Plotter();

	void setPlot(const UevaBuffer &b);

signals:

protected:

private:
	QVector<QColor> colors;
	QVector<Qt::PenStyle> penStyles;
	QVector<QString> penStyleTexts;

	private slots:

};

#endif // PLOTTER_H
