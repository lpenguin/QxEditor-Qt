#include "SimpleVerDialogImpl.h"
//
SimpleVerDialogImpl::SimpleVerDialogImpl( QWidget * parent, Qt::WFlags f)
	: QDialog(parent, f)
{
	setupUi(this);
	
	m_ver = 0;
}
//

LocationType SimpleVerDialogImpl::radio2type ( void ){
    if( odinaryRadio->isChecked())
        return odinary;
    if( startRadio->isChecked())
        return start;
    if( winRadio->isChecked())
        return win;
    if( failRadio->isChecked())
        return fail;
    return odinary;
}

void SimpleVerDialogImpl::type2radio( LocationType type){
    switch( type ){
    case odinary:
        odinaryRadio->setChecked(true);
        break;
    case start:
        startRadio->setChecked(true);
        break;
    case win:
        winRadio->setChecked(true);
        break;
    case fail:
        failRadio->setChecked(true);
        break;

    }
}

int SimpleVerDialogImpl::ShowVer(BaseVer * ver)
{
	m_ver = ver;
        actionsEdit->setText( ver->info()->actions());
        verIdEdit->setText( ver->info()->id() );
        textEdit->setText(ver->info()->text() );
        type2radio( ver->info()->type());
	return exec();
}

void SimpleVerDialogImpl::on_buttonBox_accepted()
{
	if( m_ver ) {
                m_ver->info()->setActions( actionsEdit->toPlainText() );
                m_ver->info()->setId( verIdEdit->text() );
                m_ver->info()->setText( textEdit->toPlainText() );
                m_ver->info()->setType( radio2type() );
	}
	accept();
}
