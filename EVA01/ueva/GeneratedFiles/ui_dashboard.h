/********************************************************************************
** Form generated from reading UI file 'dashboard.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARD_H
#define UI_DASHBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dashboard
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_5;
    QFormLayout *formLayout;
    QLabel *label;
    QPushButton *recordDataButton;
    QLabel *label_3;
    QPushButton *recordRawButton;
    QLabel *label_4;
    QPushButton *recordDrawnButton;
    QLabel *label_11;
    QPushButton *recordNeckButton;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QHBoxLayout *pumpLayout;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pumpButton;
    QPushButton *zeroPumpButton;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout;
    QPushButton *imgprocButton;
    QGridLayout *gridLayout;
    QLabel *convexSizeLabel;
    QLabel *label_5;
    QSlider *threshSlider;
    QLabel *persistenceLabel;
    QLabel *threshLabel;
    QLabel *label_12;
    QLabel *label_6;
    QSlider *erodeSizeSlider;
    QLabel *erodeSizeLabel;
    QLabel *label_9;
    QSlider *convexSizeSlider;
    QSlider *contourSizeSlider;
    QLabel *contourSizeLabel;
    QLabel *label_13;
    QSlider *persistenceSlider;
    QSlider *trackTooFarSlider;
    QLabel *label_14;
    QLabel *trackTooFarLabel;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *autoCatchLayout;
    QLabel *label_16;
    QHBoxLayout *useNeckLayout;
    QLabel *label_18;
    QGridLayout *gridLayout_3;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *modelCovLabel;
    QLabel *disturbanceCovLabel;
    QSlider *modelCovSlider;
    QSlider *disturbanceCovSlider;
    QLabel *label_21;
    QSlider *disturbanceCorrSlider;
    QLabel *disturbanceCorrLabel;
    QPushButton *ctrlButton;
    QLabel *markerSizeLabel;
    QSlider *markerSizeSlider;
    QLabel *label_7;
    QSlider *autoHorzExclSlider;
    QLabel *label_15;
    QLabel *autoHorzExclLabel;
    QLabel *label_17;
    QSlider *autoVertExclSlider;
    QLabel *autoVertExclLabel;
    QGridLayout *gridLayout_4;
    QDoubleSpinBox *neckThresholdSBox;
    QLabel *label_10;
    QDoubleSpinBox *neckDesireSBox;
    QLabel *label_8;
    QLabel *label_23;
    QDoubleSpinBox *neckLowerGainSBox;
    QLabel *label_24;
    QDoubleSpinBox *neckHigherGainSBox;
    QHBoxLayout *neckDirectionLayout;
    QLabel *label_22;

    void setupUi(QWidget *Dashboard)
    {
        if (Dashboard->objectName().isEmpty())
            Dashboard->setObjectName(QStringLiteral("Dashboard"));
        Dashboard->resize(600, 900);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(Dashboard->sizePolicy().hasHeightForWidth());
        Dashboard->setSizePolicy(sizePolicy);
        Dashboard->setMinimumSize(QSize(350, 400));
        verticalLayout_3 = new QVBoxLayout(Dashboard);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox_5 = new QGroupBox(Dashboard);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        sizePolicy.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy);
        formLayout = new QFormLayout(groupBox_5);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(groupBox_5);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        recordDataButton = new QPushButton(groupBox_5);
        recordDataButton->setObjectName(QStringLiteral("recordDataButton"));
        recordDataButton->setCheckable(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, recordDataButton);

        label_3 = new QLabel(groupBox_5);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        recordRawButton = new QPushButton(groupBox_5);
        recordRawButton->setObjectName(QStringLiteral("recordRawButton"));
        recordRawButton->setCheckable(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, recordRawButton);

        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        recordDrawnButton = new QPushButton(groupBox_5);
        recordDrawnButton->setObjectName(QStringLiteral("recordDrawnButton"));
        recordDrawnButton->setCheckable(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, recordDrawnButton);

        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QStringLiteral("label_11"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_11);

        recordNeckButton = new QPushButton(groupBox_5);
        recordNeckButton->setObjectName(QStringLiteral("recordNeckButton"));
        recordNeckButton->setCheckable(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, recordNeckButton);


        verticalLayout_3->addWidget(groupBox_5);

        groupBox = new QGroupBox(Dashboard);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(2);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pumpLayout = new QHBoxLayout();
        pumpLayout->setSpacing(6);
        pumpLayout->setObjectName(QStringLiteral("pumpLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        pumpButton = new QPushButton(groupBox);
        pumpButton->setObjectName(QStringLiteral("pumpButton"));
        pumpButton->setCheckable(true);

        verticalLayout_2->addWidget(pumpButton);

        zeroPumpButton = new QPushButton(groupBox);
        zeroPumpButton->setObjectName(QStringLiteral("zeroPumpButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(zeroPumpButton->sizePolicy().hasHeightForWidth());
        zeroPumpButton->setSizePolicy(sizePolicy2);

        verticalLayout_2->addWidget(zeroPumpButton);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);


        pumpLayout->addLayout(verticalLayout_2);


        gridLayout_2->addLayout(pumpLayout, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);


        verticalLayout_3->addWidget(groupBox);

        groupBox_3 = new QGroupBox(Dashboard);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        gridLayout_5 = new QGridLayout(groupBox_3);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        imgprocButton = new QPushButton(groupBox_3);
        imgprocButton->setObjectName(QStringLiteral("imgprocButton"));
        imgprocButton->setCheckable(true);

        verticalLayout->addWidget(imgprocButton);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        convexSizeLabel = new QLabel(groupBox_3);
        convexSizeLabel->setObjectName(QStringLiteral("convexSizeLabel"));

        gridLayout->addWidget(convexSizeLabel, 5, 2, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        threshSlider = new QSlider(groupBox_3);
        threshSlider->setObjectName(QStringLiteral("threshSlider"));
        threshSlider->setMinimum(1);
        threshSlider->setMaximum(100);
        threshSlider->setPageStep(1);
        threshSlider->setValue(25);
        threshSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(threshSlider, 1, 1, 1, 1);

        persistenceLabel = new QLabel(groupBox_3);
        persistenceLabel->setObjectName(QStringLiteral("persistenceLabel"));

        gridLayout->addWidget(persistenceLabel, 6, 2, 1, 1);

        threshLabel = new QLabel(groupBox_3);
        threshLabel->setObjectName(QStringLiteral("threshLabel"));

        gridLayout->addWidget(threshLabel, 1, 2, 1, 1);

        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 2, 0, 1, 1);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        erodeSizeSlider = new QSlider(groupBox_3);
        erodeSizeSlider->setObjectName(QStringLiteral("erodeSizeSlider"));
        erodeSizeSlider->setMinimum(1);
        erodeSizeSlider->setMaximum(4);
        erodeSizeSlider->setPageStep(1);
        erodeSizeSlider->setValue(1);
        erodeSizeSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(erodeSizeSlider, 2, 1, 1, 1);

        erodeSizeLabel = new QLabel(groupBox_3);
        erodeSizeLabel->setObjectName(QStringLiteral("erodeSizeLabel"));

        gridLayout->addWidget(erodeSizeLabel, 2, 2, 1, 1);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 5, 0, 1, 1);

        convexSizeSlider = new QSlider(groupBox_3);
        convexSizeSlider->setObjectName(QStringLiteral("convexSizeSlider"));
        convexSizeSlider->setMinimum(1);
        convexSizeSlider->setMaximum(100);
        convexSizeSlider->setPageStep(1);
        convexSizeSlider->setValue(7);
        convexSizeSlider->setSliderPosition(7);
        convexSizeSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(convexSizeSlider, 5, 1, 1, 1);

        contourSizeSlider = new QSlider(groupBox_3);
        contourSizeSlider->setObjectName(QStringLiteral("contourSizeSlider"));
        contourSizeSlider->setMinimum(1);
        contourSizeSlider->setMaximum(1000);
        contourSizeSlider->setPageStep(1);
        contourSizeSlider->setValue(10);
        contourSizeSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(contourSizeSlider, 3, 1, 1, 1);

        contourSizeLabel = new QLabel(groupBox_3);
        contourSizeLabel->setObjectName(QStringLiteral("contourSizeLabel"));

        gridLayout->addWidget(contourSizeLabel, 3, 2, 1, 1);

        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout->addWidget(label_13, 6, 0, 1, 1);

        persistenceSlider = new QSlider(groupBox_3);
        persistenceSlider->setObjectName(QStringLiteral("persistenceSlider"));
        persistenceSlider->setMinimum(1);
        persistenceSlider->setMaximum(100);
        persistenceSlider->setPageStep(1);
        persistenceSlider->setValue(7);
        persistenceSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(persistenceSlider, 6, 1, 1, 1);

        trackTooFarSlider = new QSlider(groupBox_3);
        trackTooFarSlider->setObjectName(QStringLiteral("trackTooFarSlider"));
        trackTooFarSlider->setMinimum(1);
        trackTooFarSlider->setMaximum(100);
        trackTooFarSlider->setPageStep(1);
        trackTooFarSlider->setValue(50);
        trackTooFarSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(trackTooFarSlider, 4, 1, 1, 1);

        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout->addWidget(label_14, 4, 0, 1, 1);

        trackTooFarLabel = new QLabel(groupBox_3);
        trackTooFarLabel->setObjectName(QStringLiteral("trackTooFarLabel"));

        gridLayout->addWidget(trackTooFarLabel, 4, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);


        gridLayout_5->addLayout(verticalLayout, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(Dashboard);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        sizePolicy1.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy1);
        verticalLayout_4 = new QVBoxLayout(groupBox_4);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        autoCatchLayout = new QHBoxLayout();
        autoCatchLayout->setSpacing(6);
        autoCatchLayout->setObjectName(QStringLiteral("autoCatchLayout"));
        label_16 = new QLabel(groupBox_4);
        label_16->setObjectName(QStringLiteral("label_16"));

        autoCatchLayout->addWidget(label_16);


        verticalLayout_4->addLayout(autoCatchLayout);

        useNeckLayout = new QHBoxLayout();
        useNeckLayout->setSpacing(6);
        useNeckLayout->setObjectName(QStringLiteral("useNeckLayout"));
        label_18 = new QLabel(groupBox_4);
        label_18->setObjectName(QStringLiteral("label_18"));

        useNeckLayout->addWidget(label_18);


        verticalLayout_4->addLayout(useNeckLayout);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_19 = new QLabel(groupBox_4);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_3->addWidget(label_19, 6, 0, 1, 1);

        label_20 = new QLabel(groupBox_4);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout_3->addWidget(label_20, 7, 0, 1, 1);

        modelCovLabel = new QLabel(groupBox_4);
        modelCovLabel->setObjectName(QStringLiteral("modelCovLabel"));

        gridLayout_3->addWidget(modelCovLabel, 6, 2, 1, 1);

        disturbanceCovLabel = new QLabel(groupBox_4);
        disturbanceCovLabel->setObjectName(QStringLiteral("disturbanceCovLabel"));

        gridLayout_3->addWidget(disturbanceCovLabel, 7, 2, 1, 1);

        modelCovSlider = new QSlider(groupBox_4);
        modelCovSlider->setObjectName(QStringLiteral("modelCovSlider"));
        modelCovSlider->setMinimum(-120);
        modelCovSlider->setMaximum(80);
        modelCovSlider->setPageStep(1);
        modelCovSlider->setValue(10);
        modelCovSlider->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(modelCovSlider, 6, 1, 1, 1);

        disturbanceCovSlider = new QSlider(groupBox_4);
        disturbanceCovSlider->setObjectName(QStringLiteral("disturbanceCovSlider"));
        disturbanceCovSlider->setMinimum(-120);
        disturbanceCovSlider->setMaximum(80);
        disturbanceCovSlider->setSingleStep(1);
        disturbanceCovSlider->setPageStep(1);
        disturbanceCovSlider->setValue(-50);
        disturbanceCovSlider->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(disturbanceCovSlider, 7, 1, 1, 1);

        label_21 = new QLabel(groupBox_4);
        label_21->setObjectName(QStringLiteral("label_21"));

        gridLayout_3->addWidget(label_21, 8, 0, 1, 1);

        disturbanceCorrSlider = new QSlider(groupBox_4);
        disturbanceCorrSlider->setObjectName(QStringLiteral("disturbanceCorrSlider"));
        disturbanceCorrSlider->setMinimum(1);
        disturbanceCorrSlider->setMaximum(1000);
        disturbanceCorrSlider->setPageStep(1);
        disturbanceCorrSlider->setValue(20);
        disturbanceCorrSlider->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(disturbanceCorrSlider, 8, 1, 1, 1);

        disturbanceCorrLabel = new QLabel(groupBox_4);
        disturbanceCorrLabel->setObjectName(QStringLiteral("disturbanceCorrLabel"));

        gridLayout_3->addWidget(disturbanceCorrLabel, 8, 2, 1, 1);

        ctrlButton = new QPushButton(groupBox_4);
        ctrlButton->setObjectName(QStringLiteral("ctrlButton"));
        ctrlButton->setCheckable(true);

        gridLayout_3->addWidget(ctrlButton, 2, 0, 1, 3);

        markerSizeLabel = new QLabel(groupBox_4);
        markerSizeLabel->setObjectName(QStringLiteral("markerSizeLabel"));

        gridLayout_3->addWidget(markerSizeLabel, 3, 2, 1, 1);

        markerSizeSlider = new QSlider(groupBox_4);
        markerSizeSlider->setObjectName(QStringLiteral("markerSizeSlider"));
        markerSizeSlider->setMinimum(0);
        markerSizeSlider->setMaximum(200);
        markerSizeSlider->setPageStep(1);
        markerSizeSlider->setValue(100);
        markerSizeSlider->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(markerSizeSlider, 3, 1, 1, 1);

        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_3->addWidget(label_7, 3, 0, 1, 1);

        autoHorzExclSlider = new QSlider(groupBox_4);
        autoHorzExclSlider->setObjectName(QStringLiteral("autoHorzExclSlider"));
        autoHorzExclSlider->setMinimum(0);
        autoHorzExclSlider->setMaximum(100);
        autoHorzExclSlider->setPageStep(1);
        autoHorzExclSlider->setValue(5);
        autoHorzExclSlider->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(autoHorzExclSlider, 4, 1, 1, 1);

        label_15 = new QLabel(groupBox_4);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_3->addWidget(label_15, 4, 0, 1, 1);

        autoHorzExclLabel = new QLabel(groupBox_4);
        autoHorzExclLabel->setObjectName(QStringLiteral("autoHorzExclLabel"));

        gridLayout_3->addWidget(autoHorzExclLabel, 4, 2, 1, 1);

        label_17 = new QLabel(groupBox_4);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_3->addWidget(label_17, 5, 0, 1, 1);

        autoVertExclSlider = new QSlider(groupBox_4);
        autoVertExclSlider->setObjectName(QStringLiteral("autoVertExclSlider"));
        autoVertExclSlider->setMinimum(0);
        autoVertExclSlider->setMaximum(100);
        autoVertExclSlider->setPageStep(1);
        autoVertExclSlider->setValue(95);
        autoVertExclSlider->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(autoVertExclSlider, 5, 1, 1, 1);

        autoVertExclLabel = new QLabel(groupBox_4);
        autoVertExclLabel->setObjectName(QStringLiteral("autoVertExclLabel"));

        gridLayout_3->addWidget(autoVertExclLabel, 5, 2, 1, 1);


        verticalLayout_4->addLayout(gridLayout_3);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        neckThresholdSBox = new QDoubleSpinBox(groupBox_4);
        neckThresholdSBox->setObjectName(QStringLiteral("neckThresholdSBox"));
        neckThresholdSBox->setValue(2);

        gridLayout_4->addWidget(neckThresholdSBox, 0, 3, 1, 1);

        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_4->addWidget(label_10, 0, 2, 1, 1);

        neckDesireSBox = new QDoubleSpinBox(groupBox_4);
        neckDesireSBox->setObjectName(QStringLiteral("neckDesireSBox"));
        neckDesireSBox->setValue(60);

        gridLayout_4->addWidget(neckDesireSBox, 0, 1, 1, 1);

        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_4->addWidget(label_8, 0, 0, 1, 1);

        label_23 = new QLabel(groupBox_4);
        label_23->setObjectName(QStringLiteral("label_23"));

        gridLayout_4->addWidget(label_23, 1, 0, 1, 1);

        neckLowerGainSBox = new QDoubleSpinBox(groupBox_4);
        neckLowerGainSBox->setObjectName(QStringLiteral("neckLowerGainSBox"));
        neckLowerGainSBox->setValue(3);

        gridLayout_4->addWidget(neckLowerGainSBox, 1, 1, 1, 1);

        label_24 = new QLabel(groupBox_4);
        label_24->setObjectName(QStringLiteral("label_24"));

        gridLayout_4->addWidget(label_24, 1, 2, 1, 1);

        neckHigherGainSBox = new QDoubleSpinBox(groupBox_4);
        neckHigherGainSBox->setObjectName(QStringLiteral("neckHigherGainSBox"));
        neckHigherGainSBox->setValue(1);

        gridLayout_4->addWidget(neckHigherGainSBox, 1, 3, 1, 1);


        verticalLayout_4->addLayout(gridLayout_4);

        neckDirectionLayout = new QHBoxLayout();
        neckDirectionLayout->setSpacing(6);
        neckDirectionLayout->setObjectName(QStringLiteral("neckDirectionLayout"));
        label_22 = new QLabel(groupBox_4);
        label_22->setObjectName(QStringLiteral("label_22"));

        neckDirectionLayout->addWidget(label_22);


        verticalLayout_4->addLayout(neckDirectionLayout);


        verticalLayout_3->addWidget(groupBox_4);


        retranslateUi(Dashboard);

        QMetaObject::connectSlotsByName(Dashboard);
    } // setupUi

    void retranslateUi(QWidget *Dashboard)
    {
        Dashboard->setWindowTitle(QApplication::translate("Dashboard", "Dashboard", 0));
        groupBox_5->setTitle(QApplication::translate("Dashboard", "Record", 0));
        label->setText(QApplication::translate("Dashboard", "Record Data:", 0));
        recordDataButton->setText(QApplication::translate("Dashboard", "On", 0));
        label_3->setText(QApplication::translate("Dashboard", "Record Raw Footage:", 0));
        recordRawButton->setText(QApplication::translate("Dashboard", "On", 0));
        label_4->setText(QApplication::translate("Dashboard", "Record Drawn Footage:", 0));
        recordDrawnButton->setText(QApplication::translate("Dashboard", "On", 0));
        label_11->setText(QApplication::translate("Dashboard", "Record Neck Profile:", 0));
        recordNeckButton->setText(QApplication::translate("Dashboard", "On", 0));
        groupBox->setTitle(QApplication::translate("Dashboard", "Pump", 0));
        pumpButton->setText(QApplication::translate("Dashboard", "On", 0));
        zeroPumpButton->setText(QApplication::translate("Dashboard", "Zero All", 0));
        label_2->setText(QApplication::translate("Dashboard", "Request (mbar)", 0));
        groupBox_3->setTitle(QApplication::translate("Dashboard", "Image Processing", 0));
        imgprocButton->setText(QApplication::translate("Dashboard", "On", 0));
        convexSizeLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        label_5->setText(QApplication::translate("Dashboard", "Droplet Threshold:", 0));
        persistenceLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        threshLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        label_12->setText(QApplication::translate("Dashboard", "Droplet Erode Size::", 0));
        label_6->setText(QApplication::translate("Dashboard", "Min Contour Size:", 0));
        erodeSizeLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        label_9->setText(QApplication::translate("Dashboard", "Neck Min Convex:", 0));
        contourSizeLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        label_13->setText(QApplication::translate("Dashboard", "Neck Persistence:", 0));
        label_14->setText(QApplication::translate("Dashboard", "Track Too Far:", 0));
        trackTooFarLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        groupBox_4->setTitle(QApplication::translate("Dashboard", "Controller", 0));
        label_16->setText(QApplication::translate("Dashboard", "Auto Catch Channels:", 0));
        label_18->setText(QApplication::translate("Dashboard", "Use Neck Channels:", 0));
        label_19->setText(QApplication::translate("Dashboard", "Model Noise Covariance:", 0));
        label_20->setText(QApplication::translate("Dashboard", "Disturbance Noise Covariance:", 0));
        modelCovLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        disturbanceCovLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        label_21->setText(QApplication::translate("Dashboard", "Disturbance Correction Speed:", 0));
        disturbanceCorrLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        ctrlButton->setText(QApplication::translate("Dashboard", "On", 0));
        markerSizeLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        label_7->setText(QApplication::translate("Dashboard", "Marker Rectangle  Size:", 0));
        label_15->setText(QApplication::translate("Dashboard", "Auto Catch Horizontal Exclude:", 0));
        autoHorzExclLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        label_17->setText(QApplication::translate("Dashboard", "Auto Catch Verticle Exclude:", 0));
        autoVertExclLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        label_10->setText(QApplication::translate("Dashboard", "Neck Threshold (um):", 0));
        label_8->setText(QApplication::translate("Dashboard", "Neck Desire (um):", 0));
        label_23->setText(QApplication::translate("Dashboard", "Neck Lower Gain:", 0));
        label_24->setText(QApplication::translate("Dashboard", "Neck Higher Gain:", 0));
        label_22->setText(QApplication::translate("Dashboard", "Neck Direction (check == >>|<<):", 0));
    } // retranslateUi

};

namespace Ui {
    class Dashboard: public Ui_Dashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_H
