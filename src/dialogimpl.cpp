#include "dialogimpl.h"
//
DialogImpl::DialogImpl( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f) 
{
	setupUi(this);
        //QGraphicsScene scene;

     
        
	QObject::connect(graphView, SIGNAL( VerClicked( VerItem * , Qt::MouseButton ) ),
					 this, SLOT( VerClicked( VerItem * , Qt::MouseButton ) ));

	QObject::connect(graphView, SIGNAL( EdgeClicked( EdgeItem *, Qt::MouseButton ) ),
					 this, SLOT( EdgeClicked( EdgeItem *, Qt::MouseButton ) ));

	QObject::connect(graphView, SIGNAL( AreaClicked( QPointF point, Qt::MouseButton) ),
					 this, SLOT( AreaClicked( QPointF point, Qt::MouseButton)));

	QObject::connect(graphView, SIGNAL( VersConnected( VerItem *, VerItem *) ),
					 this, SLOT( VersConnected( VerItem *, VerItem *)));
	verDialog = new VerDialogImpl( this );
	edgeDialog= new EdgeDialogImpl( this );	

}
void DialogImpl::VerClicked( VerItem * ver , Qt::MouseButton ){
	verDialog->ShowVer(ver->ver());
}

void DialogImpl::EdgeClicked( EdgeItem * edge, Qt::MouseButton ){
	edgeDialog->ShowEdge( edge->edge() );
}

void DialogImpl::AreaClicked( QPointF point, Qt::MouseButton){
	
}

void DialogImpl::VersConnected( VerItem * ver1, VerItem * ver2){
	
}
