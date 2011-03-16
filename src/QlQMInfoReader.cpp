#include "QlQMInfoReader.h"


BaseInfo * QlQMInfoReader::ReadVerInfo(QMLocation *location)
{
    return new QlVerInfo(  ConvertLocationTexts( location ),
                          ConvertLocationTexts( location ),
                         ConvertLocationType( location->type ),
                         QString("L")+QString::number(location->locNumber) );
}

BaseInfo * QlQMInfoReader::ReadEdgeInfo(QMPath *path)
{
    BsExpression * expr;
    if( path->logicalCondition )
        expr = BsCondition( BsCondition::And,
                           BsExpressionList() <<
                           new BsUserString(path->logicalCondition) <<
                           ConvertConditions(path->conditions)
                           );
    return new QlEdgeInfo( path->text,
                          path->question,
                          expr,
                          ConvertActions( path->actions ),
                          QString("P")+QString::number(path->pathNumber) );
}

BaseInfo * QlQMInfoReader::ReadGraphInfo(QMGraph *graph)
{
    m_qmToBs->setQmGlobals( graph->params() );
    return new QlGraphInfo( "[Not inplemented yet]", graph->m_stringReplaces.missionString, ConvertParametrs( graph->params()), "Main")
}

QlLocationTexts * QlQMInfoReader::ConvertLocationTexts(QMLocation *location)
{
    BsExpression * expr;
    if( location->selectTextByFormula )
        expr = new BsUserString(location->textFormula);
    else
        expr = new BsNull();
    return new QlLocationTexts( location->texts, expr)
}

BlockScript * QlQMInfoReader::ConvertActions(QMActionList actions)
{
    return  m_qmToBs.ConvertQMActions(actions);
}

BsExpression * QlQMInfoReader::ConvertConditions(QMConditionList conditions)
{
    BsCondition * cond = m_qmToBs.ConvertQMConditions( conditions );
    BsExpressionList exprs = cond->arguments();
    BsExpression * expr;
    if( exprs.count() != 1)
        expr = (BsExpression *)cond;
    else
        expr = exprs.at(0);
    return expr;
}

QMLocation::QMLocationType QlQMInfoReader::ConvertLocationType(QMLocation::QMLocationType type)
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

QlParametr * QlQMInfoReader::ConvertParametr(QMParametr *parametr)
{
    return m_qmToBs->ConvertQMParametr( parametr );
}

QlParametrList QlQMInfoReader::ConvertParametrs(QMParametrList params)
{
    QlParametrList res;
    foreach( QMParametr * par, params ){
        res<<ConvertParametr( par );
    }
    return res;
}
