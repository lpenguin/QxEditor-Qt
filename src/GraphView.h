#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H
//
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtCore>
#include "BaseGraph.h"
#include "VerItem.h"
#include "EdgeItem.h"
#include "JSONGraphReader.h"
#include "JSONGraphWriter.h"
#include "QMGraphReader.h"
#include "QlQMInfoReader.h"
//
	enum Types {EdgeType = QGraphicsItem::UserType + 1,
		 VerType = QGraphicsItem::UserType + 2};

class GraphView : public QGraphicsView
{
    Q_OBJECT
private:
    Graph * m_graph;
    //QGraphicsItemGroup m_vers;
    // QGraphicsItemGroup m_edges;
    QList<VerItem *> m_vers;
    QList<EdgeItem *> m_edges;
    int m_verSize;
    int m_gridSize;
    VerItem * markedVer;
    bool movingVer;

    void AppendEdge( Edge * edge, QPointF pos, QPointF endPoint );
    void AppendVer( Ver * ver, QPointF pos );
    QGraphicsItem * minItem( const QPointF & pos );
public:
    void RemoveEdge(EdgeItem * edge);
    void RemoveVer(VerItem * ver);
    int Curvature(EdgeItem * edge);
    //	void setGraph(Graph * graph);
    VerItem * FindVer(Ver * v);
    ~GraphView();
    void CleanGraph();
    void LoadGraph(Graph * graph);
    void Load(const QString & filename, AbstractGraphReader * reader);
    void Save(const QString & filename, AbstractGraphWriter * writer);
    Graph * graph() { return m_graph; }
    GraphView( QWidget * parent = 0  );
    void AddVer( Ver * ver, QPointF pos);
    void AddEdge( Edge * edge, QPointF pos, QPointF endPoint );



protected:
    void mouseMoveEvent ( QMouseEvent * e );
    void mousePressEvent ( QMouseEvent * e );
    void mouseReleaseEvent ( QMouseEvent * e );
signals:
    void VerClicked( VerItem * , Qt::MouseButton );
    void EdgeClicked( EdgeItem *, Qt::MouseButton );
    void AreaClicked( QPointF , Qt::MouseButton);
    void VersConnected( VerItem *, VerItem *);
};


	 
#endif
