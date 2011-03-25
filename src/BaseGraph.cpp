#include "BaseGraph.h"
namespace Graphs {
Graph::Graph( GraphInfo * info, QObject * object ):
    m_info( info ), QObject( object ){

}

Ver * Graph::FindVer(QString id)
{
        Ver * v;
	foreach(v, m_vers){
                if( v->info()->id() == id )
			return v;
	}
 	return 0;
}

QString Graph::GetNewVerId(  ){
    QString prefix = "L";
    QString intString;
    int maxId = 0;
    int id;

    bool ok;
    foreach(Ver * ver, m_vers){
        intString = ver->info()->id();
        intString.replace(QRegExp("^"+prefix),"");
        id = intString.toInt( &ok );
        if( ok && maxId < id){
            maxId = id;
        }
    }

    return prefix+QString::number(++maxId);
}

QString Graph::GetNewEdgeId(  ){
    QString prefix = "P";
    QString intString;
    int maxId = 0;
    int id;

    bool ok;
    foreach(Edge * edge, m_edges){
        intString = edge->info()->id();
        intString.replace(QRegExp("^"+prefix),"");
        id = intString.toInt( &ok );
        if( ok && maxId < id){
            maxId = id;
        }
    }
    return prefix+QString::number(++maxId);
}



Graph::~Graph()
{
	qDebug()<<"graph desturctor";
}



void Graph::AddVer(Ver * ver)
{
	ver->setParent(this);
	m_vers.append( ver );
}


void Graph::AddEdge(Edge * edge)
{
	qDebug()<<"Add edge";
	edge->setParent(this);
	m_edges.append( edge );
}


void Graph::Clean()
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

void Graph::RemoveVer(Ver * ver)
{
        Edge * e;
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

void Graph::RemoveEdge(Edge * edge)
{
	m_edges.removeOne( edge );
	delete edge;
}

Graph * Edge::parentGraph()
{
    if( ! parent())
        return 0;
    return qobject_cast<Graph*>(parent());
}

int Edge::ConnectSame(Edge *edge)
{
    if( m_v0 == edge->m_v0 && m_v1 == edge->m_v1 )
        return 1;
    if(m_v0 == edge->m_v1 && m_v1 == edge->m_v0)
        return -1;
    return 0;
}

bool Edge::Have(Ver *v0, Ver *v1)
{
    if( v1 )
        return m_v0 == v0 && m_v1 == v1;
    else
        return m_v0 == v0 || m_v1 == v0;
}

QString Edge::toString() const
{
    return QString("Edge( id: %1, v0: %2, v1: %3, this: %4)")
            .arg( m_info->id())
            .arg( m_v0->info()->id() )
            .arg( m_v1->info()->id() )
            .arg( (int)this );
}

Graph * Ver::parentGraph()
{
    if( ! parent())
        return 0;
    return qobject_cast<Graph*>(parent());

}
}
