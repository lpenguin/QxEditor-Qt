#include "QMGraphConverter.h"

QMGraphConverter::QMGraphConverter()
{
}

Graph * QMGraphConverter::Convert(QMGraph *qmGraph)
{
    if( !qmGraph ) return 0;
    Graph * graph = new Graph();
    m_graph = graph;
    m_qmGraph = qmGraph;

    graph->setName("Converted from QMGraph");
    graph->setDescription( qmGraph->stringReplaces().missionString );
    ConvertLocations( qmGraph->locations() );
    ConvertPaths( qmGraph->paths() );;
    graph->setScript( ConvertParams(qmGraph->params() ) );
    return graph;
}

void QMGraphConverter::ConvertLocations( QMLocationList locations)
{
    foreach( QMLocation * loc, locations){
        m_graph->AddVer( ConvertLocation( loc ) );
    }
}

void  QMGraphConverter::ConvertPaths( QMPathList paths)
{
    Ver * v0;
    Ver * v1;
    foreach( QMPath * path, paths){
        v0 = FindVer( path->ownerLoc );
        v1 = FindVer( path->nextLoc );
        m_graph->AddEdge( ConvertPath( path, v0, v1 ) );
    }
}

Ver * QMGraphConverter::ConvertLocation(QMLocation *location)
{
    VerInfo info;
    QPoint pos = QPoint(location->x, location->y);;
    info.id = QString("L")+QString::number(location->locNumber);
    if( location->texts.count() )
        info.text = location->texts[0];
    else
        info.text = "";
    info.actions = ConvertActions( location->actions);
    info.type = ConvertLocationType( location->type );
    return new Ver(info, pos);
}

Edge *  QMGraphConverter::ConvertPath( QMPath * path, Ver * v0, Ver * v1 ){
    EdgeInfo info;
    info.id =  QString("P")+QString::number(path->pathNumber);
    info.actions = ConvertActions( path->actions);
    info.conditions = ConvertConditions( path->conditions);
    info.question = path->question;
    info.text = path->text;
    return new Edge( info, v0, v1 );
}

QString QMGraphConverter::ConvertAction(QMAction * action)
{
    return "";
}

QString QMGraphConverter::ConvertCondition(QMCondition *condition)
{
    return "";
}

QString QMGraphConverter::ConvertConditions(QMConditionList conditions)
{
    return "";
}

QString QMGraphConverter::ConvertActions(QMActionList actions)
{
    return "";
}

LocationType QMGraphConverter::ConvertLocationType(QMLocation::QMLocationType type)
{
    switch(type){
    case QMLocation::Death:
        return fail;
    case QMLocation::Empty:
        return odinary;
    case QMLocation::Fail:
        return fail;
    case QMLocation::Odinary:
        return odinary;
    case QMLocation::Start:
        return start;
    case QMLocation::Success:
        return win;
    }
}

Ver * QMGraphConverter::FindVer( QMLocation *location)
{
    return m_graph->vers().at( m_qmGraph->locations().indexOf( location ) );
}

QString QMGraphConverter::ConvertParams(QMParametrList params)
{
    return "";
}
