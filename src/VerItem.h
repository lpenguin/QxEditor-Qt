#ifndef VerItem_H
#define VerItem_H
#include "BaseGraph.h"
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QtGui>
#include <QtCore>

class VerItem : public QGraphicsEllipseItem {
//Q_OBJECT
private:
        BaseVer * m_ver;
	QSizeF m_size;
	QColor m_color;
	QString typeString;
public:
        void setPos ( const QPointF & pos );
        void setPos ( qreal x, qreal y );
	QRectF boundingRect() const;
	void UpdateBrush();
        VerItem( BaseVer * ver, const QSizeF &size = QSizeF(), QGraphicsItem * parent = 0 );
	
        void setVer(BaseVer * value) { m_ver = value; }
        BaseVer * ver() { return m_ver; }
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
