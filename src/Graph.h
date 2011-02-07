#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <QtCore>
#include <QXmlStreamReader>
#include "Edge.h"
#include "Ver.h"

class Ver;
class Edge;

class Graph : public QObject{
private:
	Q_OBJECT
	
	QList<Ver*> m_vers;
	QList<Edge*> m_edges;
	QString m_script;
        QString m_name;
        QString m_description;
public:
	void RemoveEdge(Edge * edge);
	void RemoveVer(Ver * ver);
	void Clean();
	void AddEdge(Edge * edge);
	void AddVer(Ver * ver);
        Edge * FindEdge( Ver * v0, Ver * v1);
	void setEdges( QList<Edge*> value) { m_edges = value; }
	QList<Edge*> edges() { return m_edges; }
	void setVers( QList<Ver*> value) { m_vers = value; }
	QList<Ver*> vers() { return m_vers; }
	void setScript( QString value) { m_script = value; }
        QString name( void ){ return m_name;}
        void setName( QString value ){ m_name = value; }
        QString description( void ){ return m_description; }
        void setDescription( QString value ){ m_description = value; }

	QString script() { return m_script; }
        QString GetNewEdgeId(  );
        QString GetNewVerId(  );
        //void LoadEdges(QXmlStreamReader & xml);
        //void LoadMain(QXmlStreamReader & xml);
	~Graph( void );
	Ver * FindVer(QString id);
	Ver * LoadVer(QXmlStreamReader & xml);
        //Edge * LoadEdge(QXmlStreamReader & xml, Ver * v0);
	Graph( QObject * object = 0 );
        //void Load(QXmlStreamReader & xml);
};
#endif // __GRAPH_H__
