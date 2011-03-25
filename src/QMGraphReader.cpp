#include "QMGraphReader.h"

QMGraphReader::QMGraphReader( AbstractQMInfoReader * infoReader ):
    m_infoReader( infoReader )
{

}

Graph * QMGraphReader::ReadGraph(const QString & filename, Graph * graph ){
    if( ! graph ) graph = new Graph();
    m_graph = graph;
    QMReader reader;
    m_qmGraph = reader.ReadGraph( filename );
    if( !m_qmGraph ){
        qDebug()<<QObject::tr("Error in loading graph: %1").arg(reader.errorString());
        return 0;
    }
    try{
        ReadGraphInfo();
        ReadVers();
        ReadEdges();
    }
    catch(Error & e){
        qDebug()<<e.message();
        return 0;
    }

    return m_graph;
}

void QMGraphReader::ReadVers()
{
    foreach(QMLocation * loc, m_qmGraph->locations()){
        m_graph->AddVer( ReadVer( loc ));
    }
}

Ver * QMGraphReader::ReadVer(QMLocation *location)
{
    QPoint pos = QPoint(location->x, location->y);
    VerInfo * info = m_infoReader->ReadVerInfo( location );
    return new Ver( info, pos );
}

void QMGraphReader::ReadEdges()
{
    foreach( QMPath * path, m_qmGraph->paths()){
        m_graph->AddEdge( ReadEdge( path ) );
    }
}

Edge * QMGraphReader::ReadEdge(QMPath *path)
{
    Ver * v0 = FindVer( path->ownerLoc );
    Ver * v1 = FindVer( path->nextLoc );
    EdgeInfo * info = m_infoReader->ReadEdgeInfo( path );
    return new Edge(info, v0, v1);
}

void QMGraphReader::ReadGraphInfo()
{
    m_graph->setInfo( m_infoReader->ReadGraphInfo(m_qmGraph ));
}

Ver * QMGraphReader::FindVer( QMLocation *location)
{
    return m_graph->vers().at( m_qmGraph->locations().indexOf( location ) );
}

