#include "QlQMInfoReader.h"


VerInfo * QlQMInfoReader::ReadVerInfo(QMLocation *location)
{
    QlLocationTexts * texts = ConvertLocationTexts( location );
    QlLocationStatementList statements;
    QString id = QString("L")+QString::number(location->locNumber);
    qDebug()<<QString("ID: %1").arg(id);
    if( texts->texts().count() > 1 )
        statements << texts;
    if( location->type == QMLocation::Empty )
        statements << new QlLocationEmpty( id );
    return new QlVerInfo(  texts->firstText(), statements,
                         ConvertActions(location->actions),
                         ConvertLocationType( location->type ),
                         id );
}

EdgeInfo * QlQMInfoReader::ReadEdgeInfo(QMPath *path)
{
    BsExpression * expr =  ConvertConditions(path->conditions);
    if( ! path->logicalCondition.isEmpty() ){
        BsExpression * eq = m_qmToBs.ConvertQMEquation( path->logicalCondition );
        if( expr->type() != BsObject::Null )
            expr = new BsCondition( BsCondition::And,
                               BsExpressionList() <<
                               eq <<
                               ConvertConditions(path->conditions)
                               );
        else
            expr = eq;
    }
//    else
//        expr = ConvertConditions(path->conditions);
    QString text = m_qmToBs.ConvertQMEquationsInText(path->text);
    QString question = m_qmToBs.ConvertQMEquationsInText(path->question);
    return new QlEdgeInfo( text,
                          question,
                          expr,
                          ConvertActions( path->actions ),
                          ConvertPathStatements( path ),
                          QString("P")+QString::number(path->pathNumber) );
}

GraphInfo * QlQMInfoReader::ReadGraphInfo(QMGraph *graph)
{
    m_qmToBs.setQmGlobals( graph->params() );
    QlParametrList params = ConvertParametrs( graph->params());
    QMStringReplaces sr = graph->stringReplaces();
    params << new QlParametr(new BsVariable("Ranger"), new BsValue("'"+sr.ranger+"'"))
           << new QlParametr(new BsVariable("FromStar"),new  BsValue("'"+sr.fromStar+"'"))
           << new QlParametr(new BsVariable("FromPlanet"),new BsValue("'"+sr.fromPlanet+"'"))
           << new QlParametr(new BsVariable("ToPlanet"),new  BsValue("'"+sr.toPlanet+"'"))
           << new QlParametr(new BsVariable("ToStar"), new BsValue("'"+sr.toStar+"'"));
    return new QlGraphInfo( "[Not inplemented yet]",
                           graph->stringReplaces().missionString,
                           QStringList()<<"main.as",
                           new BsScript(),
                           params, "Main");
}

QlLocationTexts * QlQMInfoReader::ConvertLocationTexts(QMLocation *location)
{
    BsExpression * expr;
    if( location->selectTextByFormula )
//        m_qmToBs.c
        expr = m_qmToBs.ConvertQMEquation( location->textFormula );
//        expr = new BsUserString(location->textFormula);
    else
        expr = new BsNull();
    QStringList texts;
    foreach(QString text, location->texts){
        texts<<m_qmToBs.ConvertQMEquationsInText( text );
    }

    return new QlLocationTexts(QString("L%1").arg(location->locNumber), texts, expr);
}

BsScript * QlQMInfoReader::ConvertActions(QMActionList actions)
{
    return  m_qmToBs.ConvertQMActions(actions);
}

BsExpression * QlQMInfoReader::ConvertConditions(QMConditionList conditions)
{
    BsExpression * cond = m_qmToBs.ConvertQMConditions( conditions );
    return cond;
//    BsExpressionList exprs = cond->arguments();
//    BsExpression * expr;
//    if( exprs.count() != 1)
//        expr = (BsExpression *)cond;
//    else
//        expr = exprs.at(0);
//    return expr;
}

VerInfo::VerType QlQMInfoReader::ConvertLocationType(QMLocation::QMLocationType type)
{
    switch(type){
    case QMLocation::Death:
        return VerInfo::fail;
    case QMLocation::Empty:
        return VerInfo::odinary;
    case QMLocation::Fail:
        return VerInfo::fail;
    case QMLocation::Odinary:
        return VerInfo::odinary;
    case QMLocation::Start:
        return VerInfo::start;
    case QMLocation::Success:
        return VerInfo::win;
    }
    return VerInfo::odinary;

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
    if(path->alwaysShow)
           result << new QlPathAlwaysShow(id);
    return result;
}

//QString QlQMInfoReader::pathId(QMPath *path)
//{
//    return QString("P%1").arg(path->pathNumber);
//}
