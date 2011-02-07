#include "EdgeDialogImpl.h"
//
EdgeDialogImpl::EdgeDialogImpl( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
	m_edge = 0;
}
//


int EdgeDialogImpl::ShowEdge(Edge * edge)
{
	m_edge = edge;
	actionsEdit->setText( edge->info().actions);
	conditionsEdit->setPlainText( edge->info().conditions);
	textEdit->setText( edge->info().text);
	questionEdit->setText( edge->info().question);

	edgeIdEdit->setText(m_edge->info().id);
	return exec();
}

void EdgeDialogImpl::on_buttonBox_accepted()
{
	if( m_edge ) {
		m_edge->info().actions = actionsEdit->toPlainText();
		m_edge->info().conditions = conditionsEdit->toPlainText();
		m_edge->info().id = edgeIdEdit->text();
		m_edge->info().text = textEdit->toPlainText();
		m_edge->info().question = questionEdit->toPlainText();
	}
	accept();
}

void EdgeDialogImpl::Reset(){
	actionsEdit->setText( "" );
	conditionsEdit->setPlainText( "" );
	textEdit->setText( "" );
	questionEdit->setText( "" );
	edgeIdEdit->setText( "" );


}
