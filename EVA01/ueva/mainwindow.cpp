/*
Copyright 2016 David Wong

This file is part of uEVA. https://github.com/DaveSketchySpeedway/uEVA

uEVA is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or 
any later version.

uEVA is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
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

//// COMMUNICATE WITH DASHBOARD
void MainWindow::recordDataOnOff()
{
	if (dashboard->recordDataButton->isChecked())
	{
		dashboard->recordDataButton->setText(tr("Off"));
		settings.flag |= UevaSettings::RECORD_DATA;
	}
	else
	{
		dashboard->recordDataButton->setText(tr("On"));
		UevaData::fileStream.close();
		settings.flag ^= UevaSettings::RECORD_DATA;
	}
}

void MainWindow::recordRawOnOff()
{
	if (dashboard->recordRawButton->isChecked())
	{
		dashboard->recordRawButton->setText(tr("Off"));
		settings.flag |= UevaSettings::RECORD_RAW;
		if (!rawVideoWriter.isOpened())
		{
			QDateTime now = QDateTime::currentDateTime();
			QString filename = "record/ueva_raw_";
			filename.append(now.toString("yyyy_MM_dd_HH_mm_ss"));
			filename.append(".avi");
			double fps = 1.0 / (timerInterval / 1000.0);
			rawVideoWriter = cv::VideoWriter(filename.toStdString(), 
				CV_FOURCC('M', 'S', 'V', 'C'), fps, videoWriterSize, 0);
		}
	}
	else
	{
		dashboard->recordRawButton->setText(tr("On"));
		settings.flag ^= UevaSettings::RECORD_RAW;
		if (rawVideoWriter.isOpened())
		{
			rawVideoWriter.release();
		}
	}
}

void MainWindow::recordDrawnOnOff()
{
	if (dashboard->recordDrawnButton->isChecked())
	{
		dashboard->recordDrawnButton->setText(tr("Off"));
		settings.flag |= UevaSettings::RECORD_DRAWN;
		if (!drawnVideoWriter.isOpened())
		{
			QDateTime now = QDateTime::currentDateTime();
			QString filename = "record/ueva_drawn_";
			filename.append(now.toString("yyyy_MM_dd_HH_mm_ss"));
			filename.append(".avi");
			double fps = 1.0 / (timerInterval / 1000.0);
			drawnVideoWriter = cv::VideoWriter(filename.toStdString(),
				CV_FOURCC('M', 'S', 'V', 'C'), fps, videoWriterSize, 1);
		}
	}
	else
	{
		dashboard->recordDrawnButton->setText(tr("On"));
		settings.flag ^= UevaSettings::RECORD_DRAWN;
		if (drawnVideoWriter.isOpened())
		{
			drawnVideoWriter.release();
		}
	}
}

void MainWindow::recordNeckOnOff()
{
	if (dashboard->recordNeckButton->isChecked())
	{
		dashboard->recordNeckButton->setText(tr("Off"));
		if (!UevaDroplet::fileStream.is_open())
		{
			QDateTime now = QDateTime::currentDateTime();
			QString filename = "record/ueva_neck_";
			filename.append(now.toString("yyyy_MM_dd_HH_mm_ss"));
			filename.append(".csv");
			UevaDroplet::fileStream.open(filename.toStdString());
		}
	}
	else
	{
		dashboard->recordNeckButton->setText(tr("On"));
		if (UevaDroplet::fileStream.is_open())
		{
			UevaDroplet::fileStream.close();
		}
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

void MainWindow::receiveInletRequests(const QVector<qreal> &values)
{
	settings.inletRequests = values;
}

void MainWindow::imgprocOnOff()
{
	if (dashboard->imgprocButton->isChecked())
	{
		dashboard->imgprocButton->setText(tr("Off"));
		settings.flag |= UevaSettings::IMGPROC_ON;
		// initialize
		imgprocSettings();
		ctrlSettings();
		engineThread->initImgproc();
	}
	else
	{
		dashboard->imgprocButton->setText(tr("On"));
		settings.flag ^= UevaSettings::IMGPROC_ON;
		// finalize
		engineThread->finalizeImgproc();
	}
}

void MainWindow::imgprocSettings()
{
	int threshold = dashboard->threshSlider->value();
	int erodeSize = dashboard->erodeSizeSlider->value() * 2 + 1;
	int contourSize = dashboard->contourSizeSlider->value();
	int trackTooFar = dashboard->trackTooFarSlider->value();
	int convexSize = dashboard->convexSizeSlider->value();
	int persistence = dashboard->persistenceSlider->value();

	settings.imgprogThreshold = threshold;
	settings.imgprogErodeSize = erodeSize;
	settings.imgprogContourSize = contourSize;
	settings.imgprogTrackTooFar = trackTooFar;
	settings.imgprocConvexSize = convexSize;
	settings.imgprocPersistence = persistence;

	dashboard->threshLabel->setText(QString::number(threshold));
	dashboard->erodeSizeLabel->setText(QString::number(erodeSize));
	dashboard->contourSizeLabel->setText(QString::number(contourSize));
	dashboard->trackTooFarLabel->setText(QString::number(trackTooFar));
	dashboard->convexSizeLabel->setText(QString::number(convexSize));
	dashboard->persistenceLabel->setText(QString::number(persistence));
}

void MainWindow::ctrlOnOff()
{
	if (dashboard->ctrlButton->isChecked())
	{
		dashboard->ctrlButton->setText(tr("Off"));
		settings.flag |= UevaSettings::CTRL_ON;
		// initialize
		imgprocSettings();
		ctrlSettings();
		engineThread->initCtrl();
	}
	else
	{
		dashboard->ctrlButton->setText(tr("On"));
		settings.flag ^= UevaSettings::CTRL_ON;
		// finalize
		QVector<qreal> inletRegurgitates;
		engineThread->finalizeCtrl(inletRegurgitates);
		dashboard->regurgitateInlets(inletRegurgitates);
	}
}

void MainWindow::ctrlSettings()
{
	int markerSize = dashboard->markerSizeSlider->value();
	int autoHorzExcl = dashboard->autoHorzExclSlider->value();
	int autoVertExcl = dashboard->autoVertExclSlider->value();
	double modelCov = std::pow(10.0, dashboard->modelCovSlider->value() / 10.0);
	double disturbanceCov = std::pow(10.0, dashboard->disturbanceCovSlider->value() / 10.0);
	double disturbanceCorr = dashboard->disturbanceCorrSlider->value() / 1000.0;
	double neckDesire = dashboard->neckDesireSBox->value();
	double neckThreshold = dashboard->neckThresholdSBox->value();
	double neckLowerGain = dashboard->neckLowerGainSBox->value();
	double neckHigherGain = dashboard->neckHigherGainSBox->value();

	settings.ctrlMarkerSize = markerSize;
	settings.ctrlAutoHorzExcl = autoHorzExcl;
	settings.ctrlAutoVertExcl = autoVertExcl;
	settings.ctrlModelCov = modelCov;
	settings.ctrlDisturbanceCov = disturbanceCov;
	settings.ctrlDisturbanceCorr = disturbanceCorr;
	settings.ctrlNeckDesire = neckDesire;
	settings.ctrlNeckThreshold = neckThreshold;
	settings.ctrlNeckLowerGain = neckLowerGain;
	settings.ctrlNeckHigherGain = neckHigherGain;
	
	dashboard->markerSizeLabel->setText(QString::number(markerSize));
	dashboard->autoHorzExclLabel->setText(QString::number(autoHorzExcl));
	dashboard->autoVertExclLabel->setText(QString::number(autoVertExcl));
	dashboard->modelCovLabel->setText(QString::number(modelCov));
	dashboard->disturbanceCovLabel->setText(QString::number(disturbanceCov));
	dashboard->disturbanceCorrLabel->setText(QString::number(disturbanceCorr));
}

void MainWindow::receiveAutoCatchRequests(const QVector<bool> &values)
{
	settings.autoCatchRequests = values;
}

void MainWindow::receiveUseNeckRequests(const QVector<bool> &values)
{
	settings.useNeckRequests = values;
}

void MainWindow::receiveNeckDirectionRequests(const QVector<bool> &values)
{
	settings.neckDirectionRequests = values;
}

//// COMMUNICATE WITH SETUP
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
		QMapIterator<QString, QString> d(cameraThread->defaultSettings());
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

void MainWindow::cameraOnOff()
{
	if (setup->cameraButton->isChecked())
	{
		setup->cameraButton->setText(tr("Off"));
		settings.flag |= UevaSettings::CAMERA_ON;
		cameraThread->startCamera((int)(timerInterval / 1000));
	}
	else
	{
		setup->cameraButton->setText(tr("On"));
		settings.flag ^= UevaSettings::CAMERA_ON;
		cameraThread->stopCamera();
		file8uc1 = cv::Mat(0, 0, CV_8UC1);
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
		}
	}

	// sort inlet info
	std::sort(settings.inletInfo.begin(), settings.inletInfo.end(),
		[](const QVector<int>& a, const QVector<int>& b)
	{
		return a[2] < b[2];
	}); 

	// reset inlet wigets
	dashboard->resetInletWidgets(settings.inletInfo);
}

void MainWindow::setCalib()
{
	double calibLength = setup->calibLengthEdit->text().toDouble();
	engineThread->setCalib(calibLength);
}

void MainWindow::setBkgd()
{
	engineThread->setBkgd();
}

void MainWindow::maskOnOff()
{
	if (setup->maskButton->isChecked())
	{
		setup->maskButton->setText(tr("Done Making Mask"));
		settings.flag |= UevaSettings::MASK_MAKING;
		// initialize in case slider not tempered with
		maskSetup();
	}
	else
	{
		setup->maskButton->setText(tr("Make Mask"));
		settings.flag ^= UevaSettings::MASK_MAKING;
	}
}

void MainWindow::maskSetup()
{
	int threshold = (127 - setup->thresholdSlider->value());
	int block = setup->blockSlider->value() * 2 + 1;
	int openSize = setup->openSizeSlider->value() * 2 + 1;

	settings.maskBlockSize = block;
	settings.maskThreshold = threshold;
	settings.maskOpenSize = openSize;

	setup->blockLabel->setText(QString::number(block));
	setup->thresholdLabel->setText(QString::number(threshold));
	setup->openSizeLabel->setText(QString::number(openSize));
}

void MainWindow::channelOnOff()
{
	if (setup->channelButton->isChecked())
	{
		setup->channelButton->setText(tr("Done Cutting Channels"));
		settings.flag |= UevaSettings::CHANNEL_CUTTING;
		// initialize in case slider not tempered with
		channelSetup();
	}
	else
	{
		setup->channelButton->setText(tr("Cut Channels"));
		settings.flag ^= UevaSettings::CHANNEL_CUTTING;
		// clear in case user don't click on screen in between
		settings.mouseLines.clear();
		QLine line = QLine(0, 0, 0, 0);
		settings.mouseLines.push_back(line);
	}
}

void MainWindow::channelSetup()
{
	int erodeSize = setup->erodeSizeSlider->value() * 2 + 1;
	int cutThickness = setup->cutThicknessSlider->value();

	settings.channelErodeSize = erodeSize;
	settings.channelCutThickness = cutThickness;
	
	setup->erodeSizeLabel->setText(QString::number(erodeSize));
	setup->cutThicknessLabel->setText(QString::number(cutThickness));
}

void MainWindow::sepSortOnOff()
{
	if (setup->sepSortButton->isChecked())
	{
		setup->sepSortButton->setText(tr("Sort Channels"));
		// create channel objects
		int numChan = 0;
		engineThread->separateChannels(numChan);
		// create channel info widgets
		setup->createChannelInfoWidgets(numChan);
	}
	else
	{
		setup->sepSortButton->setText(tr("Separate Channels"));
		// delete channel info widgets
		std::map<std::string, std::vector<int> > channelInfo;
		setup->deleteChannelInfoWidgets(channelInfo);
		// sort channel objects
		engineThread->sortChannels(channelInfo);
		// reset checkboxes
		dashboard->resetAutoCatchCBoxes(channelInfo["newIndices"].size());
		dashboard->resetUseNeckCBoxes(channelInfo["newIndices"].size());
		dashboard->resetNeckDirectionCBoxes(channelInfo["newIndices"].size());
	}
}

void MainWindow::loadCtrl()
{
	QString fileName = QFileDialog::getOpenFileName(setup,
		tr("Load Controller"), "./config",
		tr("YAML (*.yaml)\n"
		"all files (*.*)"));
	// set parent so file dialog appear at center
	if (!fileName.isEmpty())
	{
		int numOut;
		int numIn;
		int numState;
		int numCtrl;
		double ctrlTs;
		engineThread->loadCtrl(fileName.toStdString(),
			&numState, &numIn, &numOut, &numCtrl, &ctrlTs);
		setup->numInLabel->setText(QString::number(numIn));
		setup->numOutLabel->setText(QString::number(numOut));
		setup->numStateLabel->setText(QString::number(numState));
		setup->numCtrlLabel->setText(QString::number(numCtrl));
		setup->ctrlTsLabel->setText(QString::number(ctrlTs));
	}
}

void MainWindow::changeTimerInterval()
{
	// stop timer
	killTimer(timerId);
	// get new interval
	timerInterval = setup->timerIntervalEdit->text().toInt();
	// start new timer
	startTimers();
}

//// COMMUNICATE WITH DISPLAY
void MainWindow::receiveMouseLine(QLine line)
{
	if (settings.flag & UevaSettings::CHANNEL_CUTTING)
	{
		settings.mouseLines.push_back(line);
	}
	else
	{
		settings.mouseLines.clear();
		settings.mouseLines.push_back(line);
	}
}

//// REIMPLEMENTATION
void MainWindow::timerEvent(QTimerEvent *event)
{
	
	if (event->timerId() == timerId)
	{
		//// PING
		QTime now = QTime::currentTime();
		pingTimeStamps.enqueue(now);
		
		//// INTERUPT CAMERA THREAD
		cv::Mat temp8uc1;
		if (settings.flag & UevaSettings::CAMERA_ON)
		{
			cameraThread->getCurrentImage(temp8uc1); // 16uc1 to 8uc1, 1 deep copy
		}
		else
		{
			temp8uc1 = file8uc1.clone(); // 1 deep copy
		}
		videoWriterSize = temp8uc1.size();

		//// COLLECT SETTINGS (SOME ARE ALREADY SET THROUG SIGNAL SLOT)
		settings.rightPressPosition = display->getRightPress();
		settings.leftPressPosition = display->getLeftPress();
		settings.leftPressMovement = display->getLeftPressMovement();

		//// CREATE AN EMPTY DATA STRUCTURE 
		UevaData data = UevaData();
		data.rawGray = temp8uc1;

		//// WAKE ENGINE THREAD
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	if (!event->isAutoRepeat())
	{
		// hide stuff
		if (event->key() == Qt::Key_Escape)
		{
			setup->hide();
			dashboard->hide();
			plotter->hide();
		}
		// channel linking
		switch (event->key())
		{
		case Qt::Key_0:
		{
			if (event->modifiers() == Qt::ControlModifier)
			{
				settings.linkRequests[0] = !settings.linkRequests[0];
				settings.inverseLinkRequests[0] = settings.linkRequests[0];
			}
			else
			{
				settings.linkRequests[0] = !settings.linkRequests[0];
			}
			break;
		}
		case Qt::Key_1:
		{
			if (event->modifiers() == Qt::ControlModifier)
			{
				settings.linkRequests[1] = !settings.linkRequests[1];
				settings.inverseLinkRequests[1] = settings.linkRequests[1];
			}
			else
			{
				settings.linkRequests[1] = !settings.linkRequests[1];
			}
			break;
		}
		case Qt::Key_2:
		{
			if (event->modifiers() == Qt::ControlModifier)
			{
				settings.linkRequests[2] = !settings.linkRequests[2];
				settings.inverseLinkRequests[2] = settings.linkRequests[2];
			}
			else
			{
				settings.linkRequests[2] = !settings.linkRequests[2];
			}
			break;
		}
		case Qt::Key_3:
		{
			if (event->modifiers() == Qt::ControlModifier)
			{
				settings.linkRequests[3] = !settings.linkRequests[3];
				settings.inverseLinkRequests[3] = settings.linkRequests[3];
			}
			else
			{
				settings.linkRequests[3] = !settings.linkRequests[3];
			}
			break;
		}
		case Qt::Key_4:
		{
			if (event->modifiers() == Qt::ControlModifier)
			{
				settings.linkRequests[4] = !settings.linkRequests[4];
				settings.inverseLinkRequests[4] = settings.linkRequests[4];
			}
			else
			{
				settings.linkRequests[4] = !settings.linkRequests[4];
			}
			break;
		}
		case Qt::Key_5:
		{
			if (event->modifiers() == Qt::ControlModifier)
			{
				settings.linkRequests[5] = !settings.linkRequests[5];
				settings.inverseLinkRequests[5] = settings.linkRequests[5];
			}
			else
			{
				settings.linkRequests[5] = !settings.linkRequests[5];
			}
			break;
		}
		case Qt::Key_6:
		{
			if (event->modifiers() == Qt::ControlModifier)
			{
				settings.linkRequests[6] = !settings.linkRequests[6];
				settings.inverseLinkRequests[6] = settings.linkRequests[6];
			}
			else
			{
				settings.linkRequests[6] = !settings.linkRequests[6];
			}
			break;
		}
		case Qt::Key_7:
		{
			if (event->modifiers() == Qt::ControlModifier)
			{
				settings.linkRequests[7] = !settings.linkRequests[7];
				settings.inverseLinkRequests[7] = settings.linkRequests[7];
			}
			else
			{
				settings.linkRequests[7] = !settings.linkRequests[7];
			}
			break;
		}
		case Qt::Key_8:
		{
			if (event->modifiers() == Qt::ControlModifier)
			{
				settings.linkRequests[8] = !settings.linkRequests[8];
				settings.inverseLinkRequests[8] = settings.linkRequests[8];
			}
			else
			{
				settings.linkRequests[8] = !settings.linkRequests[8];
			}
			break;
		}
		case Qt::Key_9:
		{
			if (event->modifiers() == Qt::ControlModifier)
			{
				settings.linkRequests[9] = !settings.linkRequests[9];
				settings.inverseLinkRequests[9] = settings.linkRequests[9];
			}
			else
			{
				settings.linkRequests[9] = !settings.linkRequests[9];
			}
			break;
		}
		}
	}
}

///// CONSTRUCTOR FUNCTIONS
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

	setupAction = new QAction(tr("show Setup"), this);
	setupAction->setIcon(QIcon("icon/setup.png"));
	setupAction->setShortcut(tr("Alt+S"));
	setupAction->setStatusTip(tr("Setup application"));
	setupAction->setShortcutContext(Qt::ApplicationShortcut);
	setupAction->setCheckable(true);
	setupAction->setChecked(false);
	connect(setupAction, SIGNAL(triggered()),
		this, SLOT(showAndHideSetup()));

	dashboardAction = new QAction(tr("show Dashboard"), this);
	dashboardAction->setIcon(QIcon("icon/dashboard.png"));
	dashboardAction->setShortcut(tr("Alt+D"));
	dashboardAction->setShortcutContext(Qt::ApplicationShortcut);
	dashboardAction->setStatusTip(tr("Operate application"));
	//dashboardAction->setCheckable(true);
	//dashboardAction->setChecked(false);
	connect(dashboardAction, SIGNAL(triggered()),
		this, SLOT(showAndHideDashboard()));

	plotterAction = new QAction(tr("show Plotter"), this);
	plotterAction->setIcon(QIcon("icon/plotter.png"));
	plotterAction->setShortcut(tr("Alt+A"));
	plotterAction->setShortcutContext(Qt::ApplicationShortcut);
	plotterAction->setStatusTip(tr("Plot data"));
	//plotterAction->setCheckable(true);
	//plotterAction->setChecked(false);
	connect(plotterAction, SIGNAL(triggered()),
		this, SLOT(showAndHidePlotter()));

	dropletAction = new QAction(tr("draw Droplet"), this);
	//contourAction->setIcon(QIcon("icon/contour.png"));
	dropletAction->setStatusTip(tr("Draw detected droplets"));
	dropletAction->setShortcut(tr("CTRL+Z"));
	dropletAction->setShortcutContext(Qt::ApplicationShortcut);
	dropletAction->setCheckable(true);
	dropletAction->setChecked(false);
	connect(dropletAction, SIGNAL(triggered()),
		this, SLOT(showAndHideDroplet()));

	markerAction = new QAction(tr("draw Marker"), this);
	//markerAction->setIcon(QIcon("icon/marker.png"));
	markerAction->setStatusTip(tr("Draw detected markers"));
	markerAction->setShortcut(tr("CTRL+X"));
	markerAction->setShortcutContext(Qt::ApplicationShortcut);
	markerAction->setCheckable(true);
	markerAction->setChecked(false);
	connect(markerAction, SIGNAL(triggered()),
		this, SLOT(showAndHideMarker()));

	channelAction = new QAction(tr("draw Channel"), this);
	//channelAction->setIcon(QIcon("icon/channel.png"));
	channelAction->setStatusTip(tr("Draw all channels"));
	channelAction->setShortcut(tr("CTRL+C"));
	channelAction->setShortcutContext(Qt::ApplicationShortcut);
	channelAction->setCheckable(true);
	channelAction->setChecked(false);
	connect(channelAction, SIGNAL(triggered()),
		this, SLOT(showAndHideChannel()));

	neckAction = new QAction(tr("draw Neck"), this);
	//neckAction->setIcon(QIcon("icon/neck.png"));
	neckAction->setStatusTip(tr("Draw detected necks"));
	neckAction->setShortcut(tr("CTRL+V"));
	neckAction->setShortcutContext(Qt::ApplicationShortcut);
	neckAction->setCheckable(true);
	neckAction->setChecked(false);
	connect(neckAction, SIGNAL(triggered()),
		this, SLOT(showAndHideNeck()));

	//useRefAction = new QAction(tr("use as Reference"), this);
	//useRefAction->setStatusTip(tr("Use this marker as reference"));

	//dropRefAction = new QAction(tr("drop Reference"), this);
	//dropRefAction->setStatusTip(tr("Drop this reference"));
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
	visibilitySubMenu->addAction(channelAction);
	visibilitySubMenu->addAction(dropletAction);
	visibilitySubMenu->addAction(markerAction);
	visibilitySubMenu->addAction(neckAction);

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAction);
}

void MainWindow::createContextMenu()
{
	//display->addAction(useRefAction);
	//display->addAction(dropRefAction);
	//display->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createToolBars()
{
	visibilityToolBar = addToolBar(tr("&Visibility"));	
	visibilityToolBar->addAction(dropletAction);
	visibilityToolBar->addAction(markerAction);
	visibilityToolBar->addAction(channelAction);
	visibilityToolBar->addAction(neckAction);
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

//// MAINWINDOW FUNCTIONS
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
	QImage argb32;
	if (!argb32.load(fileName)) 
	{
		statusBar()->showMessage(tr("Loading canceled"), 2000);
		return false;
	}
	file8uc1 = Ueva::qImage2cvMat(argb32);
	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File loaded"), 2000);
	return true;
}

bool MainWindow::saveFile(const QString &fileName)
{
	if (!fileRgb888.save(fileName))
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

//// ACTION FUNCTIONS
void MainWindow::clear()
{
	if (noUnsavedFile())
	{
		file8uc1 = cv::Mat(0, 0, CV_8UC1);
		setCurrentFile("");
	}
}

void MainWindow::open()
{
	if (noUnsavedFile())
	{
		QString fileName = QFileDialog::getOpenFileName(this,
			tr("Open Image"), "./image",
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
		tr("Save"), "./image",
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
		"<p>This program is free software: you can redistribute it and/or modify "
		"it under the terms of the GNU General Public License as published by "
		"the Free Software Foundation, either version 3 of the License, or "
		"any later version."
		"<p>This program is distributed in the hope that it will be useful, "
		"but WITHOUT ANY WARRANTY; without even the implied warranty of "
		"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the "
		"GNU General Public License for more details."
		"<p>You should have received a copy of the GNU General Public License "
		"along with this program. If not, see http://www.gnu.org/licenses/."
		));
}

void MainWindow::updateStatusBar()
{
	QPoint mousePosition = display->getMousePosition();
	engineFpsLabel->setText(tr("Engine FPS: %1")
		.arg(QString::number(engineFps)));
	engineDutyCycleLabel->setText(tr("Engine Duty Cycle: %1 %")
		.arg(QString::number(engineDutyCycle * 100.0)));
	pumpFpsLabel->setText(tr("Pump FPS: %1")
		.arg(QString::number(pumpFps)));
	pumpDutyCycleLabel->setText(tr("Pump Duty Cycle: %1 %")
		.arg(QString::number(pumpDutyCycle * 100.0)));
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
	plotter->show();
	plotter->activateWindow();
}

void MainWindow::showAndHideChannel()
{
	if (channelAction->isChecked())
		settings.flag |= UevaSettings::DRAW_CHANNEL;
	else
		settings.flag ^= UevaSettings::DRAW_CHANNEL;
}

void MainWindow::showAndHideDroplet()
{
	if (dropletAction->isChecked())
		settings.flag |= UevaSettings::DRAW_DROPLET;
	else
		settings.flag ^= UevaSettings::DRAW_DROPLET;
}

void MainWindow::showAndHideNeck()
{
	if (neckAction->isChecked())
		settings.flag |= UevaSettings::DRAW_NECK;
	else
		settings.flag ^= UevaSettings::DRAW_NECK;
}

void MainWindow::showAndHideMarker()
{
	if (markerAction->isChecked())
		settings.flag |= UevaSettings::DRAW_MARKER;
	else
		settings.flag ^= UevaSettings::DRAW_MARKER;
}

//// THREAD FUNCTIONS
void MainWindow::engineSlot(const UevaData &data)
{
	//// TRACK IMAGE DATA
	//if (!cvMatGray.empty() && !data.rawGray.empty() && !data.displayRgb.empty())
	//{
	//	cerr << "cvMatGray " << static_cast<void*>(cvMatGray.data) << endl;
	//	cerr << "data.rawGray" << static_cast<void*>(data.rawGray.data) << endl;
	//	cerr << "data.displayRgb" << static_cast<void*>(data.displayRgb.data) << endl << endl;
	//}
	

	//// ENGINE THREAD DUTY CYCLE
	QTime now = QTime::currentTime();
	engineDutyCycle = double(engineLastTime.msecsTo(now))/
		double(timerInterval);

	//// WAKE PUMP THREAD
	pumpThread->setSettings(settings);
	pumpThread->setData(data);
	pumpThread->wake();

	//// UPDATE DISPLAY
	fileRgb888 = Ueva::cvMat2qImage(data.drawnRgb); // rgb8uc3 to rgb888, 1 deep copy
	display->setImage(fileRgb888); 
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

	//// RECORD DATA
	if (settings.flag & UevaSettings::RECORD_DATA)
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
	//// RECORD RAW
	if (settings.flag & UevaSettings::RECORD_RAW)
	{
		rawVideoWriter << data.rawGray;
	}
	//// RECORD DRAWN
	if (settings.flag & UevaSettings::RECORD_DRAWN)
	{
		drawnVideoWriter << data.drawnBgr;
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



