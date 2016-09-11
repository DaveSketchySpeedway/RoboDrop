/********************************************************************************
** Form generated from reading UI file 'addpumpdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPUMPDIALOG_H
#define UI_ADDPUMPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_AddPumpDialog
{
public:
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *pumpTypeCombo;
    QLabel *label_2;
    QSpinBox *numTransducerSpin;
    QLabel *label_3;
    QLineEdit *pumpSnEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelButton;
    QPushButton *okButton;

    void setupUi(QDialog *AddPumpDialog)
    {
        if (AddPumpDialog->objectName().isEmpty())
            AddPumpDialog->setObjectName(QStringLiteral("AddPumpDialog"));
        AddPumpDialog->setWindowModality(Qt::NonModal);
        AddPumpDialog->resize(400, 161);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AddPumpDialog->sizePolicy().hasHeightForWidth());
        AddPumpDialog->setSizePolicy(sizePolicy);
        AddPumpDialog->setModal(true);
        gridLayout = new QGridLayout(AddPumpDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(AddPumpDialog);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        pumpTypeCombo = new QComboBox(AddPumpDialog);
        pumpTypeCombo->setObjectName(QStringLiteral("pumpTypeCombo"));

        formLayout->setWidget(0, QFormLayout::FieldRole, pumpTypeCombo);

        label_2 = new QLabel(AddPumpDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        numTransducerSpin = new QSpinBox(AddPumpDialog);
        numTransducerSpin->setObjectName(QStringLiteral("numTransducerSpin"));
        numTransducerSpin->setMinimum(1);
        numTransducerSpin->setMaximum(8);
        numTransducerSpin->setValue(4);

        formLayout->setWidget(2, QFormLayout::FieldRole, numTransducerSpin);

        label_3 = new QLabel(AddPumpDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        pumpSnEdit = new QLineEdit(AddPumpDialog);
        pumpSnEdit->setObjectName(QStringLiteral("pumpSnEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, pumpSnEdit);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        cancelButton = new QPushButton(AddPumpDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        okButton = new QPushButton(AddPumpDialog);
        okButton->setObjectName(QStringLiteral("okButton"));

        horizontalLayout->addWidget(okButton);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        QWidget::setTabOrder(pumpTypeCombo, numTransducerSpin);
        QWidget::setTabOrder(numTransducerSpin, cancelButton);
        QWidget::setTabOrder(cancelButton, okButton);

        retranslateUi(AddPumpDialog);
        QObject::connect(okButton, SIGNAL(clicked()), AddPumpDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), AddPumpDialog, SLOT(reject()));

        okButton->setDefault(true);


        QMetaObject::connectSlotsByName(AddPumpDialog);
    } // setupUi

    void retranslateUi(QDialog *AddPumpDialog)
    {
        AddPumpDialog->setWindowTitle(QApplication::translate("AddPumpDialog", "AddPumpDialog", 0));
        label->setText(QApplication::translate("AddPumpDialog", "Pump Type:", 0));
        label_2->setText(QApplication::translate("AddPumpDialog", "Number of Transducers:", 0));
        label_3->setText(QApplication::translate("AddPumpDialog", "Pump Serial Number:", 0));
        pumpSnEdit->setText(QApplication::translate("AddPumpDialog", "863", 0));
        cancelButton->setText(QApplication::translate("AddPumpDialog", "Cancel", 0));
        okButton->setText(QApplication::translate("AddPumpDialog", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class AddPumpDialog: public Ui_AddPumpDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPUMPDIALOG_H
