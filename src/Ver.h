#ifndef __VER_H__
#define __VER_H__

#include <QtCore>
#include <QPointF>
#include "Graph.h"

enum LocationType {
	 start, fail, odinary, win
};

struct VerInfo {
	QString id;
	QString actions;
	QString text;
	LocationType type;
};
class Graph;
class Ver;


class Ver : public QObject{
	
private:
	VerInfo m_info;
	QPointF m_pos;
public:
	Ver(VerInfo info, QPointF pos, QObject * parent = 0);
	Ver(){};
	//Getters/Setters	
	void setPos( QPointF value) { m_pos = value; }
	QPointF pos() { return m_pos; }
	void setInfo( VerInfo value) { m_info = value; }
        VerInfo & info() { return m_info; }
        Graph * parentGraph();
	
	
};
#endif // __VER_H__

