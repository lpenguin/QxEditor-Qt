#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <QtCore>

//#include "Edge.h"
//#include "Ver.h"

namespace Graphs{

class Info;
class Ver;
class Graph;

class Info : public QObject{
Q_OBJECT
protected:
    QString m_id;
public:
    Info(){}
    Info( QString id, QObject * parent = 0 ):
        m_id(id), QObject(parent){}
    void virtual setId( QString id ){
        m_id = id;
    }

    QString virtual id() const{
        return m_id;
    }
};

class VerInfo : public Info{
    Q_OBJECT
public:
    enum VerType{
        odinary, win, fail, start
    };
private:
    VerType m_verType;
public:
    VerInfo( VerType verType, QString id, QObject * parent = 0 ):
        Info(id, parent), m_verType(verType)
    {}

    VerInfo( QString id, QObject * parent = 0 ):
        Info(id, parent)
    {}

    VerInfo():
        Info(QString::null, 0)
    {}
    VerType verType() const{
        return m_verType;
    }

    void setVerType( VerType verType ){
        m_verType = verType;
    }
};

class EdgeInfo : public Info{
    Q_OBJECT
public:
    EdgeInfo( QString id, QObject * parent = 0):
        Info(id, parent)
    {}

    EdgeInfo():
        Info(QString::null, 0)
    {}
};

class GraphInfo : public Info {
    Q_OBJECT
private:
    QString m_name;
    QString m_description;
    QStringList m_libraries;
public:
    GraphInfo( QString name, QString description, QStringList libraries, QString id = QString::null, QObject * parent = 0 ):
        Info(id, parent ), m_name(name), m_description(description ), m_libraries(libraries)
    {}
    GraphInfo( QString id = QString(), QObject * parent = 0 ):
        Info(id, parent)
    {}

    QStringList libraries() const {
        return m_libraries;
    }

    void setLibraries( QStringList libraries ){
        m_libraries = libraries;
    }

    void setName( QString name ){
        m_name = name;
    }
    QString name() const{
        return m_name;
    }

    void setDescription( QString description ){
        m_description = description;
    }
    QString description() const{
        return m_description;
    }
};

//class BaseGraphObject : public QObject{
//protected:
//    BaseInfo * m_info;
//public:
//    BaseGraphObject( BaseInfo * info = 0, QObject * parent = 0):
//        m_info(info), QObject(parent){ m_info->setParent(this); }
//    void setInfo( BaseInfo * value) { m_info = value; m_info->setParent(this); }
//    BaseInfo * info() { return m_info; }
//};

class Ver : public QObject{
private:
    QPointF m_pos;
    VerInfo * m_info;
public:
    Ver(VerInfo * info, QPointF pos = QPointF(), QObject * parent = 0):
        m_info(info), QObject(parent), m_pos(pos){}
    void setPos( QPointF value) { m_pos = value; }
    QPointF pos() { return m_pos; }
    Graph * parentGraph();
    void setInfo( VerInfo * value) { m_info = value; m_info->setParent(this); }
    VerInfo * info() { return m_info; }
};

class Edge: public QObject
{
    Q_OBJECT
private:
    Ver * m_v0;
    Ver * m_v1;
    EdgeInfo * m_info;
public:
    Edge(EdgeInfo * info, Ver * v0, Ver * v1, QObject * parent = 0):
         m_info(info), QObject(parent), m_v0( v0 ), m_v1 ( v1 ){}
    Edge(Ver * v0, Ver * v1, QObject * parent = 0):
        QObject( parent ), m_v0( v0 ), m_v1 ( v1 ), m_info(0){}
    int ConnectSame(Edge * edge);
    QString toString() const;

    bool Have(Ver * v0, Ver * v1 = 0);
    Graph * parentGraph();

    //Getters/Setters
    void setV1(  Ver * value) { m_v1 = value;  }
    Ver * v1() { return m_v1; }
    void setV0(  Ver * value) { m_v0 = value; }
    Ver * v0() { return m_v0; }
    void setInfo( EdgeInfo * value) { m_info = value; m_info->setParent(this); }
    EdgeInfo * info() { return m_info; }
};

class Graph : public QObject{
private:
	Q_OBJECT
        QList<Ver*> m_vers;
        QList<Edge*> m_edges;
        GraphInfo * m_info;
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

        QString GetNewEdgeId(  );
        QString GetNewVerId(  );

        ~Graph( void );
        Ver * FindVer(QString id);
        Graph( QObject * parent = 0 ):
            QObject(parent)
        {}
        Graph( GraphInfo * info, QObject * object = 0 );
        void setInfo( GraphInfo * value) { m_info = value; m_info->setParent(this); }
        GraphInfo * info() { return m_info; }
//        BaseGraph( BaseInfo * info, QList<BaseVer*> vers, QList<BaseEdge*> edges, QObject * object = 0 );
};
}
#endif // __GRAPH_H__
