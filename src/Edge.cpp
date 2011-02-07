#include "Edge.h"
//

Edge::Edge(EdgeInfo info, Ver * v0, Ver * v1, QObject * parent)
	: QObject( parent ), m_v0( v0 ), m_v1 ( v1 ), m_info( info )
{

}

bool Edge::Have(Ver * v0, Ver * v1)
{
	if( v1 )
		return m_v0 == v0 && m_v1 == v1;
	else
		return m_v0 == v0 || m_v1 == v0;
}
int Edge::ConnectSame(Edge * edge){
	if( m_v0 == edge->m_v0 && m_v1 == edge->m_v1 )
		return 1;
	if(m_v0 == edge->m_v1 && m_v1 == edge->m_v0)
		return -1;
	return 0;
    //return (m_v0 == edge->m_v0 && m_v1 == edge->m_v1) || (m_v0 == edge->m_v1 && m_v1 == edge->m_v0);
}

Edge::~Edge(){
        //qDebug()<<"Destructor Edge"<<toString();
}

Edge::Edge(Ver * v0, Ver * v1, QObject * parent)
	: QObject( parent ), m_v0( v0 ), m_v1 ( v1 )
{

}

QString Edge::toString()
{
	return QString("Edge( id: %1, v0: %2, v1: %3, this: %4)")
		.arg( m_info.id )
		.arg( m_v0->info().id )
		.arg( m_v1->info().id )
		.arg( (int)this );
}

Graph * Edge::parentGraph(){
    if( ! parent())
        return 0;
    return qobject_cast<Graph*>(parent());
}
