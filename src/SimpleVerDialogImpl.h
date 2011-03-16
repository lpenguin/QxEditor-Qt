#ifndef VERDIALOGIMPL_H
#define VERDIALOGIMPL_H
//
#include <QDialog>
#include "ui_VerDialog.h"
#include "BaseGraph.h"
#include "SimpleGraph.h"
//
class SimpleVerDialogImpl : public QDialog, public Ui::VerDialog
{
Q_OBJECT
public:
        BaseVer *  m_ver;
        int ShowVer(BaseVer * ver);
        SimpleVerDialogImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
	void on_buttonBox_accepted();
private:
        SimpleVerInfo::VerType radio2type ( void );
        void type2radio( SimpleVerInfo::VerType type);
};
#endif






