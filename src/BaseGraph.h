#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <QtCore>

//#include "Edge.h"
//#include "Ver.h"

class BaseInfo;
class BaseVer;
class BaseGraphObject;
class BaseGraph;

class BaseInfo : public QObject{
protected:
    QString m_id;
public:
    enum LocationType{

    };

    BaseInfo(){}
    BaseInfo( QString id, QObject * parent = 0 ):
        m_id(id), QObject(parent){}
    void virtual setId( QString id ){
        m_id = id;
    }

    QString virtual id() const{
        return m_id;
    }
};

class BaseGraphObject : public QObject{
private:
    BaseInfo * m_info;
public:
    BaseGraphObject( BaseInfo * info = 0, QObject * parent = 0):
        m_info(info), QObject(parent){ m_info->setParent(this); }
    void setInfo( BaseInfo * value) { m_info = value; m_info->setParent(this); }
    BaseInfo * info() { return m_info; }
};

class BaseVer : BaseGraphObject{
private:
    QPointF m_pos;
public:
    BaseVer(BaseInfo * info, QPointF pos, QObject * parent = 0):
        BaseGraphObject(info, parent), m_pos(pos){}
    BaseVer(){};
    void setPos( QPointF value) { m_pos = value; }
    QPointF pos() { return m_pos; }
    BaseGraph * parentGraph();
};

class BaseEdge: public BaseGraphObject
{
    Q_OBJECT
private:
    BaseVer * m_v0;
    BaseVer * m_v1;
public:
    BaseEdge(BaseInfo * info, BaseVer * v0, BaseVer * v1, QObject * parent = 0):
        BaseGraphObject( info, parent ), m_v0( v0 ), m_v1 ( v1 ){}
    int ConnectSame(BaseEdge * edge);
    QString toString() const;

    bool Have(BaseVer * v0, BaseVer * v1 = 0);
    BaseGraph * parentGraph();

    //Getters/Setters
    void setV1(  BaseVer * value) { m_v1 = value;  }
    BaseVer * v1() { return m_v1; }
    void setV0(  BaseVer * value) { m_v0 = value; }
    BaseVer * v0() { return m_v0; }

};

class BaseGraph : public BaseGraphObject{
private:
	Q_OBJECT
	
        QList<BaseVer*> m_vers;
        QList<BaseEdge*> m_edges;
public:
        void RemoveEdge(BaseEdge * edge);
        void RemoveVer(BaseVer * ver);
	void Clean();
        void AddEdge(BaseEdge * edge);
        void AddVer(BaseVer * ver);
        BaseEdge * FindEdge( BaseVer * v0, BaseVer * v1);
        void setEdges( QList<BaseEdge*> value) { m_edges = value; }
        QList<BaseEdge*> edges() { return m_edges; }
        void setVers( QList<BaseVer*> value) { m_vers = value; }
        QList<BaseVer*> vers() { return m_vers; }

        QString GetNewEdgeId(  );
        QString GetNewVerId(  );

        ~BaseGraph( void );
        BaseVer * FindVer(QString id);
        BaseGraph( QObject * object = 0 );
};
#endif // __GRAPH_H__
