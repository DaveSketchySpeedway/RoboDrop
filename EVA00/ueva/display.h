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
	QPoint getMousePosition(); // used by mask picking, ref set
	QLine getMousePressedMovement(); // used by ref update

signals:
	void sendMouseLine(QLine line);
	
protected:
	void mousePressEvent(QMouseEvent *event); // used by cut and calib
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event); // used by cut and calib
	void paintEvent(QPaintEvent *event);

private:
	QImage image;

	bool mousePressed;
	QPoint mousePosition;
	bool lastMousePressed;
	QPoint lastMousePosition;
	QPoint linePoint1;
	QPoint linePoint2;

	private slots:

};

#endif
