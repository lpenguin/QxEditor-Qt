#include "QMGraphConverter.h"

QMGraphConverter::QMGraphConverter()
{
}

BaseGraph * QMGraphConverter::Convert(QMGraph *qmGraph)
{
    if( !qmGraph ) return 0;
    BaseGraph * graph = new BaseGraph();
    m_graph = graph;
    m_qmGraph = qmGraph;

    graph->setName("Converted from QMGraph");
    graph->setDescription( qmGraph->stringReplaces().missionString );
    m_qmToBs.setQmGlobals( qmGraph->params() );
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

    QString text;
    if( location->texts.count() )
        text = location->texts[0];
    QPoint pos = QPoint(location->x, location->y);;
    VerInfo * info = new VerInfo(QString("L")+QString::number(location->locNumber),
                                 ConvertActions( location->actions),
                                 text,
                                 ConvertLocationType( location->type ));
//    info.id = QString("L")+QString::number(location->locNumber);
//    if( location->texts.count() )
//        info.text = location->texts[0];
//    else
//        info.text = "";
//    info.actions = ConvertActions( location->actions);
//    info.type = ConvertLocationType( location->type );
    return new Ver(info, pos);
}

Edge *  QMGraphConverter::ConvertPath( QMPath * path, Ver * v0, Ver * v1 ){
    EdgeInfo *  info = new EdgeInfo(QString("P")+QString::number(path->pathNumber),
                                    ConvertActions( path->actions),
                                    ConvertPathConditions( path ),
                                    path->text,
                                    path->question);
    return new Edge( info, v0, v1 );
}

//QString QMGraphConverter::ConvertAction(QMAction * action)
//{
//    BlockScript * script =  m_qmToBs.ConvertStatement(action);
//    QString result = m_BsToESMA.ConvertBlockSript( script );
//    return result;
//}

QString QMGraphConverter::ConvertCondition(QMCondition *condition)
{
    return "[Not realized yet]";
}

QString QMGraphConverter::ConvertConditions(QMConditionList conditions)
{
    return "[Not realized yet]";
}

QString QMGraphConverter::ConvertActions(QMActionList actions)
{
     BlockScript * script =  m_qmToBs.ConvertQMActions(actions);
     QString result = m_BsToESMA.ConvertBlockSript( script );
     delete script;
     return result;
//    QStringList res;
//    foreach( QMAction * action, actions){
//        res<<ConvertAction( action );
//    }

//    return res.join("\n");
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
    return odinary;
}

Ver * QMGraphConverter::FindVer( QMLocation *location)
{
    return m_graph->vers().at( m_qmGraph->locations().indexOf( location ) );
}

QString QMGraphConverter::ConvertParams(QMParametrList params)
{
    QStringList result;
    BlockScript * script;
    foreach( QMParametr * par, params){
        if( par->active ){
            script = m_qmToBs.ConvertQMParametr( par );
            result<<m_BsToESMA.ConvertBlockSript( script );
            delete script;
        }
    }

    return result.join("\n");
}


QString QMGraphConverter::ConvertPathConditions(QMPath *path)
{
    BsCondition * cond = m_qmToBs.ConvertQMConditions( path->conditions );
    BsExpressionList exprs = cond->arguments();
    BsExpression * expr;
    if( exprs.count() != 1)
        expr = (BsExpression *)cond;
    else
        expr = exprs.at(0);

//    if( !path->logicalCondition.isEmpty() ){
//        BsCondition * logCond = m_qmToBs.ConvertQMLocaigalCondition(path->logicalCondition);
//        //conds << new BsCondition( BsCondition::And, BsObjectList()<< cond << logCond <<cond);
//    }
    QString result = m_BsToESMA.ConvertBsConditionStatement( expr );
    delete cond;
    return result;
//    info.conditions = ConvertConditions( path->conditions);
//    if( !path->logicalCondition.isEmpty() ){
//        if( info.conditions.isEmpty())
//            info.conditions = ConvertPathLogicalCondition( path->logicalCondition );
//    }
//    return "[Not realized yet]";
}
