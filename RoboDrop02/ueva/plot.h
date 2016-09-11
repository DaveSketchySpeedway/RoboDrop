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

#ifndef PLOT_H
#define PLOT_H

#include <QtGui > 
#include <QWidget >
#include <algorithm >
#include <cmath>

class Plot : public QWidget
{
	Q_OBJECT
public:
	Plot(QWidget *parent);
	~Plot();

	void clearData();
	void clearColors();
	void clearPenStyles();
	void addData(const QVector<qreal> &d);
	void addColor(const QColor &c);
	void addPenStyle(const Qt::PenStyle &p);
	void setPlotCursor(const int &i);

signals:


protected:
	void paintEvent(QPaintEvent *event);

private:
	void adjustAxis(qreal &min, qreal &max, int &numTicks);

	QVector<QVector<qreal>> data;
	QVector<QColor> colors;
	QVector<Qt::PenStyle> penStyles;
	int cursor;
	enum { MARGIN = 50 };
	qreal minX;
	qreal maxX;
	int numXTicks;
	qreal minY;
	qreal maxY;
	int numYTicks;



	private slots:
};

#endif
