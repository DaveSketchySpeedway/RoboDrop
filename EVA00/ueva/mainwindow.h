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



#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtGui >
#include <QMainWindow >
#include <QMenuBar >
#include <QToolBar >
#include <QStatusBar >
#include <QMenu >
#include <QAction >
#include <QWidget >
#include <QLabel >
#include <QFileDialog >
#include <QMessageBox >
#include <QTime >
#include <QThread >
#include <QMutex >
#include <QPainter >
#include <algorithm>
#include <fstream>
#include "opencv2/core.hpp"

#include "setup.h"
#include "dashboard.h"
#include "plotter.h"
#include "display.h"
#include "camerathread.h"
#include "s2enginethread.h"
#include "pumpthread.h"
#include "uevastructures.h"

using namespace std;
using namespace cv;

class MainWindow : public QMainWindow
{
	Q_OBJECT;

public:
	MainWindow();
	~MainWindow();

	public slots:
	//// COMMUNICATE WITH SUBWINDOW
	void cameraOnOff();
	void recordDataOnOff();
	void recordRawOnOff();
	void recordDisplayOnOff();
	void pumpOnOff();
	void connectCamera();
	void getCamera();
	void setCamera();
	void getPump();
	void setPump();
	void receiveInletRequests(const QVector<qreal> &values);
	void imgprocOnOff();
	void ctrlOnOff();

signals:
	

protected:
	//// REIMPLEMENTATION
	void timerEvent(QTimerEvent *event);
	void closeEvent(QCloseEvent *event);

private:
	//// CONSTRUCTOR FUNCTIONS
	void createActions();
	void createMenus();
	void createContextMenu();
	void createToolBars();
	void createStatusBar();
	void createThreads();
	void startTimers();

	//// FUNCTIONS
	bool noUnsavedFile(); // check if image is unsaved
	bool loadFile(const QString &filename); // write image to file
	bool saveFile(const QString &filename); // read image from file
	void setCurrentFile(const QString &filename); // keep track of current image file and update title
	void readSettings();
	void writeSettings(); 
	
	//// MEMBER
	QString currentFile;

	int timerInterval; // sampling period right here
	int timerId;

	QTime engineLastTime;
	QTime pumpLastTime;

	double engineFps;
	double pumpFps;

	double engineDutyCycle;
	double pumpDutyCycle;

	QQueue<QTime> pingTimeStamps;
	int ping;

	CameraThread *cameraThread;
	S2EngineThread *engineThread;
	PumpThread *pumpThread;

	UevaSettings settings;
	int dataId;
	UevaBuffer buffer;

	Mat cvMat;
	QImage qImage;

	enum FlagValues
	{
		DRAW_DEFAULT = 1,
		DRAW_PLOT = 2,
		DRAW_CONTOUR = 4,
		DRAW_NECK = 8,
		DRAW_MARKER = 16,
		RECORD_DATA = 32,
		RECORD_RAW = 64,
		RECORD_DISPLAY = 128,
		CAMERA_ON = 256,
	};
	int guiFlag;


	//// NON MODAL SUBWINDOW
	Setup *setup;
	Dashboard *dashboard;
	Plotter *plotter;

	//// CHILD WIDGETS
	Display *display;
	
	QLabel *engineFpsLabel;
	QLabel *engineDutyCycleLabel;
	QLabel *pumpFpsLabel;
	QLabel *pumpDutyCycleLabel;
	QLabel *pingLabel;
	QLabel *mousePositionLabel;

	QMenu *fileMenu;
	QMenu *viewMenu;
	QMenu *helpMenu;
	QMenu *visibilitySubMenu;

	QToolBar *visibilityToolBar;

	QAction *clearAction;
	QAction *openAction;
	QAction *saveAction;
	QAction *saveAsAction;
	QAction *exitAction;
	QAction *aboutAction;
	QAction *setupAction;
	QAction *dashboardAction;
	QAction *plotterAction;
	QAction *contourAction;
	QAction *neckAction;
	QAction *markerAction;
	QAction *useRefAction;
	QAction *dropRefAction;

	private slots:
	//// TRIGGERED BY ACTIONS
	void clear(); // check unsave and close image file
	void open(); // check unsave and get open file name dialog
	bool save(); // redirect to save as
	bool saveAs(); // get save file name dialog
	void about();
	void updateStatusBar();
	void showAndHideSetup();
	void showAndHideDashboard();
	void showAndHidePlotter();
	void showAndHideContour();
	void showAndHideNeck();
	void showAndHideMarker();


	//// TRIGGERED BY THREADS
	void engineSlot(const UevaData &data);
	void pumpSlot(const UevaData &data);


};

#endif //MAINWINDOW_H