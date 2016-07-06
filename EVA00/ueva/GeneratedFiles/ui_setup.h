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
#include <QtWidgets/QPushButton>
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
    QSpacerItem *horizontalSpacer_2;
    QPushButton *getCameraButton;
    QPushButton *setCameraButton;
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
    QWidget *ctrlTab;

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

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        getCameraButton = new QPushButton(cameraTab);
        getCameraButton->setObjectName(QStringLiteral("getCameraButton"));

        horizontalLayout_2->addWidget(getCameraButton);

        setCameraButton = new QPushButton(cameraTab);
        setCameraButton->setObjectName(QStringLiteral("setCameraButton"));

        horizontalLayout_2->addWidget(setCameraButton);


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
        tabWidget->addTab(imgprocTab, QString());
        ctrlTab = new QWidget();
        ctrlTab->setObjectName(QStringLiteral("ctrlTab"));
        tabWidget->addTab(ctrlTab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(Setup);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Setup);
    } // setupUi

    void retranslateUi(QWidget *Setup)
    {
        Setup->setWindowTitle(QApplication::translate("Setup", "Setup", 0));
        connectCameraButton->setText(QApplication::translate("Setup", "Connect", 0));
        getCameraButton->setText(QApplication::translate("Setup", "Get Camera", 0));
        setCameraButton->setText(QApplication::translate("Setup", "Set Camera", 0));
        tabWidget->setTabText(tabWidget->indexOf(cameraTab), QApplication::translate("Setup", "Camera", 0));
        addPumpButton->setText(QApplication::translate("Setup", "Add Pump", 0));
        clearPumpButton->setText(QApplication::translate("Setup", "Clear All", 0));
        getPumpButton->setText(QApplication::translate("Setup", "Get Pump", 0));
        setPumpButton->setText(QApplication::translate("Setup", "Set Pump", 0));
        tabWidget->setTabText(tabWidget->indexOf(pumpTab), QApplication::translate("Setup", "Pump", 0));
        tabWidget->setTabText(tabWidget->indexOf(imgprocTab), QApplication::translate("Setup", "Image Processing", 0));
        tabWidget->setTabText(tabWidget->indexOf(ctrlTab), QApplication::translate("Setup", "Controller", 0));
    } // retranslateUi

};

namespace Ui {
    class Setup: public Ui_Setup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUP_H
