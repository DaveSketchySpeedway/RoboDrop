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

#include "mainwindow.h"

MainWindow::MainWindow()
{
	//// INITIALIZE VARIABLES
	timerInterval = 100; // ms
	settings = UevaSettings();
	dataId = qRegisterMetaType<UevaData>();
	buffer = UevaBuffer();
	guiFlag = DRAW_DEFAULT | DRAW_PLOT;
	qImage = QImage(0, 0, QImage::Format_Indexed8);

	//// INITIALIZE GUI
	setWindowIcon(QIcon("icon/eva_icon.png"));
	setAttribute(Qt::WA_QuitOnClose);
	setMinimumSize(800, 800);

	display = new Display(this);
	setCentralWidget(display);

	setup = new Setup(this);
	dashboard = new Dashboard(this);
	plotter = new Plotter(this);

	createActions();
	createMenus();
	createContextMenu();
	createToolBars();
	createStatusBar();

	createThreads();
	updateStatusBar();
	setCurrentFile("");
	showMaximized();
	readSettings();

	startTimers();
}

MainWindow::~MainWindow()
{

}

void MainWindow::cameraOnOff()
{
	if (dashboard->cameraButton->isChecked())
	{
		dashboard->cameraButton->setText(tr("Off"));
		guiFlag |= CAMERA_ON;
		cameraThread->startCamera( (int)(timerInterval/1000) );
	}
	else
	{
		dashboard->cameraButton->setText(tr("On"));
		guiFlag ^= CAMERA_ON;
		cameraThread->stopCamera();
		// qImage to cvMat
	}
}

void MainWindow::recordDataOnOff()
{
	if (dashboard->recordDataButton->isChecked())
	{
		dashboard->recordDataButton->setText(tr("Off"));
		guiFlag |= RECORD_DATA;
	}
	else
	{
		dashboard->recordDataButton->setText(tr("On"));
		UevaData::fileStream.close();
		guiFlag ^= RECORD_DATA;
	}
}

void MainWindow::recordRawOnOff()
{
	if (dashboard->recordRawButton->isChecked())
	{
		dashboard->recordRawButton->setText(tr("Off"));
		guiFlag |= RECORD_RAW;
	}
	else
	{
		dashboard->recordRawButton->setText(tr("On"));
		guiFlag ^= RECORD_RAW;
	}
}

void MainWindow::recordDisplayOnOff()
{
	if (dashboard->recordDisplayButton->isChecked())
	{
		dashboard->recordDisplayButton->setText(tr("Off"));
		guiFlag |= RECORD_DISPLAY;
	}
	else
	{
		dashboard->recordDisplayButton->setText(tr("On"));
		guiFlag ^= RECORD_DISPLAY;
	}
}

void MainWindow::pumpOnOff()
{
	if (dashboard->pumpButton->isChecked())
	{
		dashboard->pumpButton->setText(tr("Off"));
		settings.flag |= UevaSettings::PUMP_ON;
	}
	else
	{
		dashboard->pumpButton->setText(tr("On"));
		settings.flag ^= UevaSettings::PUMP_ON;
	}
}

void MainWindow::connectCamera()
{
	if (setup->connectCameraButton->isChecked())
	{
		setup->connectCameraButton->setText(tr("Disconnect"));
		//// new camera
		cameraThread->addCamera();
		//// erase settings
		while (int numItem = setup->cameraTree->topLevelItemCount())
		{
			delete setup->cameraTree->takeTopLevelItem(numItem - 1);
		}
		//// default setting
		QMapIterator<QString, QString> d (cameraThread->defaultSettings());
		QTreeWidgetItem *p;
		d.toFront();
		while (d.hasNext())
		{
			d.next();
			p = new QTreeWidgetItem(setup->cameraTree);
			p->setText(0, d.key());
			p->setText(1, d.value());
			p->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);
		}
	}
	else
	{
		setup->connectCameraButton->setText(tr("Connect"));
		//// delete camera
		cameraThread->deleteCamera();
		//// erase settings
		while (int numItem = setup->cameraTree->topLevelItemCount())
		{
			delete setup->cameraTree->takeTopLevelItem(numItem - 1);
		}
	}
}

void MainWindow::getCamera()
{
	//// erase settings
	while (int numItem = setup->cameraTree->topLevelItemCount())
	{
		delete setup->cameraTree->takeTopLevelItem(numItem - 1);
	}
	//// get settings
	QMapIterator<QString, QString> s(cameraThread->getSettings());
	QTreeWidgetItem *p;
	s.toFront();
	while (s.hasNext())
	{
		s.next();
		p = new QTreeWidgetItem(setup->cameraTree);
		p->setText(0, s.key());
		p->setText(1, s.value());
		p->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
}

void MainWindow::setCamera()
{
	// extract settings from tree
	QMap<QString, QString> s;
	for (int i = 0; i < setup->cameraTree->topLevelItemCount(); i++)
	{
		QTreeWidgetItem *p;
		p = setup->cameraTree->topLevelItem(i);
		s[p->text(0)] = p->text(1);
	}
	//// set settings
	cameraThread->setSettings(s);
}

void MainWindow::getPump()
{

}

void MainWindow::setPump()
{
	QTreeWidgetItem *p, *c;

	//// CLEAR
	// delete pump
	pumpThread->deletePumps();

	// erase settings
	settings.inletInfo.clear();
	settings.inletRequests.clear();

	//// NEW
	for (int i = 0; i < setup->pumpTree->topLevelItemCount(); i++)
	{
		// pump tree 
		p = setup->pumpTree->topLevelItem(i);
		int ez = 0;
		if (p->text(0) == "ez")
			ez = 1;
		int sn = p->text(1).toInt();
		pumpThread->addPump(sn, ez);

		for (int j = 0; j < p->childCount(); j++)
		{
			c = p->child(j);
			QVector<int> d;
			d.push_back(c->text(0).toInt());
			d.push_back(c->text(1).toInt());
			d.push_back(c->text(2).toInt());
			d.push_back(c->text(3).toInt());
			settings.inletInfo.push_back(d);
			settings.inletRequests.push_back(0.0);
		}
	}

	// sort inlet info
	sort(settings.inletInfo.begin(), settings.inletInfo.end(),
		[](const QVector<int>& a, const QVector<int>& b)
	{
		return a[2] < b[2];
	}); 

	// reset inlet wigets
	dashboard->resetInletWidgets(settings.inletInfo);
}

void MainWindow::receiveInletRequests(
	const QVector<qreal> &values)
{
	settings.inletRequests = values;
}

void MainWindow::imgprocOnOff()
{
	if (dashboard->imgprocButton->isChecked())
	{
		dashboard->imgprocButton->setText(tr("Off"));
		settings.flag |= UevaSettings::IMGPROC_ON;
	}
	else
	{
		dashboard->imgprocButton->setText(tr("On"));
		settings.flag ^= UevaSettings::IMGPROC_ON;
	}
}

void MainWindow::ctrlOnOff()
{
	if (dashboard->ctrlButton->isChecked())
	{
		dashboard->ctrlButton->setText(tr("Off"));
		settings.flag |= UevaSettings::CTRL_ON;
	}
	else
	{
		dashboard->ctrlButton->setText(tr("On"));
		settings.flag ^= UevaSettings::CTRL_ON;
	}
}

void MainWindow::timerEvent(QTimerEvent *event)
{
	
	if (event->timerId() == timerId)
	{
		//// PING
		QTime now = QTime::currentTime();
		pingTimeStamps.enqueue(now);
		
		//// INTERUPT CAMERA THREAD
		if (guiFlag & CAMERA_ON)
		{
			cameraThread->getCurrentImage(cvMat);
			qDebug() << cvMat.total() << " " <<
				cvMat.type() << " " << // 0 means CV_8U
				cvMat.rows << " " <<
				cvMat.cols << " " <<
				cvMat.isContinuous() << endl;;
		}

		//// WAKE ENGINE THREAD
		UevaData data = UevaData();
		//data.rawImage = cvMat.clone(); // deep copy, cost 7ms seconds for 1x1
		data.rawImage = cvMat; // shallow copy, screwed if engine last more than interval
		engineThread->setSettings(settings); 
		engineThread->setData(data);
		engineThread->wake();

		//// ENGINE THREAD FPS
		now = QTime::currentTime();
		engineFps = 1000.0 / engineLastTime.msecsTo(now);
		engineLastTime = now;
	}
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (noUnsavedFile())
	{
		writeSettings();
		event->accept(); // doesn't work
	}
	else
	{
		event->ignore(); // doesn't work
	}
}

void MainWindow::createActions()
{
	clearAction = new QAction(tr("&Clear"), this);
	clearAction->setIcon(QIcon("icon/clear.png"));
	clearAction->setShortcut(tr("Ctrl+W"));
	clearAction->setStatusTip(tr("Clear File"));
	connect(clearAction, SIGNAL(triggered()),
		this, SLOT(clear()));

	openAction = new QAction(tr("&Open"), this);
	openAction->setIcon(QIcon("icon/open.png"));
	openAction->setShortcut(tr("Ctrl+O"));
	openAction->setStatusTip(tr("Open an existing file"));
	connect(openAction, SIGNAL(triggered()),
		this, SLOT(open()));

	saveAction = new QAction(tr("&Save"), this);
	saveAction->setIcon(QIcon("icon/save.png"));
	saveAction->setShortcut(tr("Ctrl+S"));
	saveAction->setStatusTip(tr("Save file"));
	connect(saveAction, SIGNAL(triggered()), 
		this, SLOT(save()));

	saveAsAction = new QAction(tr("Save As"), this);
	saveAsAction->setShortcut(tr("Ctrl+Shift+S"));
	saveAsAction->setStatusTip(tr("Save as new file"));
	connect(saveAsAction, SIGNAL(triggered()), 
		this, SLOT(saveAs()));

	exitAction = new QAction(tr("E&xit"), this);
	exitAction->setIcon(QIcon("icon/exit.png"));
	exitAction->setShortcut(tr("Ctrl+Q"));
	exitAction->setStatusTip(tr("Exit the application"));
	connect(exitAction, SIGNAL(triggered()),
		this, SLOT(close()));

	aboutAction = new QAction(tr("&About"), this);
	aboutAction->setStatusTip(tr("Show App information"));
	connect(aboutAction, SIGNAL(triggered()),
		this, SLOT(about()));

	setupAction = new QAction(tr("show &Setup"), this);
	setupAction->setIcon(QIcon("icon/setup.png"));
	setupAction->setShortcut(tr("Alt+S"));
	setupAction->setStatusTip(tr("Setup application"));
	setupAction->setCheckable(true);
	setupAction->setChecked(false);
	connect(setupAction, SIGNAL(triggered()),
		this, SLOT(showAndHideSetup()));

	dashboardAction = new QAction(tr("show &Dashboard"), this);
	dashboardAction->setIcon(QIcon("icon/dashboard.png"));
	dashboardAction->setShortcut(tr("Alt+D"));
	dashboardAction->setStatusTip(tr("Operate application"));
	//dashboardAction->setCheckable(true);
	//dashboardAction->setChecked(false);
	connect(dashboardAction, SIGNAL(triggered()),
		this, SLOT(showAndHideDashboard()));

	plotterAction = new QAction(tr("show &Plotter"), this);
	plotterAction->setIcon(QIcon("icon/plotter.png"));
	plotterAction->setShortcut(tr("Alt+P"));
	plotterAction->setStatusTip(tr("Plot data"));
	//plotterAction->setCheckable(true);
	//plotterAction->setChecked(false);
	connect(plotterAction, SIGNAL(triggered()),
		this, SLOT(showAndHidePlotter()));


	contourAction = new QAction(tr("draw &Contour"), this);
	//contourAction->setIcon(QIcon("icon/contour.png"));
	contourAction->setStatusTip(tr("Draw detected contours"));
	contourAction->setCheckable(true);
	contourAction->setChecked(false);
	connect(contourAction, SIGNAL(triggered()),
		this, SLOT(showAndHideContour()));

	neckAction = new QAction(tr("draw &Neck"), this);
	//neckAction->setIcon(QIcon("icon/neck.png"));
	neckAction->setStatusTip(tr("Draw detected necks"));
	neckAction->setCheckable(true);
	neckAction->setChecked(false);
	connect(neckAction, SIGNAL(triggered()),
		this, SLOT(showAndHideNeck()));

	markerAction = new QAction(tr("draw &Marker"), this);
	//markerAction->setIcon(QIcon("icon/marker.png"));
	markerAction->setStatusTip(tr("Draw all detected markers"));
	markerAction->setCheckable(true);
	markerAction->setChecked(false);
	connect(markerAction, SIGNAL(triggered()),
		this, SLOT(showAndHideMarker()));

	useRefAction = new QAction(tr("use as Reference"), this);
	useRefAction->setStatusTip(tr("Use this marker as reference"));

	dropRefAction = new QAction(tr("drop Reference"), this);
	dropRefAction->setStatusTip(tr("Drop this reference"));
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File")); 
	fileMenu->addAction(clearAction);
	fileMenu->addAction(openAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(saveAsAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	viewMenu = menuBar()->addMenu(tr("&View"));
	viewMenu->addAction(setupAction);
	viewMenu->addAction(dashboardAction);
	viewMenu->addAction(plotterAction);
	viewMenu->addSeparator();
	visibilitySubMenu = viewMenu->addMenu(tr("&Visibility"));
	visibilitySubMenu->addAction(contourAction);
	visibilitySubMenu->addAction(neckAction);
	visibilitySubMenu->addAction(markerAction);

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAction);
}

void MainWindow::createContextMenu()
{
	display->addAction(useRefAction);
	display->addAction(dropRefAction);
	display->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createToolBars()
{
	visibilityToolBar = addToolBar(tr("&Visibility"));	
	visibilityToolBar->addAction(contourAction);
	visibilityToolBar->addAction(neckAction);
	visibilityToolBar->addAction(markerAction);
	visibilityToolBar->addSeparator();
}

void MainWindow::createStatusBar()
{
	engineFpsLabel = new QLabel;
	engineDutyCycleLabel = new QLabel;
	pumpFpsLabel = new QLabel;
	pumpDutyCycleLabel = new QLabel;
	pingLabel = new QLabel;
	mousePositionLabel = new QLabel;

	statusBar()->addWidget(engineFpsLabel,1);
	statusBar()->addWidget(engineDutyCycleLabel,1);
	statusBar()->addWidget(pumpFpsLabel,1);
	statusBar()->addWidget(pumpDutyCycleLabel,1);
	statusBar()->addWidget(pingLabel,1);
	statusBar()->addWidget(mousePositionLabel,1);
}

void MainWindow::createThreads()
{
	cameraThread = new CameraThread();
	engineThread = new S2EngineThread();
	pumpThread = new PumpThread();

	cameraThread->start();
	engineThread->start();
	pumpThread->start();

	connect(engineThread, 
		SIGNAL(engineSignal(const UevaData &)),
		this, 
		SLOT(engineSlot(const UevaData &)),
		Qt::QueuedConnection);

	connect(pumpThread,
		SIGNAL(pumpSignal(const UevaData &)),
		this,
		SLOT(pumpSlot(const UevaData &)),
		Qt::QueuedConnection);

}

void MainWindow::startTimers()
{
	QTime now = QTime::currentTime();

	timerId =
		startTimer(timerInterval, Qt::PreciseTimer);

	engineLastTime = now;
	pumpLastTime = now;
}

bool MainWindow::noUnsavedFile()
{
	if (isWindowModified())
	{
		int r = QMessageBox::warning(this,
			tr("Unsaved Changes"),
			tr("Document has been modified.\n"
				"Do you want to save the changes?"),
			QMessageBox::Yes | QMessageBox::Default,
			QMessageBox::No,
			QMessageBox::Cancel | QMessageBox::Escape);
		// set parent so message box appear at center
		// QFileDialog::DontConfirmOverwrite
		if (r == QMessageBox::Yes)
		{
			return save();
		}
		else if (r == QMessageBox::Cancel)
		{
			return false;
		}
	}
	return true;
}

bool MainWindow::loadFile(const QString &fileName)
{

	if (!qImage.load(fileName)) 
	{
		statusBar()->showMessage(tr("Loading canceled"), 2000);
		return false;
	}
	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File loaded"), 2000);
	return true;
}

bool MainWindow::saveFile(const QString &fileName)
{
	if (!qImage.save(fileName))
	{
		statusBar()->showMessage(tr("Saving canceled"), 2000);
		return false;
	}
	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File saved"), 2000);
	return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
	currentFile = fileName;
	QString shownName = "Untitled";
	if (!fileName.isEmpty())
	{
		shownName = QFileInfo(fileName).fileName();
	}
	setWindowTitle(tr("%1 - %2[*]")
		.arg(tr("uEVA"))
		.arg(shownName));
	setWindowModified(false);
}

void MainWindow::writeSettings()
{
	QSettings settings("DaveSketchySpeedway", "uEVA");
	settings.setValue("nothing", QVariant("1"));

}

void MainWindow::readSettings() 
{
	QSettings settings("DaveSketchySpeedway", "uEVA");
	int i = settings.value("nothing", QVariant("0")).toInt();

}

void MainWindow::clear()
{
	if (noUnsavedFile())
	{
		qImage = QImage(0, 0, QImage::Format_Indexed8);
		setCurrentFile("");
	}
}

void MainWindow::open()
{
	if (noUnsavedFile())
	{
		QString fileName = QFileDialog::getOpenFileName(this,
			tr("Open Image"), ".",
			tr("png (*.png)\n"
			"jpeg (*.jpg)\n"
			"all files (*.*)"));
		// set parent so file dialog appear at center
		if (!fileName.isEmpty())
			loadFile(fileName);
	}
}

bool MainWindow::save()
{
	if (currentFile.isEmpty())
	{
		return saveAs();
	}
	else
	{
		return saveFile(currentFile);
	}
}

bool MainWindow::saveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save"), ".",
		tr("png (*.png)\n"
		"jpeg (*.jpg)\n"
		"all files (*.*)"));
	// set parent so message box appear at center
	if (fileName.isEmpty())
		return false;
	return saveFile(fileName);
}

void MainWindow::about()
{
	QMessageBox::about(this,
		tr("About"),
		tr("<h2> uEVA-01</h2>"
		"<p>Microfluidics Enhanced Vison-based Automation"
		" https://github.com/DaveSketchySpeedway/uEVA"
		"<p>Copyright &copy; 2016 David Wong"
		"<p>This program is free software: you can redistribute it and/or modify"
		"it under the terms of the GNU General Public License as published by"
		"the Free Software Foundation, either version 3 of the License, or"
		"any later version."
		"<p>This program is distributed in the hope that it will be useful,"
		"but WITHOUT ANY WARRANTY; without even the implied warranty of"
		"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the"
		"GNU General Public License for more details."
		"<p>You should have received a copy of the GNU General Public License"
		"along with this program. If not, see http://www.gnu.org/licenses/."
		));
}

void MainWindow::updateStatusBar()
{
	QPoint mousePosition = display->getMousePosition();
	engineFpsLabel->setText(tr("Engine FPS: %1")
		.arg(QString::number(engineFps)));
	engineDutyCycleLabel->setText(tr("Engine Duty Cycle: %1")
		.arg(QString::number(engineDutyCycle)));
	pumpFpsLabel->setText(tr("Pump FPS: %1")
		.arg(QString::number(pumpFps)));
	pumpDutyCycleLabel->setText(tr("Pump Duty Cycle: %1")
		.arg(QString::number(pumpDutyCycle)));
	pingLabel->setText(tr("Ping: %1")
		.arg(QString::number(ping)));
	mousePositionLabel->setText(tr("X: %1	Y: %2")
		.arg(QString::number(mousePosition.x()))
		.arg(QString::number(mousePosition.y())));
}

void MainWindow::showAndHideSetup()
{
	setup->show(); 
	setup->activateWindow();
}

void MainWindow::showAndHideDashboard()
{
	dashboard->show(); 
	dashboard->activateWindow();
}

void MainWindow::showAndHidePlotter()
{
	plotter->showMaximized();
	plotter->activateWindow();
}

void MainWindow::showAndHideContour()
{
	if (contourAction->isChecked())
		guiFlag |= DRAW_CONTOUR;
	else
		guiFlag ^= DRAW_CONTOUR;
}

void MainWindow::showAndHideNeck()
{
	if (neckAction->isChecked())
		guiFlag |= DRAW_NECK;
	else
		guiFlag ^= DRAW_NECK;
}

void MainWindow::showAndHideMarker()
{
	if (markerAction->isChecked())
		guiFlag |= DRAW_MARKER;
	else
		guiFlag ^= DRAW_MARKER;
}

void MainWindow::engineSlot(const UevaData &data)
{
	//// ENGINE THREAD DUTY CYCLE
	QTime now = QTime::currentTime();
	engineDutyCycle = double(engineLastTime.msecsTo(now))/
		double(timerInterval);

	//// WAKE PUMP THREAD
	pumpThread->setSettings(settings);
	pumpThread->setData(data);
	pumpThread->wake();

	//// UPDATE DISPLAY
	// data.rawImage to qImage
	display->setImage(qImage);
	// display set data
	display->update();
	
	//// PUMP THREAD FPS
	now = QTime::currentTime();
	pumpFps = 1000.0 / pumpLastTime.msecsTo(now);
	pumpLastTime = now;
}

void MainWindow::pumpSlot(const UevaData &data)
{
	//// PUMPTHREAD DUTY CYCLE
	QTime now = QTime::currentTime();
	pumpDutyCycle = double(pumpLastTime.msecsTo(now)) /
		double(timerInterval);

	//// WRITE BUFFER
	buffer.write(data);

	//// UPDATE PLOT
	plotter->setPlot(buffer);
	plotter->plot->update();

	//// RECORD
	if (guiFlag & RECORD_DATA)
	{
		if (!UevaData::fileStream.is_open()) // first time
		{
			QDateTime now = QDateTime::currentDateTime();
			QString filename = "record/ueva_data_";
			filename.append(now.toString("yyyy_MM_dd_HH_mm_ss"));
			filename.append(".csv");
			UevaData::fileStream.open(filename.toStdString());
			UevaData::startTime = now.time();
			data.headerToFile();
		}
		data.writeToFile();
	}

	//// PONG
	if (!pingTimeStamps.isEmpty())
	{
		now = QTime::currentTime();
		ping = pingTimeStamps.dequeue().msecsTo(now);
	}

	//// STATUS
	updateStatusBar();
	setWindowModified(true);
}



