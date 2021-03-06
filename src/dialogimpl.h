#ifndef DIALOGIMPL_H
#define DIALOGIMPL_H
//
#include <QDialog>
#include <QXmlStreamReader>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsView>
#include <QPushButton>
#include "ui_dialog.h"


#include "GraphView.h"
#include "BaseGraph.h"
#include "VerDialog.h"
#include "EdgeDialog.h"

//
class DialogImpl : public QDialog, public Ui::Dialog
{
Q_OBJECT
public:
	DialogImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
private:
        VerDialog * verDialog;
        EdgeDialog * edgeDialog;
private slots:
	void VerClicked( VerItem * , Qt::MouseButton );
	void EdgeClicked( EdgeItem *, Qt::MouseButton );
	void AreaClicked( QPointF point, Qt::MouseButton);
	void VersConnected( VerItem *, VerItem *);
};
#endif




