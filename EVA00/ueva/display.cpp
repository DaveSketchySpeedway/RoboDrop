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

#include "display.h"

Display::Display(QWidget *parent)
	: QWidget(parent)
{
	setMouseTracking(true);

	leftPressed = false;
	lastLeftPressed = false;
	mousePosition = QPoint(0, 0);
	lastMousePosition = QPoint(0, 0);
	lineStartPosition = QPoint(0, 0);
	lineEndPosition = QPoint(0, 0);
	leftPressPosition = QPoint(0, 0);
	rightPressPosition = QPoint(0, 0);

	connect(this, SIGNAL(sendMouseLine(QLine)),
		parent, SLOT(receiveMouseLine(QLine)));

	QLine line = QLine(lineStartPosition, lineEndPosition);
	emit sendMouseLine(line);
}

Display::~Display()
{

}

//// REGULAR CALLS
void Display::setImage(const QImage &i)
{
	image = i;
}

QPoint Display::getMousePosition()
{
	return mousePosition;
}

QPoint Display::getLeftPress()
{
	QPoint lpp = leftPressPosition;
	leftPressPosition = QPoint(0, 0);
	return lpp;
}

QPoint Display::getRightPress()
{
	QPoint rpp = rightPressPosition;
	rightPressPosition = QPoint(0, 0);
	return rpp;
}

QLine Display::getLeftPressMovement()
{
	QLine movement = QLine(0, 0, 0, 0);
	if (leftPressed && lastLeftPressed)
	{
		movement = QLine(lastMousePosition, mousePosition);
	}
	lastMousePosition = mousePosition;
	lastLeftPressed = leftPressed;
	return movement;
}

//// EVENTS

void Display::mousePressEvent(QMouseEvent *event)
{
	mousePosition = event->pos();
	leftPressed = false;

	if (event->button() & Qt::LeftButton)
	{
		leftPressed = true;
		lineStartPosition = event->pos();
		leftPressPosition = event->pos();
	}
	if (event->button() & Qt::RightButton)
	{
		rightPressPosition = event->pos();
	}
	update();
}

void Display::mouseMoveEvent(QMouseEvent *event)
{
	mousePosition = event->pos();
	leftPressed = false;

	if (event->buttons() & Qt::LeftButton) // must use buttons() instead of button()
	{
		leftPressed = true;
		lineEndPosition = event->pos();
	}
	//update(); 
	// cost up to 50ms in GUI when moving mouse
	// jam up gui so much that timer event will be delayed
	// engine duty cycle will appear to spike, but not actually when timed inside thread
	// relies on gui timer (10hz default) to update mouse movement
}

void Display::mouseReleaseEvent(QMouseEvent *event)
{
	mousePosition = event->pos();
	leftPressed = false;

	if (event->button() & Qt::LeftButton)
	{
		leftPressed = false;
		lineEndPosition = event->pos();
		
		QLine line = QLine(lineStartPosition, lineEndPosition);
		emit sendMouseLine(line);
	}
	update();
}

void Display::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawImage(0, 0, image);
	painter.setPen(QPen(Qt::green, 3));
	painter.drawLine(lineStartPosition, lineEndPosition);
}

