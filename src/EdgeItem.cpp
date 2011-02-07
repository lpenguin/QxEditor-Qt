#include "EdgeItem.h"

float DistancePoint(QPointF p0, QPointF p1){
	QPointF delta = p0 - p1;
	return sqrt( pow( delta.x(), 2 ) +  pow( delta.x() , 2) );
}

//
EdgeItem::EdgeItem( Edge * edge, QPointF endPoint, float curvature, float selectDistance, QGraphicsItem * parent  ) 
	: QGraphicsPathItem(  parent )
{
    m_edge = edge;
    m_curvature = curvature;
    m_endPoint = endPoint;
    m_color = Qt::black;
    m_selectDistance = selectDistance;
    
    m_pen =  QPen(m_color, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    points = 0;
    pointsCount = 0;

	UpdatePath();
    setAcceptHoverEvents(true);
    setParentItem( parent );
    setFlag(QGraphicsItem::ItemIsSelectable, true);



}
//
EdgeItem::~EdgeItem(){
	qDebug()<<"Destructor EdgeItem"<<toString();
	if( points ) 
		delete []points;
}
//void EdgeItem::UpdatePath()
//{
//	//Control point
//	double c,d,l;
//        d=(m_p1 - m_p0).x();
//        c=(m_p1 - m_p0).y();
//    QPointF control;	
//	QPointF control1;	
//	QPointF control2;	
//	double kpower = 15;
//	
//	l = sqrt(d * d + c * c);
//    control1.setX( 0 + m_curve * kpower * c / l  );
//    control1.setY( 0 - m_curve * kpower * d / l  );
//    control2.setX( d  + m_curve * kpower * c / l  );
//    control2.setY( c  - m_curve * kpower * d / l  );
//    control.setX( d/2 + m_curve  * kpower * c / l * 0.75  );
//    control.setY( c/2 - m_curve  * kpower * d / l *0.75 );
//	double angle = atan2( c, -d );
//	double anglep = angle + 3.14 / 180 * 15;
//	double anglem = angle - 3.14 / 180 * 15;
//	m_path = QPainterPath();
//	m_path.moveTo(0,0);
//	//m_path.lineTo(m_p1 - m_p0 );
//    //m_path.moveTo(m_p0);
//    //m_path.lineTo(m_p1);
//    //m_path.lineTo( m_p1 - m_p0 );
//     m_path.cubicTo(control1, control2 , m_p1 - m_p0);
////     m_path.moveTo(control );
//// 	 m_path.lineTo( control.x()  + 15  * cos( anglem),control.y() + 10  * sin( anglem) );
////     m_path.moveTo(control);
//// 	 m_path.lineTo( control.x() + 15  * cos( anglep),control.y() + 10  * sin( anglep) );
////	//m_path.moveTo(0,0);
//    //m_path.lineTo(control1);
//    //m_path.lineTo(control2);
//   // m_path.lineTo(m_p1 - m_p0);
//}



//bool EdgeItem::Have(Ver * v0, Ver * v1)
//{
	//return m_v0->ver() == v0 && m_v1->ver() == v1;
//}


void EdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen selectedPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen unselectedPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	
     if( isSelected() )
         painter->setPen(selectedPen);
     else
         painter->setPen(unselectedPen);
	
    painter->drawPath( path() );
    painter->drawPath( m_arrowPath );

}

QRectF EdgeItem::boundingRect() const
{
    //qDebug("rect");
   // QRectF r = m_path.boundingRect();
  //  qDebug()<<(void*)this<<" left "<<r.left()<<" top "<<r.top()<<" width  "<<r.width()<<" height "<<r.height();
    QPainterPathStroker s;
    s.setWidth(20);
    return s.createStroke( path() ).boundingRect();
        //QRectF(0,0, 20*m_curve,m_p1.x() - m_p0.x());//
}
QPainterPath EdgeItem::shape () const{
	QPainterPathStroker s;
	s.setWidth(20);
	return s.createStroke( path() );
}

void EdgeItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
//	qDebug()<<"press on "<<(void*)this;
}
//bool EdgeItem::contains ( const QPointF & point ) const{
//    qDebug()<<"cnt "<<(void*)this<<" "<<point.x()<<" "<<point.y();
//    QPointF m = mapFromScene(point);
//    qDebug()<<"map "<<(void*)this<<" "<<m.x()<<" "<<m.y();
//    qDebug()<<"pos "<<(void*)this<<" "<<pos().x()<<" "<<pos().y();
//    qDebug()<<"rct "<<(void*)this<<" "<<boundingRect();
//    qDebug()<<"";
//    return m_path.contains(point);
//    //m_pen =  QPen(m_color, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
//        //qDebug()<<"cnt "<<(void*)this<<" "<<point.x()<<" "<<point.y();
//}

void EdgeItem::UpdateArrow(){

    double c,d,l;
    d=(m_endPoint - pos()).x();
    c=(m_endPoint - pos()).y();

    double angle = atan2( c, d);
    double anglep = angle + 3.1415 / 180 * 15;
    double anglem = angle - 3.1415 / 180 * 15;
    QPointF control = MidPoint();
    control = BezierValue( 0.5, control );
    m_arrowPath = QPainterPath();
    m_arrowPath.moveTo( control );
    m_arrowPath.lineTo( control.x()  - 15  * cos( anglem ), control.y() - 15  * sin( anglem) );
    m_arrowPath.moveTo( control );
    m_arrowPath.lineTo( control.x() - 15  * cos( anglep ), control.y() - 15  * sin( anglep) );
}

void EdgeItem::UpdatePath( void ){
	if( points )
		delete []points;

	QPainterPath m_path;
	m_path.moveTo(0, 0);

	QPointF control = MidPoint();
        double dist = DistancePoint(QPointF(0, 0) , control) + DistancePoint(control, m_endPoint);
	

	pointsCount = (int)(dist / m_selectDistance) + 1;
	points = new QPointF[pointsCount];
	QPointF point;
	for (int i = 0; i < pointsCount; i++){
		point = BezierValue( (double)i / ( pointsCount - 1), control );
		m_path.lineTo( point );
		points[i] = point;
	}
	
        setPath( m_path );
        UpdateArrow();
}

QPointF EdgeItem::BezierValue( double t, QPointF pm ){
	double r1, r2, r3;
    r1 = (1 - t) * (1 - t);
    r2 = 2 * t * (1 - t);
    r3 = t * t;
    return QPointF( r2 * pm.x() + r3 * (m_endPoint.x() - pos().x() ),r2 * pm.y() + r3 * ( m_endPoint.y() - pos().y() ));

}

QPointF EdgeItem::MidPoint( void ){

	double c,d,l;
	d=m_endPoint.x() - pos().x();
	c=m_endPoint.y() - pos().y();

	l = sqrt(d * d + c * c);
	return QPointF( d / 2 + m_curvature * c / l ,  c / 2 - m_curvature * d / l );
}

qreal EdgeItem::Distance( QPointF point){
	qreal minDist = 99999;
	qreal dist;
	for(int i = 0; i < pointsCount; i++){
		dist = DistancePoint( points[i], point);
		if( minDist > dist )
			minDist = dist;
	}
	return minDist;
}
QString EdgeItem::toString(){
		return QString("EdgeItem( id: %1, v0: %2, v1: %3, this: %4)")
		.arg( m_edge->info().id )
		.arg( m_edge->v0()->info().id )
		.arg( m_edge->v1()->info().id )
		.arg( (int)this );
	
}
