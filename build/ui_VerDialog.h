/********************************************************************************
** Form generated from reading UI file 'VerDialog.ui'
**
** Created: Tue 1. Feb 20:18:11 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VERDIALOG_H
#define UI_VERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "ScriptEdit.h"

QT_BEGIN_NAMESPACE

class Ui_VerDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QTextEdit *textEdit;
    QLabel *label;
    ScriptEdit *actionsEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *verIdEdit;
    QGridLayout *gridLayout;
    QRadioButton *winRadio;
    QLabel *label_6;
    QRadioButton *odinaryRadio;
    QRadioButton *startRadio;
    QRadioButton *failRadio;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *VerDialog)
    {
        if (VerDialog->objectName().isEmpty())
            VerDialog->setObjectName(QString::fromUtf8("VerDialog"));
        VerDialog->resize(773, 663);
        verticalLayoutWidget = new QWidget(VerDialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 751, 641));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        textEdit = new QTextEdit(verticalLayoutWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        actionsEdit = new ScriptEdit(verticalLayoutWidget);
        actionsEdit->setObjectName(QString::fromUtf8("actionsEdit"));
        QFont font;
        font.setFamily(QString::fromUtf8("Monospace"));
        font.setPointSize(11);
        actionsEdit->setFont(font);
        actionsEdit->setTabStopWidth(40);

        verticalLayout->addWidget(actionsEdit);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        verIdEdit = new QLineEdit(verticalLayoutWidget);
        verIdEdit->setObjectName(QString::fromUtf8("verIdEdit"));

        horizontalLayout_2->addWidget(verIdEdit);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        winRadio = new QRadioButton(verticalLayoutWidget);
        winRadio->setObjectName(QString::fromUtf8("winRadio"));

        gridLayout->addWidget(winRadio, 1, 2, 1, 1);

        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        odinaryRadio = new QRadioButton(verticalLayoutWidget);
        odinaryRadio->setObjectName(QString::fromUtf8("odinaryRadio"));

        gridLayout->addWidget(odinaryRadio, 0, 1, 1, 1);

        startRadio = new QRadioButton(verticalLayoutWidget);
        startRadio->setObjectName(QString::fromUtf8("startRadio"));

        gridLayout->addWidget(startRadio, 1, 1, 1, 1);

        failRadio = new QRadioButton(verticalLayoutWidget);
        failRadio->setObjectName(QString::fromUtf8("failRadio"));

        gridLayout->addWidget(failRadio, 0, 2, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);

        buttonBox = new QDialogButtonBox(verticalLayoutWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayoutWidget->raise();
        verIdEdit->raise();

        retranslateUi(VerDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), VerDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(VerDialog);
    } // setupUi

    void retranslateUi(QDialog *VerDialog)
    {
        VerDialog->setWindowTitle(QApplication::translate("VerDialog", "Edit location", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("VerDialog", "Text", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("VerDialog", "Actions", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("VerDialog", "Name", 0, QApplication::UnicodeUTF8));
        winRadio->setText(QApplication::translate("VerDialog", "Win", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("VerDialog", "Type", 0, QApplication::UnicodeUTF8));
        odinaryRadio->setText(QApplication::translate("VerDialog", "Odinary", 0, QApplication::UnicodeUTF8));
        startRadio->setText(QApplication::translate("VerDialog", "Start", 0, QApplication::UnicodeUTF8));
        failRadio->setText(QApplication::translate("VerDialog", "Fail", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VerDialog: public Ui_VerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VERDIALOG_H
