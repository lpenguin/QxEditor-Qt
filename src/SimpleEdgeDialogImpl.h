#ifndef EDGEDIALOGIMPL_H
#define EDGEDIALOGIMPL_H
//
#include <QDialog>
#include "ui_EdgeDialog.h"
#include "BaseGraph.h"
#include "SimpleGraph.h"
//
class SimpleEdgeDialogImpl : public QDialog, public Ui::EdgeDialog
{
Q_OBJECT
public:
        BaseEdge * m_edge;
        int ShowEdge(BaseEdge * edge);
        SimpleEdgeDialogImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
	void Reset();
private slots:
	void on_buttonBox_accepted();
};
#endif





