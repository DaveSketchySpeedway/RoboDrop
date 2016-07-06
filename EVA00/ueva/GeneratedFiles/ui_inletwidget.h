/********************************************************************************
** Form generated from reading UI file 'inletwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INLETWIDGET_H
#define UI_INLETWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InletWidget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSlider *slider;
    QSpinBox *spinBox;

    void setupUi(QWidget *InletWidget)
    {
        if (InletWidget->objectName().isEmpty())
            InletWidget->setObjectName(QStringLiteral("InletWidget"));
        InletWidget->resize(153, 300);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(InletWidget->sizePolicy().hasHeightForWidth());
        InletWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(InletWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(InletWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(label);

        slider = new QSlider(InletWidget);
        slider->setObjectName(QStringLiteral("slider"));
        slider->setOrientation(Qt::Vertical);

        verticalLayout->addWidget(slider);

        spinBox = new QSpinBox(InletWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
        spinBox->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(spinBox);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(InletWidget);
        QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(InletWidget);
    } // setupUi

    void retranslateUi(QWidget *InletWidget)
    {
        InletWidget->setWindowTitle(QApplication::translate("InletWidget", "InletWidget", 0));
        label->setText(QApplication::translate("InletWidget", "Pi Tj", 0));
    } // retranslateUi

};

namespace Ui {
    class InletWidget: public Ui_InletWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INLETWIDGET_H
