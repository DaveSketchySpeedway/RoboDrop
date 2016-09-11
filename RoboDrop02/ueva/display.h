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

#ifndef DISPLAY_H
#define DISPLAY_H

#include <QtGui > 
#include <QWidget >

#include "uevastructures.h"

class Display : public QWidget
{
	Q_OBJECT
public:
	Display(QWidget *parent);
	~Display();

	//// REGULAR CALLS
	void setImage(const QImage &i);
	QPoint getMousePosition(); // return instantaneous mouse position
	QPoint getLeftPress(); // return point if there is left click since last get
	QPoint getRightPress(); // return point if there is right click since last get
	QLine getLeftPressMovement(); // return line start at last get

signals:
	void sendMouseLine(QLine line); // send line start at button press
	
protected:
	void mousePressEvent(QMouseEvent *event); // used by cut and calib
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event); // used by cut and calib
	void paintEvent(QPaintEvent *event);

private:
	QImage image;

	bool leftPressed;
	bool lastLeftPressed;
	QPoint mousePosition;
	QPoint lastMousePosition;
	QPoint lineStartPosition;
	QPoint lineEndPosition;
	QPoint leftPressPosition;
	QPoint rightPressPosition;

	private slots:

};

#endif
