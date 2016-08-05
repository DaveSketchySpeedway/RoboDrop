/********************************************************************************
** Form generated from reading UI file 'channelinfowidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANNELINFOWIDGET_H
#define UI_CHANNELINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChannelInfoWidget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *oldLabel;
    QComboBox *newBox;
    QComboBox *directionBox;

    void setupUi(QWidget *ChannelInfoWidget)
    {
        if (ChannelInfoWidget->objectName().isEmpty())
            ChannelInfoWidget->setObjectName(QStringLiteral("ChannelInfoWidget"));
        ChannelInfoWidget->resize(400, 40);
        gridLayout = new QGridLayout(ChannelInfoWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        oldLabel = new QLabel(ChannelInfoWidget);
        oldLabel->setObjectName(QStringLiteral("oldLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(oldLabel->sizePolicy().hasHeightForWidth());
        oldLabel->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(oldLabel);

        newBox = new QComboBox(ChannelInfoWidget);
        newBox->setObjectName(QStringLiteral("newBox"));

        horizontalLayout->addWidget(newBox);

        directionBox = new QComboBox(ChannelInfoWidget);
        directionBox->setObjectName(QStringLiteral("directionBox"));

        horizontalLayout->addWidget(directionBox);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(ChannelInfoWidget);

        QMetaObject::connectSlotsByName(ChannelInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *ChannelInfoWidget)
    {
        ChannelInfoWidget->setWindowTitle(QApplication::translate("ChannelInfoWidget", "ChannelInfoWidget", 0));
        oldLabel->setText(QApplication::translate("ChannelInfoWidget", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class ChannelInfoWidget: public Ui_ChannelInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANNELINFOWIDGET_H
