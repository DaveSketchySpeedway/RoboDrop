/********************************************************************************
** Form generated from reading UI file 'setup.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUP_H
#define UI_SETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Setup
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *cameraTab;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QTreeWidget *cameraTree;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *connectCameraButton;
    QPushButton *setCameraButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *cameraButton;
    QPushButton *getCameraButton;
    QWidget *pumpTab;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QTreeWidget *pumpTree;
    QHBoxLayout *horizontalLayout;
    QPushButton *addPumpButton;
    QPushButton *clearPumpButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *getPumpButton;
    QPushButton *setPumpButton;
    QWidget *imgprocTab;
    QPushButton *bkgdButton;
    QPushButton *maskButton;
    QPushButton *channelButton;
    QPushButton *calibButton;
    QLabel *label_2;
    QLineEdit *calibLengthEdit;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_5;
    QSlider *openSizeSlider;
    QLabel *openSizeLabel;
    QLabel *label_12;
    QSlider *openShapeSlider;
    QLabel *openShapeLabel;
    QLabel *label_8;
    QSlider *thresholdSlider;
    QLabel *thresholdLabel;
    QLabel *label_10;
    QSlider *blockSlider;
    QLabel *blockLabel;
    QLabel *label_14;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_6;
    QLabel *label_15;
    QLabel *erodeSizeLabel;
    QSlider *erodeSizeSlider;
    QLabel *label_13;
    QLabel *erodeShapeLabel;
    QSlider *erodeShapeSlider;
    QLabel *label_16;
    QSlider *cutThicknessSlider;
    QLabel *cutThicknessLabel;
    QWidget *ctrlTab;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_4;
    QLabel *label_7;
    QLabel *numInLabel;
    QLabel *label;
    QLabel *numOutLabel;
    QLabel *label_5;
    QLabel *numCtrlLabel;
    QPushButton *loadCtrlButton;
    QLabel *label_3;
    QLabel *numStateLabel;
    QLabel *label_6;
    QLabel *ctrlTsLabel;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout_7;
    QLineEdit *timerIntervalEdit;
    QPushButton *timerIntervalButton;

    void setupUi(QWidget *Setup)
    {
        if (Setup->objectName().isEmpty())
            Setup->setObjectName(QStringLiteral("Setup"));
        Setup->resize(600, 800);
        Setup->setMinimumSize(QSize(600, 800));
        gridLayout = new QGridLayout(Setup);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(Setup);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        cameraTab = new QWidget();
        cameraTab->setObjectName(QStringLiteral("cameraTab"));
        gridLayout_3 = new QGridLayout(cameraTab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        cameraTree = new QTreeWidget(cameraTab);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        cameraTree->setHeaderItem(__qtreewidgetitem);
        cameraTree->setObjectName(QStringLiteral("cameraTree"));

        verticalLayout_2->addWidget(cameraTree);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        connectCameraButton = new QPushButton(cameraTab);
        connectCameraButton->setObjectName(QStringLiteral("connectCameraButton"));
        connectCameraButton->setCheckable(true);

        horizontalLayout_2->addWidget(connectCameraButton);

        setCameraButton = new QPushButton(cameraTab);
        setCameraButton->setObjectName(QStringLiteral("setCameraButton"));

        horizontalLayout_2->addWidget(setCameraButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        cameraButton = new QPushButton(cameraTab);
        cameraButton->setObjectName(QStringLiteral("cameraButton"));
        cameraButton->setCheckable(true);

        horizontalLayout_2->addWidget(cameraButton);

        getCameraButton = new QPushButton(cameraTab);
        getCameraButton->setObjectName(QStringLiteral("getCameraButton"));

        horizontalLayout_2->addWidget(getCameraButton);


        verticalLayout_2->addLayout(horizontalLayout_2);


        gridLayout_3->addLayout(verticalLayout_2, 0, 0, 1, 1);

        tabWidget->addTab(cameraTab, QString());
        pumpTab = new QWidget();
        pumpTab->setObjectName(QStringLiteral("pumpTab"));
        gridLayout_2 = new QGridLayout(pumpTab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pumpTree = new QTreeWidget(pumpTab);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QStringLiteral("1"));
        pumpTree->setHeaderItem(__qtreewidgetitem1);
        pumpTree->setObjectName(QStringLiteral("pumpTree"));

        verticalLayout->addWidget(pumpTree);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        addPumpButton = new QPushButton(pumpTab);
        addPumpButton->setObjectName(QStringLiteral("addPumpButton"));

        horizontalLayout->addWidget(addPumpButton);

        clearPumpButton = new QPushButton(pumpTab);
        clearPumpButton->setObjectName(QStringLiteral("clearPumpButton"));

        horizontalLayout->addWidget(clearPumpButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        getPumpButton = new QPushButton(pumpTab);
        getPumpButton->setObjectName(QStringLiteral("getPumpButton"));
        getPumpButton->setEnabled(false);

        horizontalLayout->addWidget(getPumpButton);

        setPumpButton = new QPushButton(pumpTab);
        setPumpButton->setObjectName(QStringLiteral("setPumpButton"));

        horizontalLayout->addWidget(setPumpButton);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        tabWidget->addTab(pumpTab, QString());
        imgprocTab = new QWidget();
        imgprocTab->setObjectName(QStringLiteral("imgprocTab"));
        bkgdButton = new QPushButton(imgprocTab);
        bkgdButton->setObjectName(QStringLiteral("bkgdButton"));
        bkgdButton->setGeometry(QRect(110, 140, 221, 23));
        bkgdButton->setCheckable(false);
        maskButton = new QPushButton(imgprocTab);
        maskButton->setObjectName(QStringLiteral("maskButton"));
        maskButton->setGeometry(QRect(110, 250, 221, 23));
        maskButton->setCheckable(true);
        channelButton = new QPushButton(imgprocTab);
        channelButton->setObjectName(QStringLiteral("channelButton"));
        channelButton->setGeometry(QRect(100, 550, 221, 23));
        channelButton->setCheckable(true);
        calibButton = new QPushButton(imgprocTab);
        calibButton->setObjectName(QStringLiteral("calibButton"));
        calibButton->setGeometry(QRect(110, 40, 221, 23));
        calibButton->setCheckable(false);
        label_2 = new QLabel(imgprocTab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(110, 70, 131, 16));
        calibLengthEdit = new QLineEdit(imgprocTab);
        calibLengthEdit->setObjectName(QStringLiteral("calibLengthEdit"));
        calibLengthEdit->setGeometry(QRect(240, 70, 71, 20));
        layoutWidget = new QWidget(imgprocTab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(92, 300, 421, 191));
        gridLayout_5 = new QGridLayout(layoutWidget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        openSizeSlider = new QSlider(layoutWidget);
        openSizeSlider->setObjectName(QStringLiteral("openSizeSlider"));
        openSizeSlider->setMaximum(10);
        openSizeSlider->setPageStep(1);
        openSizeSlider->setValue(0);
        openSizeSlider->setSliderPosition(0);
        openSizeSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(openSizeSlider, 2, 1, 1, 1);

        openSizeLabel = new QLabel(layoutWidget);
        openSizeLabel->setObjectName(QStringLiteral("openSizeLabel"));

        gridLayout_5->addWidget(openSizeLabel, 2, 2, 1, 1);

        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_5->addWidget(label_12, 3, 0, 1, 1);

        openShapeSlider = new QSlider(layoutWidget);
        openShapeSlider->setObjectName(QStringLiteral("openShapeSlider"));
        openShapeSlider->setMaximum(2);
        openShapeSlider->setPageStep(1);
        openShapeSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(openShapeSlider, 3, 1, 1, 1);

        openShapeLabel = new QLabel(layoutWidget);
        openShapeLabel->setObjectName(QStringLiteral("openShapeLabel"));

        gridLayout_5->addWidget(openShapeLabel, 3, 2, 1, 1);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_5->addWidget(label_8, 0, 0, 1, 1);

        thresholdSlider = new QSlider(layoutWidget);
        thresholdSlider->setObjectName(QStringLiteral("thresholdSlider"));
        thresholdSlider->setMaximum(255);
        thresholdSlider->setPageStep(5);
        thresholdSlider->setValue(127);
        thresholdSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(thresholdSlider, 0, 1, 1, 1);

        thresholdLabel = new QLabel(layoutWidget);
        thresholdLabel->setObjectName(QStringLiteral("thresholdLabel"));

        gridLayout_5->addWidget(thresholdLabel, 0, 2, 1, 1);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_5->addWidget(label_10, 1, 0, 1, 1);

        blockSlider = new QSlider(layoutWidget);
        blockSlider->setObjectName(QStringLiteral("blockSlider"));
        blockSlider->setMaximum(10);
        blockSlider->setPageStep(1);
        blockSlider->setValue(5);
        blockSlider->setSliderPosition(5);
        blockSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(blockSlider, 1, 1, 1, 1);

        blockLabel = new QLabel(layoutWidget);
        blockLabel->setObjectName(QStringLiteral("blockLabel"));

        gridLayout_5->addWidget(blockLabel, 1, 2, 1, 1);

        label_14 = new QLabel(layoutWidget);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_5->addWidget(label_14, 2, 0, 1, 1);

        layoutWidget1 = new QWidget(imgprocTab);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(78, 619, 451, 100));
        gridLayout_6 = new QGridLayout(layoutWidget1);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        label_15 = new QLabel(layoutWidget1);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_6->addWidget(label_15, 1, 0, 1, 1);

        erodeSizeLabel = new QLabel(layoutWidget1);
        erodeSizeLabel->setObjectName(QStringLiteral("erodeSizeLabel"));

        gridLayout_6->addWidget(erodeSizeLabel, 0, 2, 1, 1);

        erodeSizeSlider = new QSlider(layoutWidget1);
        erodeSizeSlider->setObjectName(QStringLiteral("erodeSizeSlider"));
        erodeSizeSlider->setMaximum(20);
        erodeSizeSlider->setPageStep(1);
        erodeSizeSlider->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(erodeSizeSlider, 0, 1, 1, 1);

        label_13 = new QLabel(layoutWidget1);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_6->addWidget(label_13, 0, 0, 1, 1);

        erodeShapeLabel = new QLabel(layoutWidget1);
        erodeShapeLabel->setObjectName(QStringLiteral("erodeShapeLabel"));

        gridLayout_6->addWidget(erodeShapeLabel, 1, 2, 1, 1);

        erodeShapeSlider = new QSlider(layoutWidget1);
        erodeShapeSlider->setObjectName(QStringLiteral("erodeShapeSlider"));
        erodeShapeSlider->setMaximum(2);
        erodeShapeSlider->setPageStep(1);
        erodeShapeSlider->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(erodeShapeSlider, 1, 1, 1, 1);

        label_16 = new QLabel(layoutWidget1);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_6->addWidget(label_16, 2, 0, 1, 1);

        cutThicknessSlider = new QSlider(layoutWidget1);
        cutThicknessSlider->setObjectName(QStringLiteral("cutThicknessSlider"));
        cutThicknessSlider->setMaximum(10);
        cutThicknessSlider->setPageStep(1);
        cutThicknessSlider->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(cutThicknessSlider, 2, 1, 1, 1);

        cutThicknessLabel = new QLabel(layoutWidget1);
        cutThicknessLabel->setObjectName(QStringLiteral("cutThicknessLabel"));

        gridLayout_6->addWidget(cutThicknessLabel, 2, 2, 1, 1);

        tabWidget->addTab(imgprocTab, QString());
        ctrlTab = new QWidget();
        ctrlTab->setObjectName(QStringLiteral("ctrlTab"));
        layoutWidget2 = new QWidget(ctrlTab);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(53, 82, 481, 139));
        gridLayout_4 = new QGridLayout(layoutWidget2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(layoutWidget2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_4->addWidget(label_7, 1, 0, 1, 1);

        numInLabel = new QLabel(layoutWidget2);
        numInLabel->setObjectName(QStringLiteral("numInLabel"));

        gridLayout_4->addWidget(numInLabel, 1, 1, 1, 1);

        label = new QLabel(layoutWidget2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_4->addWidget(label, 2, 0, 1, 1);

        numOutLabel = new QLabel(layoutWidget2);
        numOutLabel->setObjectName(QStringLiteral("numOutLabel"));

        gridLayout_4->addWidget(numOutLabel, 2, 1, 1, 1);

        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_4->addWidget(label_5, 4, 0, 1, 1);

        numCtrlLabel = new QLabel(layoutWidget2);
        numCtrlLabel->setObjectName(QStringLiteral("numCtrlLabel"));

        gridLayout_4->addWidget(numCtrlLabel, 4, 1, 1, 1);

        loadCtrlButton = new QPushButton(layoutWidget2);
        loadCtrlButton->setObjectName(QStringLiteral("loadCtrlButton"));

        gridLayout_4->addWidget(loadCtrlButton, 7, 1, 1, 1);

        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_4->addWidget(label_3, 0, 0, 1, 1);

        numStateLabel = new QLabel(layoutWidget2);
        numStateLabel->setObjectName(QStringLiteral("numStateLabel"));

        gridLayout_4->addWidget(numStateLabel, 0, 1, 1, 1);

        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_4->addWidget(label_6, 5, 0, 1, 1);

        ctrlTsLabel = new QLabel(layoutWidget2);
        ctrlTsLabel->setObjectName(QStringLiteral("ctrlTsLabel"));

        gridLayout_4->addWidget(ctrlTsLabel, 5, 1, 1, 1);

        layoutWidget3 = new QWidget(ctrlTab);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(59, 540, 411, 25));
        gridLayout_7 = new QGridLayout(layoutWidget3);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        timerIntervalEdit = new QLineEdit(layoutWidget3);
        timerIntervalEdit->setObjectName(QStringLiteral("timerIntervalEdit"));

        gridLayout_7->addWidget(timerIntervalEdit, 0, 0, 1, 1);

        timerIntervalButton = new QPushButton(layoutWidget3);
        timerIntervalButton->setObjectName(QStringLiteral("timerIntervalButton"));

        gridLayout_7->addWidget(timerIntervalButton, 0, 1, 1, 1);

        tabWidget->addTab(ctrlTab, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);


        retranslateUi(Setup);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(Setup);
    } // setupUi

    void retranslateUi(QWidget *Setup)
    {
        Setup->setWindowTitle(QApplication::translate("Setup", "Setup", 0));
        connectCameraButton->setText(QApplication::translate("Setup", "Connect", 0));
        setCameraButton->setText(QApplication::translate("Setup", "Set Camera", 0));
        cameraButton->setText(QApplication::translate("Setup", "On", 0));
        getCameraButton->setText(QApplication::translate("Setup", "Get Camera", 0));
        tabWidget->setTabText(tabWidget->indexOf(cameraTab), QApplication::translate("Setup", "Camera", 0));
        addPumpButton->setText(QApplication::translate("Setup", "Add Pump", 0));
        clearPumpButton->setText(QApplication::translate("Setup", "Clear All", 0));
        getPumpButton->setText(QApplication::translate("Setup", "Get Pump", 0));
        setPumpButton->setText(QApplication::translate("Setup", "Set Pump", 0));
        tabWidget->setTabText(tabWidget->indexOf(pumpTab), QApplication::translate("Setup", "Pump", 0));
        bkgdButton->setText(QApplication::translate("Setup", "Set Background", 0));
        maskButton->setText(QApplication::translate("Setup", "Make Mask", 0));
        channelButton->setText(QApplication::translate("Setup", "Cut Channel", 0));
        calibButton->setText(QApplication::translate("Setup", "Set Calibration", 0));
        label_2->setText(QApplication::translate("Setup", "Drawn Line Length (um): ", 0));
        calibLengthEdit->setText(QApplication::translate("Setup", "500", 0));
        openSizeLabel->setText(QApplication::translate("Setup", "TextLabel", 0));
        label_12->setText(QApplication::translate("Setup", "Open Shape:", 0));
        openShapeLabel->setText(QApplication::translate("Setup", "TextLabel", 0));
        label_8->setText(QApplication::translate("Setup", "Threshold:", 0));
        thresholdLabel->setText(QApplication::translate("Setup", "TextLabel", 0));
        label_10->setText(QApplication::translate("Setup", "Block Size:", 0));
        blockLabel->setText(QApplication::translate("Setup", "TextLabel", 0));
        label_14->setText(QApplication::translate("Setup", "Open Size:", 0));
        label_15->setText(QApplication::translate("Setup", "Erode Shape:", 0));
        erodeSizeLabel->setText(QApplication::translate("Setup", "TextLabel", 0));
        label_13->setText(QApplication::translate("Setup", "Erode Size:", 0));
        erodeShapeLabel->setText(QApplication::translate("Setup", "TextLabel", 0));
        label_16->setText(QApplication::translate("Setup", "Cut Thickness:", 0));
        cutThicknessLabel->setText(QApplication::translate("Setup", "TextLabel", 0));
        tabWidget->setTabText(tabWidget->indexOf(imgprocTab), QApplication::translate("Setup", "Image Processing", 0));
        label_7->setText(QApplication::translate("Setup", "Number of Plant Inputs (inlets):", 0));
        numInLabel->setText(QApplication::translate("Setup", "0", 0));
        label->setText(QApplication::translate("Setup", "Number of Plant Outputs (channels):", 0));
        numOutLabel->setText(QApplication::translate("Setup", "0", 0));
        label_5->setText(QApplication::translate("Setup", "Number of Controllers:", 0));
        numCtrlLabel->setText(QApplication::translate("Setup", "0", 0));
        loadCtrlButton->setText(QApplication::translate("Setup", "Load Controllers", 0));
        label_3->setText(QApplication::translate("Setup", "Number of Plant States:", 0));
        numStateLabel->setText(QApplication::translate("Setup", "0", 0));
        label_6->setText(QApplication::translate("Setup", "Controller Designed Sample Period:", 0));
        ctrlTsLabel->setText(QApplication::translate("Setup", "0", 0));
        timerIntervalEdit->setText(QApplication::translate("Setup", "100", 0));
        timerIntervalButton->setText(QApplication::translate("Setup", "Change uEVA Timer Interval (Sampling Period [ms])", 0));
        tabWidget->setTabText(tabWidget->indexOf(ctrlTab), QApplication::translate("Setup", "Controller", 0));
    } // retranslateUi

};

namespace Ui {
    class Setup: public Ui_Setup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUP_H
