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
Q_OBJECT
protected:
    QString m_id;
public:
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

class BaseVerInfo : public BaseInfo{
    Q_OBJECT
public:
    enum VerType{
        odinary, win, fail, start
    };
private:
    VerType m_verType;
public:
    BaseVerInfo( VerType verType, QString id, QObject * parent = 0 ):
        BaseInfo(id, parent), m_verType(verType)
    {}

    BaseVerInfo( QString id, QObject * parent = 0 ):
        BaseInfo(id, parent)
    {}

    BaseVerInfo():
        BaseInfo(QString::null, 0)
    {}
    VerType verType() const{
        return m_verType;
    }

    void setVerType( VerType verType ){
        m_verType = verType;
    }
};

class BaseEdgeInfo : public BaseInfo{
    Q_OBJECT
public:
    BaseEdgeInfo( QString id, QObject * parent = 0):
        BaseInfo(id, parent)
    {}

    BaseEdgeInfo():
        BaseInfo(QString::null, 0)
    {}
};

class BaseGraphInfo : public BaseInfo {
    Q_OBJECT
private:
    QString m_name;
    QString m_description;
public:
    BaseGraphInfo( QString name, QString description, QString id = QString::null, QObject * parent = 0 ):
        BaseInfo(id, parent ), m_name(name), m_description(description )
    {}
    BaseGraphInfo( QString id = QString(), QObject * parent = 0 ):
        BaseInfo(id, parent)
    {}

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

class BaseVer : public QObject{
private:
    QPointF m_pos;
    BaseVerInfo * m_info;
public:
    BaseVer(BaseVerInfo * info, QPointF pos = QPointF(), QObject * parent = 0):
        m_info(info), QObject(parent), m_pos(pos){}
    void setPos( QPointF value) { m_pos = value; }
    QPointF pos() { return m_pos; }
    BaseGraph * parentGraph();
    void setInfo( BaseVerInfo * value) { m_info = value; m_info->setParent(this); }
    BaseVerInfo * info() { return m_info; }
};

class BaseEdge: public QObject
{
    Q_OBJECT
private:
    BaseVer * m_v0;
    BaseVer * m_v1;
    BaseEdgeInfo * m_info;
public:
    BaseEdge(BaseEdgeInfo * info, BaseVer * v0, BaseVer * v1, QObject * parent = 0):
         m_info(info), QObject(parent), m_v0( v0 ), m_v1 ( v1 ){}
    BaseEdge(BaseVer * v0, BaseVer * v1, QObject * parent = 0):
        QObject( parent ), m_v0( v0 ), m_v1 ( v1 ), m_info(0){}
    int ConnectSame(BaseEdge * edge);
    QString toString() const;

    bool Have(BaseVer * v0, BaseVer * v1 = 0);
    BaseGraph * parentGraph();

    //Getters/Setters
    void setV1(  BaseVer * value) { m_v1 = value;  }
    BaseVer * v1() { return m_v1; }
    void setV0(  BaseVer * value) { m_v0 = value; }
    BaseVer * v0() { return m_v0; }
    void setInfo( BaseEdgeInfo * value) { m_info = value; m_info->setParent(this); }
    BaseEdgeInfo * info() { return m_info; }
};

class BaseGraph : public QObject{
private:
	Q_OBJECT
        QList<BaseVer*> m_vers;
        QList<BaseEdge*> m_edges;
        BaseGraphInfo * m_info;
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
        BaseGraph( QObject * parent = 0 ):
            QObject(parent)
        {}
        BaseGraph( BaseGraphInfo * info, QObject * object = 0 );
        void setInfo( BaseGraphInfo * value) { m_info = value; m_info->setParent(this); }
        BaseGraphInfo * info() { return m_info; }
//        BaseGraph( BaseInfo * info, QList<BaseVer*> vers, QList<BaseEdge*> edges, QObject * object = 0 );
};
#endif // __GRAPH_H__
