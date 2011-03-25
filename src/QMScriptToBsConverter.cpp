#include "QMScriptToBsConverter.h"

QMScriptToBsConverter::QMScriptToBsConverter(QMParametrList qmGlobals):
    m_qmGlobals( qmGlobals )
{
    setQmGlobals( qmGlobals );
}

BsScript * QMScriptToBsConverter::ConvertQMActions(QMActionList qmActions)
{
    BsStatementList instructions;
    foreach( QMAction * action, qmActions ){
        instructions.append( ConvertQMAction( action ));
    }
    return new BsScript( instructions );
}

BsVariable * QMScriptToBsConverter::ConvertQMParametrToVariable(QMParametr * qmParametr)
{
    return new BsVariable( Transliter::Translate( qmParametr->name ) );
}

BsStatementList QMScriptToBsConverter::ConvertQMAction(QMAction * qmAction)
{
    BsVariable * var = m_varMap[qmAction->param];
    qDebug()<<QString("Variable %1 (%2)").arg(qmAction->param->name).arg(qmAction->param->parNumber) ;
    if( !var )
        throw( Error(QString("Variable %1 (%2) not found").arg(qmAction->param->name).arg(qmAction->param->parNumber)) );
    BsAction *  action = new BsAction( var );
    BsStatementList list;
    switch(qmAction->type){
    case QMAction::Mov:
        action->setActionType( BsObject::Mov );
        action->setValue(new BsValue( QString::number(qmAction->addNumber )));
        list<<action;
        break;
    case QMAction::Number:
        if( !qmAction->addNumber )
            break;
        else if( qmAction->addNumber > 0 )
            action->setActionType( BsObject::Addition);
        else
            action->setActionType( BsObject::Substraction);
        action->setValue(new BsValue( QString::number( abs( qmAction->addNumber ) )));
        list<<action;
        break;
    case QMAction::Equation:
        action->setActionType(BsObject::Mov);
        action->setValue(ConvertQMEquation(qmAction->equation));
        list<<action;
        break;
     case QMAction::Procent:
        action->setActionType(BsObject::Mov);
        QString str = QString::number(qmAction->addNumber);
        BsValue * val = new BsValue(str);/*{
            BsFunction * f = new BsFunction;
            f->setName( QString("prc") );
            f->setArguments( BsExpressionList() << var << val );
            action->setValue( f );
        }*/
        action->setValue(new BsFunction( QString("prc"), BsExpressionList() << var << val));
        list<<action;
        break;
    }

    if( qmAction->show == QMAction::Show){
        BsAction * action = new BsAction( var );
        action->setActionType(BsObject::Show);
        action->setValue( new BsNull );
        list<<action;
    }else if(qmAction->show == QMAction::Hide){
        BsAction *  action = new BsAction( var );
        action->setActionType(BsObject::Hide);
        action->setValue( new BsNull );
        list<<action;
    }


    return list;
}

BsUserString * QMScriptToBsConverter::ConvertQMEquation(QString equation)
{
    return new BsUserString( equation );
}

void QMScriptToBsConverter::setQmGlobals(QMParametrList qmGlobals)
{
    BsVariable * var;
    m_qmGlobals = qmGlobals;
    foreach( QMParametr * par, qmGlobals){
        var = ConvertQMParametrToVariable( par );
        m_globals.append( var);
        m_varMap.insert(par, var);
    }

}

BsConditionList QMScriptToBsConverter::ConvertQMCondition(QMCondition *qmCondition)
{
    BsConditionList result;
    BsVariable * var = m_varMap[qmCondition->param];
    if( qmCondition->maxDiap != qmCondition->param->max ||
            qmCondition->minDiap != qmCondition->param->min){
        BsCondition * cond = new BsCondition( BsCondition::In,
                                             BsExpressionList() <<
                                                var <<
                                                new BsRange(
                                                 new BsValue( QString::number(qmCondition->minDiap)),
                                                 new BsValue( QString::number(qmCondition->maxDiap))
                                                 ));
        result<<cond;
    }
    if( qmCondition->isEquals ){
        BsExpressionList list;
        foreach( int v, qmCondition->equals){
            list<<var<<new BsValue( QString::number( v ));
        }

        BsCondition * cond = new BsCondition( BsCondition::In, list);
        result<<cond;
    }
    if( qmCondition->isKraten ){
        BsExpressionList list;
        foreach( int v, qmCondition->kraten){
            list<<var<<new BsValue( QString::number( v ));
        }

        BsCondition * cond = new BsCondition( BsCondition::Multiple, list);
        result<<cond;
    }
    return result;

}

BsCondition * QMScriptToBsConverter::ConvertQMConditions(QMConditionList qmConditions)
{
    BsConditionList result;
    foreach(QMCondition * cond, qmConditions){
        result<<ConvertQMCondition(cond);
    }
    return new BsCondition( BsCondition::And, BsCondition::ConditionsToExpressions(result));
}

BsCondition * QMScriptToBsConverter::ConvertQMLocaigalCondition(QString condition)
{
    return new BsCondition( BsCondition::UserString, BsExpressionList() << new BsUserString( condition ));
}

QlParametr *  QMScriptToBsConverter::ConvertQMParametr(QMParametr *qmParametr)
{
    BsVariable * var = m_varMap[ qmParametr ];
    QlParamStatementList list;
    list<<      new QlConstraint( var, new BsValue( QString::number(qmParametr->min)), new BsValue( QString::number(qmParametr->max)))
                <<
                new QlShowVariable( var, ConvertQMRanges( qmParametr->ranges),  ConvertQMRangesTexts(qmParametr->ranges));
    if( qmParametr->type != QMParametr::Odinary){
        QlBoundTrigger * trig = new QlBoundTrigger();
        trig->setText( qmParametr->critText);
        trig->setVar( var );
        if( qmParametr->critValue == QMParametr::Max ){
            trig->setBoundType(QlBoundTrigger::Max);
            trig->setValue( new BsValue(QString::number(qmParametr->max)));
        }else{
            trig->setBoundType(QlBoundTrigger::Max);
            trig->setValue( new BsValue(QString::number(qmParametr->max)));
        }
        list << trig ;
    }
    BsExpression * startValue = new BsUserString( qmParametr->start );
    return new QlParametr( var, startValue, list );
}

BsRangeList QMScriptToBsConverter::ConvertQMRanges(QMParametrRangeList ranges)
{
    BsRangeList list;
    foreach( QMParametrRange range, ranges){
        list<<new BsRange( new BsValue(QString::number( range.min)), new BsValue(QString::number( range.max)));
    }
    return list;
}

QStringList QMScriptToBsConverter::ConvertQMRangesTexts(QMParametrRangeList ranges)
{
    QStringList list;
    foreach( QMParametrRange range, ranges){
        list<<range.text;
    }
    return list;
}

QString QMScriptToBsConverter::ConvertQMParametrType(QMParametr::QMParametrType type)
{
    switch(type){
    case QMParametr::Fail:
    return "fail";
    case QMParametr::Success:
    return "win";
    case QMParametr::Odinary:
    return "odinary";
    case QMParametr::Death:
    return "fail";
    default:
        return "[ERROR]";
    }

}
