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

BlockScript QMScriptToBsConverter::ConvertActions(QMActionList actions)
{
    BlockScript script;
    QListIterator<QMAction> i(actions);
    while (i.hasNext()){
        script.AddActions( ConvertAction(i.next() ));
    }
    return script;
}

BsVariable * QMScriptToBsConverter::ConvertQMParametr(QMParametr * qmParametr)
{
    return new BsVariable( Transliter::Translate( qmParametr.name ) );
}

BsActionList QMScriptToBsConverter::ConvertAction(QMAction * qmAction)
{
    BsVariable * var = m_varMap[qmAction->param];
    BsAction *  action = new BsAction( var );
    BsActionList list;
    switch(qmAction.type){
    case QMAction::Mov:
        action->setActionType( BsAction::Mov);
        action->setValue(new BsValue( QString::number(qmAction.addNumber )));
        break;
    case QMAction::Number:
        if( qmAction.addNumber > 0 )
            action->setActionType( BsAction::Addition);
        else
            action->setActionType( BsAction::Substraction);
        action->setValue(new BsValue( QString::number( abs( qmAction.addNumber ) )));
        break;
    case QMAction::Equation:
        action->setActionType(BsAction::UserString);
        action->setValue(ConvertQMEquation(qmAction->equation));
        break;
     case QMAction::Procent:
        action->setActionType(BsAction::Mov);
        action->setValue(new BsFunction('prc',
                                        BsObjectList(var,
                                                     new BsValue(QString::number(qmAction->addNumber)))));
        break;
    }

    if( qmAction->show == QMAction::Show){
        BsAction * action = new BsAction( var );
        action->setActionType(BsAction::Show);
        action->setValue( new BsNull );
        list<<action;
    }else if(qmAction->show == QMAction::Hide){
        BsAction *  action = new BsAction( var );
        action->setActionType(BsAction::Hide);
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
