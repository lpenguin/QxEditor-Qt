#ifndef MAINDIALOGIMPL_H
#define MAINDIALOGIMPL_H
//
#include <QMainWindow>
#include <QList>
#include "ui_MainDialog.h"
#include "GraphView.h"
#include "Graph.h"
#include "VerDialogImpl.h"
#include "EdgeDialogImpl.h"
#include "QuestActionsDialog.h"
#include "QuestSettingsDialog.h"

class QAction;
class QMenu;
class QTextEdit;
 
class MainDialogImpl : public QMainWindow, public Ui::MainDialog
{
Q_OBJECT
public:
	MainDialogImpl( QWidget * parent = 0, Qt::WFlags f = 0 );

private:
        //Dialogs
	VerDialogImpl * verDialog;
	EdgeDialogImpl * edgeDialog;
        QuestActionsDialog * questActionsDialog;
        QuestSettingsDialog * questSettingsDialog;
private slots:
	void on_actionOpen_triggered();
	void on_actionSave_triggered();
	void on_actionSave_as_triggered();
        void on_actionSettings_triggered();
        void on_actionActions_triggered();
    void newFile();
    void open();
    void save();
    void saveAs();
    void openRecentFile();
    void about();
	void VerClicked( VerItem * , Qt::MouseButton );
	void EdgeClicked( EdgeItem *, Qt::MouseButton );
	void AreaClicked( QPointF point, Qt::MouseButton);
	void VersConnected( VerItem *, VerItem *);

private:
     void createActions();
     void createMenus();
     void loadFile(const QString &fileName);
     void saveFile(const QString &fileName);
     void setCurrentFile(const QString &fileName);
     void updateRecentFileActions();
     QString strippedName(const QString &fullFileName);

     QString curFile;


     enum { MaxRecentFiles = 5 };
     QAction *recentFileActs[MaxRecentFiles];
}; 
#endif





