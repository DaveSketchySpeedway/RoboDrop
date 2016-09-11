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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
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
    QWidget *widget;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout;
    QPushButton *imgprocButton;
    QGridLayout *gridLayout;
    QSlider *erodeSizeSlider;
    QLabel *erodeSizeLabel;
    QLabel *label_9;
    QSlider *convexSizeSlider;
    QLabel *convexSizeLabel;
    QLabel *label_5;
    QSlider *threshSlider;
    QLabel *persistenceLabel;
    QLabel *label_10;
    QSlider *sortGridSizeSlider;
    QLabel *threshLabel;
    QLabel *sorGridSizeLabel;
    QLabel *label_12;
    QLabel *label_6;
    QSlider *contourSizeSlider;
    QLabel *contourSizeLabel;
    QLabel *label_13;
    QSlider *persistenceSlider;
    QSlider *sortOrderSlider;
    QLabel *label_14;
    QLabel *sortOrderLabel;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_3;
    QLabel *label_7;
    QSlider *markerSizeSlider;
    QLabel *markerSizeLabel;
    QLabel *label_15;
    QSlider *autoMarginSlider;
    QLabel *autoMarginLabel;
    QPushButton *ctrlButton;
    QHBoxLayout *ctrlLayout;
    QLabel *label_16;
    QWidget *widget_2;

    void setupUi(QWidget *Dashboard)
    {
        if (Dashboard->objectName().isEmpty())
            Dashboard->setObjectName(QStringLiteral("Dashboard"));
        Dashboard->resize(600, 800);
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

        widget = new QWidget(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy3);

        pumpLayout->addWidget(widget);


        gridLayout_2->addLayout(pumpLayout, 0, 0, 1, 1);


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
        erodeSizeSlider = new QSlider(groupBox_3);
        erodeSizeSlider->setObjectName(QStringLiteral("erodeSizeSlider"));
        erodeSizeSlider->setMinimum(0);
        erodeSizeSlider->setMaximum(3);
        erodeSizeSlider->setPageStep(1);
        erodeSizeSlider->setValue(0);
        erodeSizeSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(erodeSizeSlider, 2, 1, 1, 1);

        erodeSizeLabel = new QLabel(groupBox_3);
        erodeSizeLabel->setObjectName(QStringLiteral("erodeSizeLabel"));

        gridLayout->addWidget(erodeSizeLabel, 2, 2, 1, 1);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 6, 0, 1, 1);

        convexSizeSlider = new QSlider(groupBox_3);
        convexSizeSlider->setObjectName(QStringLiteral("convexSizeSlider"));
        convexSizeSlider->setMinimum(0);
        convexSizeSlider->setMaximum(100);
        convexSizeSlider->setPageStep(1);
        convexSizeSlider->setValue(7);
        convexSizeSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(convexSizeSlider, 6, 1, 1, 1);

        convexSizeLabel = new QLabel(groupBox_3);
        convexSizeLabel->setObjectName(QStringLiteral("convexSizeLabel"));

        gridLayout->addWidget(convexSizeLabel, 6, 2, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        threshSlider = new QSlider(groupBox_3);
        threshSlider->setObjectName(QStringLiteral("threshSlider"));
        threshSlider->setMinimum(1);
        threshSlider->setMaximum(100);
        threshSlider->setPageStep(1);
        threshSlider->setValue(20);
        threshSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(threshSlider, 1, 1, 1, 1);

        persistenceLabel = new QLabel(groupBox_3);
        persistenceLabel->setObjectName(QStringLiteral("persistenceLabel"));

        gridLayout->addWidget(persistenceLabel, 7, 2, 1, 1);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 4, 0, 1, 1);

        sortGridSizeSlider = new QSlider(groupBox_3);
        sortGridSizeSlider->setObjectName(QStringLiteral("sortGridSizeSlider"));
        sortGridSizeSlider->setMinimum(1);
        sortGridSizeSlider->setMaximum(100);
        sortGridSizeSlider->setPageStep(1);
        sortGridSizeSlider->setValue(40);
        sortGridSizeSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sortGridSizeSlider, 4, 1, 1, 1);

        threshLabel = new QLabel(groupBox_3);
        threshLabel->setObjectName(QStringLiteral("threshLabel"));

        gridLayout->addWidget(threshLabel, 1, 2, 1, 1);

        sorGridSizeLabel = new QLabel(groupBox_3);
        sorGridSizeLabel->setObjectName(QStringLiteral("sorGridSizeLabel"));

        gridLayout->addWidget(sorGridSizeLabel, 4, 2, 1, 1);

        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 2, 0, 1, 1);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        contourSizeSlider = new QSlider(groupBox_3);
        contourSizeSlider->setObjectName(QStringLiteral("contourSizeSlider"));
        contourSizeSlider->setMinimum(1);
        contourSizeSlider->setMaximum(1000);
        contourSizeSlider->setValue(10);
        contourSizeSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(contourSizeSlider, 3, 1, 1, 1);

        contourSizeLabel = new QLabel(groupBox_3);
        contourSizeLabel->setObjectName(QStringLiteral("contourSizeLabel"));

        gridLayout->addWidget(contourSizeLabel, 3, 2, 1, 1);

        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout->addWidget(label_13, 7, 0, 1, 1);

        persistenceSlider = new QSlider(groupBox_3);
        persistenceSlider->setObjectName(QStringLiteral("persistenceSlider"));
        persistenceSlider->setMinimum(0);
        persistenceSlider->setMaximum(100);
        persistenceSlider->setPageStep(1);
        persistenceSlider->setValue(7);
        persistenceSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(persistenceSlider, 7, 1, 1, 1);

        sortOrderSlider = new QSlider(groupBox_3);
        sortOrderSlider->setObjectName(QStringLiteral("sortOrderSlider"));
        sortOrderSlider->setMinimum(0);
        sortOrderSlider->setMaximum(1);
        sortOrderSlider->setPageStep(1);
        sortOrderSlider->setValue(0);
        sortOrderSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sortOrderSlider, 5, 1, 1, 1);

        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout->addWidget(label_14, 5, 0, 1, 1);

        sortOrderLabel = new QLabel(groupBox_3);
        sortOrderLabel->setObjectName(QStringLiteral("sortOrderLabel"));

        gridLayout->addWidget(sortOrderLabel, 5, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);


        gridLayout_5->addLayout(verticalLayout, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(Dashboard);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(groupBox_4);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_3->addWidget(label_7, 1, 0, 1, 1);

        markerSizeSlider = new QSlider(groupBox_4);
        markerSizeSlider->setObjectName(QStringLiteral("markerSizeSlider"));
        markerSizeSlider->setMinimum(0);
        markerSizeSlider->setMaximum(200);
        markerSizeSlider->setPageStep(1);
        markerSizeSlider->setValue(100);
        markerSizeSlider->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(markerSizeSlider, 1, 1, 1, 1);

        markerSizeLabel = new QLabel(groupBox_4);
        markerSizeLabel->setObjectName(QStringLiteral("markerSizeLabel"));

        gridLayout_3->addWidget(markerSizeLabel, 1, 2, 1, 1);

        label_15 = new QLabel(groupBox_4);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_3->addWidget(label_15, 2, 0, 1, 1);

        autoMarginSlider = new QSlider(groupBox_4);
        autoMarginSlider->setObjectName(QStringLiteral("autoMarginSlider"));
        autoMarginSlider->setMinimum(0);
        autoMarginSlider->setMaximum(200);
        autoMarginSlider->setPageStep(1);
        autoMarginSlider->setValue(100);
        autoMarginSlider->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(autoMarginSlider, 2, 1, 1, 1);

        autoMarginLabel = new QLabel(groupBox_4);
        autoMarginLabel->setObjectName(QStringLiteral("autoMarginLabel"));

        gridLayout_3->addWidget(autoMarginLabel, 2, 2, 1, 1);

        ctrlButton = new QPushButton(groupBox_4);
        ctrlButton->setObjectName(QStringLiteral("ctrlButton"));
        ctrlButton->setCheckable(true);

        gridLayout_3->addWidget(ctrlButton, 0, 0, 1, 3);


        verticalLayout_4->addLayout(gridLayout_3);

        ctrlLayout = new QHBoxLayout();
        ctrlLayout->setSpacing(6);
        ctrlLayout->setObjectName(QStringLiteral("ctrlLayout"));
        label_16 = new QLabel(groupBox_4);
        label_16->setObjectName(QStringLiteral("label_16"));

        ctrlLayout->addWidget(label_16);

        widget_2 = new QWidget(groupBox_4);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        sizePolicy3.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy3);

        ctrlLayout->addWidget(widget_2);


        verticalLayout_4->addLayout(ctrlLayout);


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
        erodeSizeLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        label_9->setText(QApplication::translate("Dashboard", "Neck Min Convex:", 0));
        convexSizeLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        label_5->setText(QApplication::translate("Dashboard", "Droplet Threshold:", 0));
        persistenceLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        label_10->setText(QApplication::translate("Dashboard", "Sort Grid Size:", 0));
        threshLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        sorGridSizeLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        label_12->setText(QApplication::translate("Dashboard", "Droplet Erode Size::", 0));
        label_6->setText(QApplication::translate("Dashboard", "Min Contour Size:", 0));
        contourSizeLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        label_13->setText(QApplication::translate("Dashboard", "Neck Persistence:", 0));
        label_14->setText(QApplication::translate("Dashboard", "Sort Order:", 0));
        sortOrderLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        groupBox_4->setTitle(QApplication::translate("Dashboard", "Controller", 0));
        label_7->setText(QApplication::translate("Dashboard", "Marker Rectangle  Size:", 0));
        markerSizeLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        label_15->setText(QApplication::translate("Dashboard", "Auto Catch Margin:", 0));
        autoMarginLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        ctrlButton->setText(QApplication::translate("Dashboard", "On", 0));
        label_16->setText(QApplication::translate("Dashboard", "Auto Catch Channel:", 0));
    } // retranslateUi

};

namespace Ui {
    class Dashboard: public Ui_Dashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_H
