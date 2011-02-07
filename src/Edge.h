#ifndef EDGE_H
#define EDGE_H
#include <QtCore>
#include <QObject>
#include "Ver.h"
#include "Graph.h"
//

//

struct EdgeInfo{
	QString id;
	QString actions;
	QString conditions;
	QString text;
	QString question;
};
class Graph;
class Ver;

class Edge: public QObject
{
private:
	Q_OBJECT
	Ver * m_v0;
	Ver * m_v1;
	EdgeInfo m_info;
public:
	QString toString();
	Edge(Ver * v0, Ver * v1, QObject * parent = 0);
	Edge(EdgeInfo info, Ver * v0, Ver * v1, QObject * parent = 0);
	~Edge();
    int ConnectSame(Edge * edge);
        
	//Getters/Setters
    void setV1(  Ver * value) { m_v1 = value;  }
    Ver * v1() { return m_v1; }
    void setV0(  Ver * value) { m_v0 = value; }
    Ver * v0() { return m_v0; }
	void set_info( EdgeInfo value) { m_info = value; }
	EdgeInfo & info() { return m_info; }
	bool Have(Ver * v0, Ver * v1 = 0);
        Graph * parentGraph();
	
};
#endif
