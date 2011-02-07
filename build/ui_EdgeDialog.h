/********************************************************************************
** Form generated from reading UI file 'EdgeDialog.ui'
**
** Created: Tue 1. Feb 20:18:11 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDGEDIALOG_H
#define UI_EDGEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>
#include "ScriptEdit.h"

QT_BEGIN_NAMESPACE

class Ui_EdgeDialog
{
public:
    ScriptEdit *actionsEdit;
    QLabel *label;
    QPlainTextEdit *conditionsEdit;
    QLabel *label_3;
    QLabel *label_4;
    QTextEdit *questionEdit;
    QTextEdit *textEdit;
    QLabel *label_5;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *edgeIdEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *EdgeDialog)
    {
        if (EdgeDialog->objectName().isEmpty())
            EdgeDialog->setObjectName(QString::fromUtf8("EdgeDialog"));
        EdgeDialog->resize(682, 646);
        actionsEdit = new ScriptEdit(EdgeDialog);
        actionsEdit->setObjectName(QString::fromUtf8("actionsEdit"));
        actionsEdit->setGeometry(QRect(10, 420, 651, 81));
        QFont font;
        font.setFamily(QString::fromUtf8("Monospace"));
        font.setPointSize(11);
        actionsEdit->setFont(font);
        actionsEdit->setTabStopWidth(40);
        label = new QLabel(EdgeDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 400, 59, 17));
        conditionsEdit = new QPlainTextEdit(EdgeDialog);
        conditionsEdit->setObjectName(QString::fromUtf8("conditionsEdit"));
        conditionsEdit->setGeometry(QRect(10, 540, 651, 31));
        label_3 = new QLabel(EdgeDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 510, 81, 17));
        label_4 = new QLabel(EdgeDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 10, 71, 17));
        questionEdit = new QTextEdit(EdgeDialog);
        questionEdit->setObjectName(QString::fromUtf8("questionEdit"));
        questionEdit->setGeometry(QRect(10, 30, 651, 71));
        textEdit = new QTextEdit(EdgeDialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 140, 651, 241));
        label_5 = new QLabel(EdgeDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 120, 59, 17));
        widget = new QWidget(EdgeDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 580, 671, 61));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        edgeIdEdit = new QLineEdit(widget);
        edgeIdEdit->setObjectName(QString::fromUtf8("edgeIdEdit"));

        horizontalLayout->addWidget(edgeIdEdit);


        horizontalLayout_2->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        retranslateUi(EdgeDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), EdgeDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(EdgeDialog);
    } // setupUi

    void retranslateUi(QDialog *EdgeDialog)
    {
        EdgeDialog->setWindowTitle(QApplication::translate("EdgeDialog", "Edit path", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("EdgeDialog", "Actions", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("EdgeDialog", "Conditions", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("EdgeDialog", "Question", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("EdgeDialog", "Text", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("EdgeDialog", "Name", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EdgeDialog: public Ui_EdgeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDGEDIALOG_H
