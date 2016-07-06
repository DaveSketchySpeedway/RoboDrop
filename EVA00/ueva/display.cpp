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

#include "display.h"

Display::Display(QWidget *parent)
	: QWidget(parent)
{
	setMouseTracking(true);

	mousePressed = false;
	mousePosition = QPoint(0, 0);
	lastMousePressed = false;
	lastMousePosition = QPoint(0, 0);
	linePoint1 = QPoint(0, 0);
	linePoint2 = QPoint(0, 0);
}

Display::~Display()
{

}

void Display::setImage(const QImage &image)
{
	displayImage = image;
}

QPoint Display::getMousePosition()
{
	return mousePosition;
}

QLine Display::getMouseLine()
{
	QLine line = QLine(linePoint1, linePoint2);
	return line;
}

QLine Display::getMousePressedMovement()
{
	QLine movement = QLine(0, 0, 0, 0);
	if (mousePressed && lastMousePressed)
	{
		movement = QLine(lastMousePosition, mousePosition);
	}
	lastMousePosition = mousePosition;
	lastMousePressed = mousePressed;
	return movement;
}

void Display::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawImage(0, 0, displayImage);
	painter.setPen(QPen(Qt::green, 3));
	painter.drawLine(linePoint1, linePoint2);
}

void Display::mouseMoveEvent(QMouseEvent *event)
{
	mousePosition = event->pos();
	mousePressed = false;
	if (event->buttons() & Qt::LeftButton)
	{
		linePoint2 = event->pos();
		mousePressed = true;
		update();
	}
}

void Display::mousePressEvent(QMouseEvent *event)
{
	mousePosition = event->pos();
	mousePressed = false;
	if (event->buttons() & Qt::LeftButton)
	{
		linePoint1 = event->pos();
		mousePressed = true;
		update();
	}
}

void Display::mouseReleaseEvent(QMouseEvent *event)
{
	mousePosition = event->pos();
	mousePressed = false;
	if (event->buttons() & Qt::LeftButton)
	{
		linePoint2 = event->pos();
		mousePressed = false;
		update();
	}
}