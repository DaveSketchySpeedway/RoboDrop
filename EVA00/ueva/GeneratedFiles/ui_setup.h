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
    QGridLayout *gridLayout_9;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_8;
    QLabel *label_2;
    QLineEdit *calibLengthEdit;
    QPushButton *calibButton;
    QVBoxLayout *verticalLayout_3;
    QPushButton *bkgdButton;
    QGridLayout *gridLayout_5;
    QSlider *openSizeSlider;
    QLabel *openSizeLabel;
    QLabel *label_8;
    QSlider *thresholdSlider;
    QLabel *thresholdLabel;
    QLabel *label_10;
    QSlider *blockSlider;
    QLabel *blockLabel;
    QLabel *label_14;
    QPushButton *maskButton;
    QGridLayout *gridLayout_6;
    QLabel *erodeSizeLabel;
    QSlider *erodeSizeSlider;
    QLabel *label_13;
    QSlider *cutThicknessSlider;
    QLabel *cutThicknessLabel;
    QPushButton *channelButton;
    QLabel *label_16;
    QVBoxLayout *sepSortLayout;
    QPushButton *sepSortButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *label_4;
    QSpacerItem *verticalSpacer_3;
    QWidget *ctrlTab;
    QWidget *layoutWidget;
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
    QWidget *layoutWidget1;
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
        gridLayout_9 = new QGridLayout(imgprocTab);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(6);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        label_2 = new QLabel(imgprocTab);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_8->addWidget(label_2, 1, 0, 1, 1);

        calibLengthEdit = new QLineEdit(imgprocTab);
        calibLengthEdit->setObjectName(QStringLiteral("calibLengthEdit"));

        gridLayout_8->addWidget(calibLengthEdit, 1, 1, 1, 1);

        calibButton = new QPushButton(imgprocTab);
        calibButton->setObjectName(QStringLiteral("calibButton"));
        calibButton->setCheckable(false);

        gridLayout_8->addWidget(calibButton, 0, 0, 1, 2);


        verticalLayout_4->addLayout(gridLayout_8);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        bkgdButton = new QPushButton(imgprocTab);
        bkgdButton->setObjectName(QStringLiteral("bkgdButton"));
        bkgdButton->setCheckable(false);

        verticalLayout_3->addWidget(bkgdButton);


        verticalLayout_4->addLayout(verticalLayout_3);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        openSizeSlider = new QSlider(imgprocTab);
        openSizeSlider->setObjectName(QStringLiteral("openSizeSlider"));
        openSizeSlider->setMaximum(10);
        openSizeSlider->setPageStep(1);
        openSizeSlider->setValue(0);
        openSizeSlider->setSliderPosition(0);
        openSizeSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(openSizeSlider, 3, 1, 1, 1);

        openSizeLabel = new QLabel(imgprocTab);
        openSizeLabel->setObjectName(QStringLiteral("openSizeLabel"));

        gridLayout_5->addWidget(openSizeLabel, 3, 2, 1, 1);

        label_8 = new QLabel(imgprocTab);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_5->addWidget(label_8, 1, 0, 1, 1);

        thresholdSlider = new QSlider(imgprocTab);
        thresholdSlider->setObjectName(QStringLiteral("thresholdSlider"));
        thresholdSlider->setMaximum(255);
        thresholdSlider->setPageStep(5);
        thresholdSlider->setValue(127);
        thresholdSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(thresholdSlider, 1, 1, 1, 1);

        thresholdLabel = new QLabel(imgprocTab);
        thresholdLabel->setObjectName(QStringLiteral("thresholdLabel"));

        gridLayout_5->addWidget(thresholdLabel, 1, 2, 1, 1);

        label_10 = new QLabel(imgprocTab);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_5->addWidget(label_10, 2, 0, 1, 1);

        blockSlider = new QSlider(imgprocTab);
        blockSlider->setObjectName(QStringLiteral("blockSlider"));
        blockSlider->setMaximum(10);
        blockSlider->setPageStep(1);
        blockSlider->setValue(5);
        blockSlider->setSliderPosition(5);
        blockSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(blockSlider, 2, 1, 1, 1);

        blockLabel = new QLabel(imgprocTab);
        blockLabel->setObjectName(QStringLiteral("blockLabel"));

        gridLayout_5->addWidget(blockLabel, 2, 2, 1, 1);

        label_14 = new QLabel(imgprocTab);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_5->addWidget(label_14, 3, 0, 1, 1);

        maskButton = new QPushButton(imgprocTab);
        maskButton->setObjectName(QStringLiteral("maskButton"));
        maskButton->setCheckable(true);

        gridLayout_5->addWidget(maskButton, 0, 1, 1, 1);


        verticalLayout_4->addLayout(gridLayout_5);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        erodeSizeLabel = new QLabel(imgprocTab);
        erodeSizeLabel->setObjectName(QStringLiteral("erodeSizeLabel"));

        gridLayout_6->addWidget(erodeSizeLabel, 1, 2, 1, 1);

        erodeSizeSlider = new QSlider(imgprocTab);
        erodeSizeSlider->setObjectName(QStringLiteral("erodeSizeSlider"));
        erodeSizeSlider->setMaximum(20);
        erodeSizeSlider->setPageStep(1);
        erodeSizeSlider->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(erodeSizeSlider, 1, 1, 1, 1);

        label_13 = new QLabel(imgprocTab);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_6->addWidget(label_13, 1, 0, 1, 1);

        cutThicknessSlider = new QSlider(imgprocTab);
        cutThicknessSlider->setObjectName(QStringLiteral("cutThicknessSlider"));
        cutThicknessSlider->setMaximum(10);
        cutThicknessSlider->setPageStep(1);
        cutThicknessSlider->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(cutThicknessSlider, 2, 1, 1, 1);

        cutThicknessLabel = new QLabel(imgprocTab);
        cutThicknessLabel->setObjectName(QStringLiteral("cutThicknessLabel"));

        gridLayout_6->addWidget(cutThicknessLabel, 2, 2, 1, 1);

        channelButton = new QPushButton(imgprocTab);
        channelButton->setObjectName(QStringLiteral("channelButton"));
        channelButton->setCheckable(true);

        gridLayout_6->addWidget(channelButton, 0, 1, 1, 1);

        label_16 = new QLabel(imgprocTab);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_6->addWidget(label_16, 2, 0, 1, 1);


        verticalLayout_4->addLayout(gridLayout_6);

        sepSortLayout = new QVBoxLayout();
        sepSortLayout->setSpacing(6);
        sepSortLayout->setObjectName(QStringLiteral("sepSortLayout"));
        sepSortButton = new QPushButton(imgprocTab);
        sepSortButton->setObjectName(QStringLiteral("sepSortButton"));
        sepSortButton->setCheckable(true);

        sepSortLayout->addWidget(sepSortButton);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_9 = new QLabel(imgprocTab);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_3->addWidget(label_9);

        label_11 = new QLabel(imgprocTab);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_3->addWidget(label_11);

        label_4 = new QLabel(imgprocTab);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);


        sepSortLayout->addLayout(horizontalLayout_3);

        verticalSpacer_3 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        sepSortLayout->addItem(verticalSpacer_3);


        verticalLayout_4->addLayout(sepSortLayout);


        gridLayout_9->addLayout(verticalLayout_4, 0, 0, 1, 1);

        tabWidget->addTab(imgprocTab, QString());
        ctrlTab = new QWidget();
        ctrlTab->setObjectName(QStringLiteral("ctrlTab"));
        layoutWidget = new QWidget(ctrlTab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(53, 82, 481, 139));
        gridLayout_4 = new QGridLayout(layoutWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_4->addWidget(label_7, 1, 0, 1, 1);

        numInLabel = new QLabel(layoutWidget);
        numInLabel->setObjectName(QStringLiteral("numInLabel"));

        gridLayout_4->addWidget(numInLabel, 1, 1, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_4->addWidget(label, 2, 0, 1, 1);

        numOutLabel = new QLabel(layoutWidget);
        numOutLabel->setObjectName(QStringLiteral("numOutLabel"));

        gridLayout_4->addWidget(numOutLabel, 2, 1, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_4->addWidget(label_5, 4, 0, 1, 1);

        numCtrlLabel = new QLabel(layoutWidget);
        numCtrlLabel->setObjectName(QStringLiteral("numCtrlLabel"));

        gridLayout_4->addWidget(numCtrlLabel, 4, 1, 1, 1);

        loadCtrlButton = new QPushButton(layoutWidget);
        loadCtrlButton->setObjectName(QStringLiteral("loadCtrlButton"));

        gridLayout_4->addWidget(loadCtrlButton, 7, 1, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_4->addWidget(label_3, 0, 0, 1, 1);

        numStateLabel = new QLabel(layoutWidget);
        numStateLabel->setObjectName(QStringLiteral("numStateLabel"));

        gridLayout_4->addWidget(numStateLabel, 0, 1, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_4->addWidget(label_6, 5, 0, 1, 1);

        ctrlTsLabel = new QLabel(layoutWidget);
        ctrlTsLabel->setObjectName(QStringLiteral("ctrlTsLabel"));

        gridLayout_4->addWidget(ctrlTsLabel, 5, 1, 1, 1);

        layoutWidget1 = new QWidget(ctrlTab);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(59, 540, 411, 25));
        gridLayout_7 = new QGridLayout(layoutWidget1);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        timerIntervalEdit = new QLineEdit(layoutWidget1);
        timerIntervalEdit->setObjectName(QStringLiteral("timerIntervalEdit"));

        gridLayout_7->addWidget(timerIntervalEdit, 0, 0, 1, 1);

        timerIntervalButton = new QPushButton(layoutWidget1);
        timerIntervalButton->setObjectName(QStringLiteral("timerIntervalButton"));

        gridLayout_7->addWidget(timerIntervalButton, 0, 1, 1, 1);

        tabWidget->addTab(ctrlTab, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);


        retranslateUi(Setup);

        tabWidget->setCurrentIndex(0);


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
        label_2->setText(QApplication::translate("Setup", "Drawn Line Length (um): ", 0));
        calibLengthEdit->setText(QApplication::translate("Setup", "500", 0));
        calibButton->setText(QApplication::translate("Setup", "Set Calibration", 0));
        bkgdButton->setText(QApplication::translate("Setup", "Set Background", 0));
        openSizeLabel->setText(QApplication::translate("Setup", "TextLabel", 0));
        label_8->setText(QApplication::translate("Setup", "Threshold:", 0));
        thresholdLabel->setText(QApplication::translate("Setup", "TextLabel", 0));
        label_10->setText(QApplication::translate("Setup", "Block Size:", 0));
        blockLabel->setText(QApplication::translate("Setup", "TextLabel", 0));
        label_14->setText(QApplication::translate("Setup", "Open Size:", 0));
        maskButton->setText(QApplication::translate("Setup", "Make Mask", 0));
        erodeSizeLabel->setText(QApplication::translate("Setup", "TextLabel", 0));
        label_13->setText(QApplication::translate("Setup", "Erode Size:", 0));
        cutThicknessLabel->setText(QApplication::translate("Setup", "TextLabel", 0));
        channelButton->setText(QApplication::translate("Setup", "Cut Channels", 0));
        label_16->setText(QApplication::translate("Setup", "Cut Thickness:", 0));
        sepSortButton->setText(QApplication::translate("Setup", "Seperate Channels", 0));
        label_9->setText(QApplication::translate("Setup", "Old Index", 0));
        label_11->setText(QApplication::translate("Setup", "New Index", 0));
        label_4->setText(QApplication::translate("Setup", "Positive Direction", 0));
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
