#ifndef VerItem_H
#define VerItem_H
#include "BaseGraph.h"
#include "SimpleGraph.h"
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QtGui>
#include <QtCore>

using namespace Graphs;

class VerItem : public QGraphicsEllipseItem {
//Q_OBJECT
private:
        Ver * m_ver;
	QSizeF m_size;
	QColor m_color;
	QString typeString;
public:
        void setPos ( const QPointF & pos );
        void setPos ( qreal x, qreal y );
	QRectF boundingRect() const;
	void UpdateBrush();
        VerItem( Ver * ver, const QSizeF &size = QSizeF(), QGraphicsItem * parent = 0 );
	
        void setVer(Ver * value) { m_ver = value; }
        Ver * ver() { return m_ver; }
//	VerItem(Ver * ver);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);
                
	//enum { Type = UserType + 2 };

    int type() const
    {
        return UserType + 2;
    }

protected:
    //void hoverEnterEvent ( QGraphicsSceneMouseEvent * event );
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
	//void hoverMoveEvent ( QGraphicsSceneHoverEvent * event );
};
#endif
