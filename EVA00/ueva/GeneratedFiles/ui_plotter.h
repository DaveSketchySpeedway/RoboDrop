/********************************************************************************
** Form generated from reading UI file 'plotter.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTTER_H
#define UI_PLOTTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include "plot.h"

QT_BEGIN_NAMESPACE

class Ui_Plotter
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QTreeWidget *plotTree;
    Plot *plot;

    void setupUi(QWidget *Plotter)
    {
        if (Plotter->objectName().isEmpty())
            Plotter->setObjectName(QStringLiteral("Plotter"));
        Plotter->resize(800, 600);
        Plotter->setMinimumSize(QSize(800, 600));
        gridLayout = new QGridLayout(Plotter);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter = new QSplitter(Plotter);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        plotTree = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        plotTree->setHeaderItem(__qtreewidgetitem);
        plotTree->setObjectName(QStringLiteral("plotTree"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(plotTree->sizePolicy().hasHeightForWidth());
        plotTree->setSizePolicy(sizePolicy);
        splitter->addWidget(plotTree);
        plot = new Plot(splitter);
        plot->setObjectName(QStringLiteral("plot"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(plot->sizePolicy().hasHeightForWidth());
        plot->setSizePolicy(sizePolicy1);
        plot->setMinimumSize(QSize(0, 0));
        splitter->addWidget(plot);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(Plotter);

        QMetaObject::connectSlotsByName(Plotter);
    } // setupUi

    void retranslateUi(QWidget *Plotter)
    {
        Plotter->setWindowTitle(QApplication::translate("Plotter", "Plotter", 0));
    } // retranslateUi

};

namespace Ui {
    class Plotter: public Ui_Plotter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTTER_H
