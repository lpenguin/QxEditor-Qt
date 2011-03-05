#include "QMScriptToBsConverter.h"

QMScriptToBsConverter::QMScriptToBsConverter(QMParametrList qmGlobals):
    m_qmGlobals( qmGlobals )
{
    BsVariable * var;
    foreach( QMParametr * par, qmGlobals){
        var = ConvertQMParametr( par );
        m_globals.append( var);
        m_varMap.insert(par, var);
    }

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
        break;
    case QMAction::Number:
        if( qmAction->addNumber > 0 )
            action->setActionType( BsObject::Addition);
        else
            action->setActionType( BsObject::Substraction);
        action->setValue(new BsValue( QString::number( abs( qmAction->addNumber ) )));
        break;
    case QMAction::Equation:
        action->setActionType(BsObject::Mov);
        action->setValue(ConvertQMEquation(qmAction->equation));
        break;
     case QMAction::Procent:
        action->setActionType(BsObject::Mov);
        QString str = QString::number(qmAction->addNumber);
        BsValue * val = new BsValue(str);
        action->setValue(new BsFunction( QString("prc"), BsObjectList() << var << val));
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

    list<<action;
    return list;
}

BsUserString * QMScriptToBsConverter::ConvertQMEquation(QString equation)
{
    return new BsUserString( equation );
}
