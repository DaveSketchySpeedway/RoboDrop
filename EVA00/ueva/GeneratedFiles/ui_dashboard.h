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
    QGroupBox *groupBox_3;
    QPushButton *imgprocButton;
    QLabel *label_5;
    QSlider *threshSlider;
    QLabel *threshLabel;
    QSlider *contourSizeSlider;
    QLabel *label_6;
    QLabel *contourSizeLabel;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QHBoxLayout *pumpLayout;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pumpButton;
    QPushButton *zeroPumpButton;
    QLabel *label_2;
    QWidget *widget;
    QGroupBox *groupBox_5;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QPushButton *recordDataButton;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *recordRawButton;
    QPushButton *recordDrawnButton;
    QGroupBox *groupBox_4;
    QPushButton *ctrlButton;

    void setupUi(QWidget *Dashboard)
    {
        if (Dashboard->objectName().isEmpty())
            Dashboard->setObjectName(QStringLiteral("Dashboard"));
        Dashboard->resize(800, 800);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(Dashboard->sizePolicy().hasHeightForWidth());
        Dashboard->setSizePolicy(sizePolicy);
        Dashboard->setMinimumSize(QSize(600, 800));
        groupBox_3 = new QGroupBox(Dashboard);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(30, 350, 661, 191));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        imgprocButton = new QPushButton(groupBox_3);
        imgprocButton->setObjectName(QStringLiteral("imgprocButton"));
        imgprocButton->setGeometry(QRect(30, 20, 75, 23));
        imgprocButton->setCheckable(true);
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(170, 40, 91, 16));
        threshSlider = new QSlider(groupBox_3);
        threshSlider->setObjectName(QStringLiteral("threshSlider"));
        threshSlider->setGeometry(QRect(280, 40, 160, 16));
        threshSlider->setMinimum(0);
        threshSlider->setMaximum(99);
        threshSlider->setValue(20);
        threshSlider->setOrientation(Qt::Horizontal);
        threshLabel = new QLabel(groupBox_3);
        threshLabel->setObjectName(QStringLiteral("threshLabel"));
        threshLabel->setGeometry(QRect(460, 40, 47, 13));
        contourSizeSlider = new QSlider(groupBox_3);
        contourSizeSlider->setObjectName(QStringLiteral("contourSizeSlider"));
        contourSizeSlider->setGeometry(QRect(280, 90, 160, 16));
        contourSizeSlider->setMinimum(0);
        contourSizeSlider->setMaximum(1000);
        contourSizeSlider->setValue(50);
        contourSizeSlider->setOrientation(Qt::Horizontal);
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(170, 90, 91, 16));
        contourSizeLabel = new QLabel(groupBox_3);
        contourSizeLabel->setObjectName(QStringLiteral("contourSizeLabel"));
        contourSizeLabel->setGeometry(QRect(460, 90, 47, 13));
        groupBox = new QGroupBox(Dashboard);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 120, 741, 211));
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

        groupBox_5 = new QGroupBox(Dashboard);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(140, 10, 471, 111));
        sizePolicy.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy);
        layoutWidget = new QWidget(groupBox_5);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 20, 201, 83));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        recordDataButton = new QPushButton(layoutWidget);
        recordDataButton->setObjectName(QStringLiteral("recordDataButton"));
        recordDataButton->setCheckable(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, recordDataButton);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        recordRawButton = new QPushButton(layoutWidget);
        recordRawButton->setObjectName(QStringLiteral("recordRawButton"));
        recordRawButton->setCheckable(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, recordRawButton);

        recordDrawnButton = new QPushButton(layoutWidget);
        recordDrawnButton->setObjectName(QStringLiteral("recordDrawnButton"));
        recordDrawnButton->setCheckable(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, recordDrawnButton);

        groupBox_4 = new QGroupBox(Dashboard);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(30, 550, 671, 201));
        sizePolicy1.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy1);
        ctrlButton = new QPushButton(groupBox_4);
        ctrlButton->setObjectName(QStringLiteral("ctrlButton"));
        ctrlButton->setGeometry(QRect(30, 40, 75, 23));
        ctrlButton->setCheckable(true);

        retranslateUi(Dashboard);

        QMetaObject::connectSlotsByName(Dashboard);
    } // setupUi

    void retranslateUi(QWidget *Dashboard)
    {
        Dashboard->setWindowTitle(QApplication::translate("Dashboard", "Dashboard", 0));
        groupBox_3->setTitle(QApplication::translate("Dashboard", "Image Processing", 0));
        imgprocButton->setText(QApplication::translate("Dashboard", "On", 0));
        label_5->setText(QApplication::translate("Dashboard", "Threshold:", 0));
        threshLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        label_6->setText(QApplication::translate("Dashboard", "Min Contour Size:", 0));
        contourSizeLabel->setText(QApplication::translate("Dashboard", "TextLabel", 0));
        groupBox->setTitle(QApplication::translate("Dashboard", "Pump", 0));
        pumpButton->setText(QApplication::translate("Dashboard", "On", 0));
        zeroPumpButton->setText(QApplication::translate("Dashboard", "Zero All", 0));
        label_2->setText(QApplication::translate("Dashboard", "Request (mbar)", 0));
        groupBox_5->setTitle(QApplication::translate("Dashboard", "Record", 0));
        label->setText(QApplication::translate("Dashboard", "Record Data:", 0));
        recordDataButton->setText(QApplication::translate("Dashboard", "On", 0));
        label_3->setText(QApplication::translate("Dashboard", "Record Raw Footage:", 0));
        label_4->setText(QApplication::translate("Dashboard", "Record Drawn Footage:", 0));
        recordRawButton->setText(QApplication::translate("Dashboard", "On", 0));
        recordDrawnButton->setText(QApplication::translate("Dashboard", "On", 0));
        groupBox_4->setTitle(QApplication::translate("Dashboard", "Controller", 0));
        ctrlButton->setText(QApplication::translate("Dashboard", "On", 0));
    } // retranslateUi

};

namespace Ui {
    class Dashboard: public Ui_Dashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_H
