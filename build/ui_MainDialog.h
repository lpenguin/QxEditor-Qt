/********************************************************************************
** Form generated from reading UI file 'MainDialog.ui'
**
** Created: Tue 1. Feb 20:18:11 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDIALOG_H
#define UI_MAINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "GraphView.h"

QT_BEGIN_NAMESPACE

class Ui_MainDialog
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionNew;
    QAction *actionExit;
    QAction *actionAbout;
    QAction *action123;
    QAction *actionActions;
    QAction *actionSettings;
    QAction *actionSettings_2;
    QAction *actionUndo;
    QAction *actionRedot;
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    GraphView *graphView;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuRecent;
    QMenu *menuHelp;
    QMenu *menuQuest;
    QMenu *menuEdit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainDialog)
    {
        if (MainDialog->objectName().isEmpty())
            MainDialog->setObjectName(QString::fromUtf8("MainDialog"));
        MainDialog->resize(622, 525);
        actionOpen = new QAction(MainDialog);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(MainDialog);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave_as = new QAction(MainDialog);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionNew = new QAction(MainDialog);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionExit = new QAction(MainDialog);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionAbout = new QAction(MainDialog);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        action123 = new QAction(MainDialog);
        action123->setObjectName(QString::fromUtf8("action123"));
        actionActions = new QAction(MainDialog);
        actionActions->setObjectName(QString::fromUtf8("actionActions"));
        actionSettings = new QAction(MainDialog);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        actionSettings_2 = new QAction(MainDialog);
        actionSettings_2->setObjectName(QString::fromUtf8("actionSettings_2"));
        actionUndo = new QAction(MainDialog);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        actionRedot = new QAction(MainDialog);
        actionRedot->setObjectName(QString::fromUtf8("actionRedot"));
        centralwidget = new QWidget(MainDialog);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 611, 481));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        graphView = new GraphView(verticalLayoutWidget);
        graphView->setObjectName(QString::fromUtf8("graphView"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphView->sizePolicy().hasHeightForWidth());
        graphView->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(graphView);

        MainDialog->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainDialog);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 622, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuRecent = new QMenu(menuFile);
        menuRecent->setObjectName(QString::fromUtf8("menuRecent"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuQuest = new QMenu(menubar);
        menuQuest->setObjectName(QString::fromUtf8("menuQuest"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        MainDialog->setMenuBar(menubar);
        statusbar = new QStatusBar(MainDialog);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainDialog->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuQuest->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);
        menuFile->addSeparator();
        menuFile->addAction(menuRecent->menuAction());
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionAbout);
        menuQuest->addAction(actionSettings);
        menuQuest->addAction(actionActions);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedot);
        menuEdit->addSeparator();
        menuEdit->addAction(actionSettings_2);

        retranslateUi(MainDialog);

        QMetaObject::connectSlotsByName(MainDialog);
    } // setupUi

    void retranslateUi(QMainWindow *MainDialog)
    {
        MainDialog->setWindowTitle(QApplication::translate("MainDialog", "QxEditor (Qt Port)", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainDialog", "Open...", 0, QApplication::UnicodeUTF8));
        actionOpen->setShortcut(QApplication::translate("MainDialog", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainDialog", "Save...", 0, QApplication::UnicodeUTF8));
        actionSave->setShortcut(QApplication::translate("MainDialog", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionSave_as->setText(QApplication::translate("MainDialog", "Save as...", 0, QApplication::UnicodeUTF8));
        actionSave_as->setShortcut(QApplication::translate("MainDialog", "Ctrl+Shift+S", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("MainDialog", "New...", 0, QApplication::UnicodeUTF8));
        actionNew->setShortcut(QApplication::translate("MainDialog", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainDialog", "E&xit", 0, QApplication::UnicodeUTF8));
        actionExit->setShortcut(QApplication::translate("MainDialog", "Alt+X", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainDialog", "About", 0, QApplication::UnicodeUTF8));
        action123->setText(QApplication::translate("MainDialog", "123", 0, QApplication::UnicodeUTF8));
        actionActions->setText(QApplication::translate("MainDialog", "Actions", 0, QApplication::UnicodeUTF8));
        actionSettings->setText(QApplication::translate("MainDialog", "Settings", 0, QApplication::UnicodeUTF8));
        actionSettings_2->setText(QApplication::translate("MainDialog", "Settings", 0, QApplication::UnicodeUTF8));
        actionSettings_2->setShortcut(QApplication::translate("MainDialog", "Ctrl+P, Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionUndo->setText(QApplication::translate("MainDialog", "Undo", 0, QApplication::UnicodeUTF8));
        actionRedot->setText(QApplication::translate("MainDialog", "Redo", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainDialog", "File", 0, QApplication::UnicodeUTF8));
        menuRecent->setTitle(QApplication::translate("MainDialog", "Recent", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainDialog", "Help", 0, QApplication::UnicodeUTF8));
        menuQuest->setTitle(QApplication::translate("MainDialog", "Quest", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainDialog", "Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainDialog: public Ui_MainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDIALOG_H
