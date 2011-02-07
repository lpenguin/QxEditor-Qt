/********************************************************************************
** Form generated from reading UI file 'QuestSettingsDialog.ui'
**
** Created: Tue 1. Feb 20:18:11 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUESTSETTINGSDIALOG_H
#define UI_QUESTSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuestSettingsDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLineEdit *questNameEdit;
    QLabel *label;
    QPlainTextEdit *questDescriptionEdit;

    void setupUi(QDialog *QuestSettingsDialog)
    {
        if (QuestSettingsDialog->objectName().isEmpty())
            QuestSettingsDialog->setObjectName(QString::fromUtf8("QuestSettingsDialog"));
        QuestSettingsDialog->resize(715, 474);
        buttonBox = new QDialogButtonBox(QuestSettingsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(350, 430, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        widget = new QWidget(QuestSettingsDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 691, 411));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        questNameEdit = new QLineEdit(widget);
        questNameEdit->setObjectName(QString::fromUtf8("questNameEdit"));

        verticalLayout->addWidget(questNameEdit);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        questDescriptionEdit = new QPlainTextEdit(widget);
        questDescriptionEdit->setObjectName(QString::fromUtf8("questDescriptionEdit"));

        verticalLayout->addWidget(questDescriptionEdit);


        retranslateUi(QuestSettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), QuestSettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), QuestSettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(QuestSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *QuestSettingsDialog)
    {
        QuestSettingsDialog->setWindowTitle(QApplication::translate("QuestSettingsDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QuestSettingsDialog", "Quest name", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QuestSettingsDialog", "Quest description", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QuestSettingsDialog: public Ui_QuestSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUESTSETTINGSDIALOG_H
