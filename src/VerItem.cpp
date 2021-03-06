#include "VerItem.h"
//
VerItem::VerItem( Ver * ver, const QSizeF &size, QGraphicsItem * parent )
	:  QGraphicsEllipseItem( parent ),  m_ver( ver ), m_size( size )
{
	UpdateBrush();
	setRect( QRectF( -m_size.width()/2, -m_size.height()/2, m_size.width(), m_size.height() ) );
	//setPos( rect.center() );
	setAcceptHoverEvents(true);
	setParentItem( parent );
}
//
void VerItem::setPos ( const QPointF & pos ){
    QGraphicsEllipseItem::setPos( pos );
}

void VerItem::setPos ( qreal x, qreal y) {
    setPos( QPointF(x, y));
}


void VerItem::UpdateBrush()
{
//    BaseInfo * info = m_ver->info();
//    SimpleVerInfo * simpleInfo;
//    if( simpleInfo = qobject_cast<SimpleVerInfo*>( m_ver->info() )){
    VerInfo* info = (VerInfo*) (m_ver->info());
    switch( info->verType()){
    case SimpleVerInfo::win:
        m_color =  QColor( Qt::blue);
        typeString = "w";
        break;
    case SimpleVerInfo::start:
        m_color =  QColor( Qt::green) ;
        typeString = "s";
        break;
    case SimpleVerInfo::fail:
        m_color =  QColor( Qt::red);
        typeString = "f";
        break;
    case SimpleVerInfo::odinary:
        m_color =  QColor( Qt::gray );
        typeString = "";
        break;
    }
//    }
}

void VerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget){

//	if( isSelected() )
//		painter->setBrush(Qt::lightGray);
//	else
//		painter->setBrush(Qt::white);
    UpdateBrush();
    painter->setBrush(Qt::white);
    if (option->state.testFlag(QStyle::State_MouseOver))
    {
        painter->setBrush(QColor( 230, 227, 228 ));
    }
	
    painter->setPen(QPen(m_color, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setRenderHint(QPainter::Antialiasing );
    painter->drawEllipse( rect()  );//QRectF( pos() - m_rect.size() / 2, m_rect.size()) );

}
QRectF VerItem::boundingRect() const{
	//return QRectF( m_rect );
	return rect();
}


void VerItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
 	QGraphicsEllipseItem::mousePressEvent(event);
}

