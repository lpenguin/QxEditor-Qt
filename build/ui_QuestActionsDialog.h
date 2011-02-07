/********************************************************************************
** Form generated from reading UI file 'QuestActionsDialog.ui'
**
** Created: Wed 2. Feb 22:53:08 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUESTACTIONSDIALOG_H
#define UI_QUESTACTIONSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "ScriptEdit.h"

QT_BEGIN_NAMESPACE

class Ui_QuestActionsDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    ScriptEdit *actionsEdit;

    void setupUi(QDialog *QuestActionsDialog)
    {
        if (QuestActionsDialog->objectName().isEmpty())
            QuestActionsDialog->setObjectName(QString::fromUtf8("QuestActionsDialog"));
        QuestActionsDialog->resize(732, 478);
        buttonBox = new QDialogButtonBox(QuestActionsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(380, 430, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(QuestActionsDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 701, 411));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        actionsEdit = new ScriptEdit(layoutWidget);
        actionsEdit->setObjectName(QString::fromUtf8("actionsEdit"));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier New"));
        actionsEdit->setFont(font);
        actionsEdit->setLineWrapMode(QTextEdit::WidgetWidth);
        actionsEdit->setTabStopWidth(40);

        verticalLayout->addWidget(actionsEdit);


        retranslateUi(QuestActionsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), QuestActionsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), QuestActionsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(QuestActionsDialog);
    } // setupUi

    void retranslateUi(QDialog *QuestActionsDialog)
    {
        QuestActionsDialog->setWindowTitle(QApplication::translate("QuestActionsDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QuestActionsDialog", "Actions", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QuestActionsDialog: public Ui_QuestActionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUESTACTIONSDIALOG_H
