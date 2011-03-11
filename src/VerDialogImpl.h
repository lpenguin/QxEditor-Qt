#ifndef VERDIALOGIMPL_H
#define VERDIALOGIMPL_H
//
#include <QDialog>
#include "ui_VerDialog.h"

#include "BaseGraph.h"
//
class VerDialogImpl : public QDialog, public Ui::VerDialog
{
Q_OBJECT
public:
	Ver *  m_ver;
	int ShowVer(Ver * ver);
	VerDialogImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
	void on_buttonBox_accepted();
private:
        LocationType radio2type ( void );
        void type2radio( LocationType type);
};
#endif






