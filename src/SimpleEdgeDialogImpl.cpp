#include "SimpleEdgeDialogImpl.h"
//
SimpleEdgeDialogImpl::SimpleEdgeDialogImpl( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
	m_edge = 0;
}
//


int SimpleEdgeDialogImpl::ShowEdge(BaseEdge * edge)
{
	m_edge = edge;
        actionsEdit->setText( edge->info()->actions());
        conditionsEdit->setPlainText( edge->info()->conditions());
        textEdit->setText( edge->info()->text());
        questionEdit->setText( edge->info()->question());

        edgeIdEdit->setText(m_edge->info()->id());
	return exec();
}

void SimpleEdgeDialogImpl::on_buttonBox_accepted()
{
	if( m_edge ) {
                m_edge->info()->setActions( actionsEdit->toPlainText() );
                m_edge->info()->setConditions( conditionsEdit->toPlainText() );
                m_edge->info()->setId( edgeIdEdit->text() );
                m_edge->info()->setText( textEdit->toPlainText() );
                m_edge->info()->setQuestion( questionEdit->toPlainText() );
	}
	accept();
}

void SimpleEdgeDialogImpl::Reset(){
	actionsEdit->setText( "" );
	conditionsEdit->setPlainText( "" );
	textEdit->setText( "" );
	questionEdit->setText( "" );
	edgeIdEdit->setText( "" );


}
