#include "BaseGraph.h"

BaseGraph::BaseGraph( BaseGraphInfo * info, QObject * object ):
    m_info( info ), QObject( object ){

}

BaseVer * BaseGraph::FindVer(QString id)
{
        BaseVer * v;
	foreach(v, m_vers){
                if( v->info()->id() == id )
			return v;
	}
 	return 0;
}

QString BaseGraph::GetNewVerId(  ){
    QString prefix = "L";
    QString intString;
    int maxId = 0;
    int id;

    bool ok;
    foreach(BaseVer * ver, m_vers){
        intString = ver->info()->id();
        intString.replace(QRegExp("^"+prefix),"");
        id = intString.toInt( &ok );
        if( ok && maxId < id){
            maxId = id;
        }
    }

    return prefix+QString::number(++maxId);
}

QString BaseGraph::GetNewEdgeId(  ){
    QString prefix = "P";
    QString intString;
    int maxId = 0;
    int id;

    bool ok;
    foreach(BaseEdge * edge, m_edges){
        intString = edge->info()->id();
        intString.replace(QRegExp("^"+prefix),"");
        id = intString.toInt( &ok );
        if( ok && maxId < id){
            maxId = id;
        }
    }
    return prefix+QString::number(++maxId);
}



BaseGraph::~BaseGraph()
{
	qDebug()<<"graph desturctor";
}



void BaseGraph::AddVer(BaseVer * ver)
{
	ver->setParent(this);
	m_vers.append( ver );
}


void BaseGraph::AddEdge(BaseEdge * edge)
{
	qDebug()<<"Add edge";
	edge->setParent(this);
	m_edges.append( edge );
}


void BaseGraph::Clean()
{
	qDebug()<<"Graph::Clean";
	qDebug()<<"Graph:: Deleting vers";
	while (!m_vers.isEmpty())
		delete m_vers.takeFirst();
	qDebug()<<"Graph:: Deleting edges";
	while (!m_edges.isEmpty())
		delete m_edges.takeFirst();
	qDebug()<<"Graph:: deleted all";
}

void BaseGraph::RemoveVer(BaseVer * ver)
{
        BaseEdge * e;
	foreach( e, m_edges ){
		if( e->Have( ver ) ){
			m_edges.removeOne( e );
			delete e;
		}
	}
	m_vers.removeOne( ver );
	delete ver;

//	return;
//	foreach( e, deletedEdges ){
//
//		m_edges.removeOne( e );
//		delete e;
//	}
//
}

void BaseGraph::RemoveEdge(BaseEdge * edge)
{
	m_edges.removeOne( edge );
	delete edge;
}

BaseGraph * BaseEdge::parentGraph()
{
    if( ! parent())
        return 0;
    return qobject_cast<BaseGraph*>(parent());
}

int BaseEdge::ConnectSame(BaseEdge *edge)
{
    if( m_v0 == edge->m_v0 && m_v1 == edge->m_v1 )
        return 1;
    if(m_v0 == edge->m_v1 && m_v1 == edge->m_v0)
        return -1;
    return 0;
}

bool BaseEdge::Have(BaseVer *v0, BaseVer *v1)
{
    if( v1 )
        return m_v0 == v0 && m_v1 == v1;
    else
        return m_v0 == v0 || m_v1 == v0;
}

QString BaseEdge::toString() const
{
    return QString("Edge( id: %1, v0: %2, v1: %3, this: %4)")
            .arg( m_info->id())
            .arg( m_v0->info()->id() )
            .arg( m_v1->info()->id() )
            .arg( (int)this );
}

BaseGraph * BaseVer::parentGraph()
{
    if( ! parent())
        return 0;
    return qobject_cast<BaseGraph*>(parent());

}
