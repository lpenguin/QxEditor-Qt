#ifndef QUESTLIBRARIESDIALOGIMPL_H
#define QUESTLIBRARIESDIALOGIMPL_H
//
#include <QDialog>
#include "ui_QuestLibrariesDialog.h"
//
class QuestLibrariesDialogImpl : public QDialog, public Ui::Dialog
{
Q_OBJECT
public:
	void ShowGraph(Graph * graph);
	QuestLibrariesDialogImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
};
#endif





