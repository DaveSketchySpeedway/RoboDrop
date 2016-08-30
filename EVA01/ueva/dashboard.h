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

#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QtGui >
#include <QDialog>
#include <QCheckBox>
#include "ui_dashboard.h"
#include "inletwidget.h"

class Dashboard : public QWidget, public Ui_Dashboard
{
	Q_OBJECT

public:
	Dashboard(QWidget *parent = 0);
	~Dashboard();

	void resetInletWidgets(QVector<QVector<int>> inletInfo);
	void resetAutoCatchCBoxes(int numChannel);
	void resetUseNeckCBoxes(int numChannel);
	void resetNeckDirectionCBoxes(int numChannel);

	public slots:
	void regurgitateInlets(QVector<qreal> values);

signals:
	void sendInletRequests(const QVector<qreal> &values);
	void sendAutoCatchRequests(const QVector<bool> &values);
	void sendUseNeckRequests(const QVector<bool> &values);
	void sendNeckDirectionRequests(const QVector<bool> &values);

protected:
	void keyPressEvent(QKeyEvent *event);

private:
	QVector<InletWidget*> inletWidgets;
	QVector<qreal> inletValues;
	QVector<QCheckBox*> autoCatchCBoxes;
	QVector<bool> autoCatchValues;
	QVector<QCheckBox*> useNeckCBoxes;
	QVector<bool> useNeckValues;
	QVector<QCheckBox*> neckDirectionCBoxes;
	QVector<bool> neckDirectionValues;

	private slots:
	void zeroInlets();
	void requestInlets();
	void requestAutoCatches();
	void requestUseNecks();
	void requestNeckDirections();
};

#endif // DASHBOARD_H
