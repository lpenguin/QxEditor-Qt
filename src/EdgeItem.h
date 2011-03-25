#ifndef EdgeItem_H
#define EdgeItem_H
//
#include <QGraphicsItem>
#include <QtGui>
#include <QtCore>
#include "BaseGraph.h"
//

//float Distance(QPointF p0, QPointF p1);

using namespace Graphs;

class EdgeItem : public QGraphicsPathItem {
    //Q_OBJECT
private:
    QPointF m_endPoint;
    Edge * m_edge;
    QPainterPath m_arrowPath;
    qreal m_curvature;
    QColor m_color;
    QPen m_pen;
    qreal m_selectDistance;
    QList<QPointF> points;
    int pointsCount;

    QPointF BezierValue( double t, QPointF pm  );
    QPointF MidPoint();
public:
    EdgeItem(Edge * edge, QPointF endPoint, float curvature, float selectDistance, QGraphicsItem * parent = 0);
    ~EdgeItem();
    QString toString();
    void setColor( QColor value) { m_color = value; }
    QColor color() { return m_color; }
    void setEndPoint(QPointF value){ m_endPoint = value; }
    QPointF endPoint(){ return m_endPoint; }
    void setEdge( Edge * value) { m_edge = value; }
    Edge * edge() { return m_edge; }
    void setCurvature( int value) { m_curvature = value; UpdatePath();}
    int curvature() { return m_curvature; }

    void UpdatePath();
    void UpdateArrow();
    qreal Distance( QPointF point);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape () const;
    //bool contains ( const QPointF & point ) const;
    
    //enum { Type = UserType + 1 };

    int type() const
    {
        return UserType + 1;
    }
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

};
#endif
