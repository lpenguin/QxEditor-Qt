#include "QlQMInfoReader.h"


BaseVerInfo * QlQMInfoReader::ReadVerInfo(QMLocation *location)
{
    QlLocationTexts * texts = ConvertLocationTexts( location );
    QlLocationStatementList statements;
    if( texts->texts().count() > 1 )
        statements << texts;
    return new QlVerInfo(  texts->firstText(), statements,
                         ConvertActions(location->actions),
                         ConvertLocationType( location->type ),
                         QString("L")+QString::number(location->locNumber) );
}

BaseEdgeInfo * QlQMInfoReader::ReadEdgeInfo(QMPath *path)
{
    BsExpression * expr;
    if( ! path->logicalCondition.isEmpty() )
        expr = new BsCondition( BsCondition::And,
                               BsExpressionList() <<
                               new BsUserString(path->logicalCondition) <<
                               ConvertConditions(path->conditions)
                               );
    else
        expr = ConvertConditions(path->conditions);

    return new QlEdgeInfo( path->text,
                          path->question,
                          expr,
                          ConvertActions( path->actions ),
                          ConvertPathStatements( path ),
                          QString("P")+QString::number(path->pathNumber) );
}

BaseGraphInfo * QlQMInfoReader::ReadGraphInfo(QMGraph *graph)
{
    m_qmToBs.setQmGlobals( graph->params() );
    return new QlGraphInfo( "[Not inplemented yet]",
                           graph->stringReplaces().missionString,
                           new BlockScript(),
                           ConvertParametrs( graph->params()), "Main");
}

QlLocationTexts * QlQMInfoReader::ConvertLocationTexts(QMLocation *location)
{
    BsExpression * expr;
    if( location->selectTextByFormula )
        expr = new BsUserString(location->textFormula);
    else
        expr = new BsNull();
    return new QlLocationTexts(QString("L%1").arg(location->locNumber), location->texts, expr);
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

BaseVerInfo::VerType QlQMInfoReader::ConvertLocationType(QMLocation::QMLocationType type)
{
    switch(type){
    case QMLocation::Death:
        return BaseVerInfo::fail;
    case QMLocation::Empty:
        return BaseVerInfo::odinary;
    case QMLocation::Fail:
        return BaseVerInfo::fail;
    case QMLocation::Odinary:
        return BaseVerInfo::odinary;
    case QMLocation::Start:
        return BaseVerInfo::start;
    case QMLocation::Success:
        return BaseVerInfo::win;
    }
    return BaseVerInfo::odinary;

}

QlParametr * QlQMInfoReader::ConvertParametr(QMParametr *parametr)
{
    return m_qmToBs.ConvertQMParametr( parametr );
}

QlParametrList QlQMInfoReader::ConvertParametrs(QMParametrList params)
{
    QlParametrList res;
    foreach( QMParametr * par, params ){
        res<<ConvertParametr( par );
    }
    return res;
}

QlPathStatementList QlQMInfoReader::ConvertPathStatements(QMPath *path)
{
    QlPathStatementList result;
    QString id = QString("P%1").arg(path->pathNumber);
    result << new QlPathPriority( id, path->priority)
           << new QlPathShowOrder(id, path->showOrder)
           << new QlPathPassability(id, path->prohodimost );
    return result;
}

//QString QlQMInfoReader::pathId(QMPath *path)
//{
//    return QString("P%1").arg(path->pathNumber);
//}
