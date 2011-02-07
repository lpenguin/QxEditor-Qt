#ifndef EDGEDIALOGIMPL_H
#define EDGEDIALOGIMPL_H
//
#include <QDialog>
#include "ui_EdgeDialog.h"
#include "Edge.h"
//
class EdgeDialogImpl : public QDialog, public Ui::EdgeDialog
{
Q_OBJECT
public:
	Edge * m_edge;
	int ShowEdge(Edge * edge);
	EdgeDialogImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
	void Reset();
private slots:
	void on_buttonBox_accepted();
};
#endif





