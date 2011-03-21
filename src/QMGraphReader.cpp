#include "QMGraphReader.h"

QMGraphReader::QMGraphReader( AbstractQMInfoReader * infoReader ):
    m_infoReader( infoReader )
{
}

BaseGraph * QMGraphReader::ReadGraph(const QString & filename, BaseGraph * graph ){
    if( ! graph ) graph = new BaseGraph();
    m_graph = graph;
    QMReader reader;
    m_qmGraph = reader.ReadGraph( filename );
    if( !m_qmGraph ){
        qDebug()<<QObject::tr("Error in loading graph: %1").arg(reader.errorString());
        return 0;
    }
    ReadVers();
    ReadEdges();
    ReadGraphInfo();
}

void QMGraphReader::ReadVers()
{
    foreach(QMLocation * loc, m_qmGraph->locations()){
        m_graph->AddVer( ReadVer( loc ));
    }
}

BaseVer * QMGraphReader::ReadVer(QMLocation *location)
{
    QPoint pos = QPoint(location->x, location->y);
    BaseVerInfo * info = m_infoReader->ReadVerInfo( location );
    return new BaseVer( info, pos );
}

void QMGraphReader::ReadEdges()
{
    foreach( QMPath * path, m_qmGraph->paths()){
        m_graph->AddEdge( ReadEdge( path ) );
    }
}

BaseEdge * QMGraphReader::ReadEdge(QMPath *path)
{
    BaseVer * v0 = FindVer( path->ownerLoc );
    BaseVer * v1 = FindVer( path->nextLoc );
    BaseEdgeInfo * info = m_infoReader->ReadEdgeInfo( path );
    return new BaseEdge(info, v0, v1);
}

void QMGraphReader::ReadGraphInfo()
{
    m_graph->setInfo( m_infoReader->ReadGraphInfo(m_qmGraph ));
}

BaseVer * QMGraphReader::FindVer( QMLocation *location)
{
    return m_graph->vers().at( m_qmGraph->locations().indexOf( location ) );
}

