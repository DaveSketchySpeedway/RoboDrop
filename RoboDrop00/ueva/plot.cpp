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

#include "plot.h"

Plot::Plot(QWidget *parent)
	: QWidget(parent)
{
	setBackgroundRole(QPalette::Shadow);
	setAutoFillBackground(true);
	numXTicks = 10;
	numYTicks = 10;
}

Plot::~Plot()
{

}

void Plot::clearData()
{
	data.clear();
}

void Plot::clearColors()
{
	colors.clear();
}

void Plot::clearPenStyles()
{
	penStyles.clear();
}

void Plot::addData(const QVector<qreal> &d)
{
	data.push_back(d);
}

void Plot::addColor(const QColor &c)
{
	colors.push_back(c);
}

void Plot::addPenStyle(const Qt::PenStyle &p)
{
	penStyles.push_back(p);
}

void Plot::setPlotCursor(const int &i)
{
	cursor = i;
}

void Plot::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QPen pen;

	if (data.empty())
	{
		return;
	}

	////// AXIS
	minX = 0;
	maxX = data[0].size();
	minY = *std::min_element(data[0].constBegin(), data[0].constEnd());
	maxY = *std::max_element(data[0].constBegin(), data[0].constEnd());
	foreach(QVector<qreal> d, data)
	{
		qreal newMaxX = d.size();
		qreal newMinY = *std::min_element(d.constBegin(), d.constEnd());
		qreal newMaxY = *std::max_element(d.constBegin(), d.constEnd());
		if (newMaxX > maxX) { maxX = newMaxX; }
		if (newMinY < minY) { minY = newMinY; }
		if (newMaxY > maxY){ maxY = newMaxY; }
	}
	// prevent divide by zero
	minX = floor(minX - 1.0);
	maxX = ceil(maxX + 1.0);
	minY = floor(minY - 1.0);
	maxY = ceil(maxY + 1.0);


	//// GRID
	pen = palette().dark().color();
	painter.setPen(pen);
	QRect rect(MARGIN, MARGIN, width() - 2 * MARGIN, height() - 2 * MARGIN);

	for (int i = 0; i <= numXTicks; i++)
	{
		int x = rect.left() + i*(rect.width()  / numXTicks);
		painter.drawLine(x, rect.top(), x, rect.bottom());
		painter.drawLine(x, rect.bottom(), x, rect.bottom() + 5);
		double label = minX + i* (maxX - minX) / numXTicks;
		painter.drawText(x - 50, rect.bottom() + 5, 100, 15,
			Qt::AlignHCenter | Qt::AlignTop,
			QString::number(label));
	}

	for (int j = 0; j <= numYTicks; ++j)
	{
		int y = rect.bottom() - j*(rect.height() / numYTicks);
		painter.drawLine(rect.left(), y, rect.right(), y);
		painter.drawLine(rect.left() - 5, y, rect.left(), y);
		double label = minY + j*(maxY - minY) / numYTicks;
		painter.drawText(rect.left() - MARGIN, y - 10, MARGIN - 5, 20,
			Qt::AlignRight | Qt::AlignVCenter,
			QString::number(label));
	}

	//// CURVES
	
	//rect.adjust(+1, +1, -1, -1); // x1, y1, x2, y2
	//painter.setViewport(rect.left() + 1, rect.top() + 1,
	//	rect.width() - 2, rect.height() - 2);
	//painter.setWindow(minX, minY,
	//	maxX - minX, maxY - maxY);
	//polyline[j] = QPointF(j, data[i][j]);
	//qDebug() << minX << " " << maxX << " " << minY << " " << maxY;

	for (int i = 0; i < data.size(); i++)
	{
		QPolygonF polyline(data[i].size());
		for (int j = 0; j < data[i].size(); j++)
		{
			double x = (j - minX)/ (maxX - minX)
				* rect.width() + rect.left();
			double y = - (data[i][j] - minY) / (maxY - minY) 
				* rect.height() + rect.bottom();
			polyline[j] = QPointF(x, y);
		}
		pen.setColor(colors[i]);
		pen.setStyle(penStyles[i]);
		pen.setWidth(2);
		painter.setPen(pen);
		painter.drawPolyline(polyline);
	}

	//// CURSOR
	double x = (cursor - minX) / (maxX - minX)
		* rect.width() + rect.left();
	QLine line(x, rect.top(), x, rect.bottom());
	pen.setColor(Qt::red);
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(5);
	painter.setPen(pen);
	painter.drawLine(line);
}

