#include "QMScriptToBsConverter.h"

QMScriptToBsConverter::QMScriptToBsConverter(QMParametrList qmGlobals):
    m_qmGlobals( qmGlobals )
{
    setQmGlobals( qmGlobals );
}

BsInstructionList QMScriptToBsConverter::ConvertInstructions(QMActionList qmActions)
{
    BsInstructionList instructions;
    foreach( QMAction * action, qmActions ){
        instructions.append( ConvertInstruction( action ));
    }
    return instructions;
}

BsVariable * QMScriptToBsConverter::ConvertQMParametr(QMParametr * qmParametr)
{
    return new BsVariable( Transliter::Translate( qmParametr->name ) );
}

BsInstructionList QMScriptToBsConverter::ConvertInstruction(QMAction * qmAction)
{
    BsVariable * var = m_varMap[qmAction->param];
    BsAction *  action = new BsAction( var );
    BsInstructionList list;
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
        BsValue * val = new BsValue(str);
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
    foreach( QMParametr * par, qmGlobals){
        var = ConvertQMParametr( par );
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

BsConditionList QMScriptToBsConverter::ConvertQMConditions(QMConditionList qmConditions)
{
    BsConditionList result;
    foreach(QMCondition * cond, qmConditions){
        result<<ConvertQMCondition(cond);
    }
    return result;
}

BsCondition * QMScriptToBsConverter::ConvertQMLocaigalCondition(QString condition)
{
    return new BsCondition( BsCondition::UserString, BsExpressionList() << new BsUserString( condition ));
}
