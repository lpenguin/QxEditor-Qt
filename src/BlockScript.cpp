#include "BlockScript.h"

BlockScript::BlockScript(QObject *parent) :
    QObject(parent)
{
}

BsVariableDefinition::BsVariableDefinition(BsVariable *var, BsValue *value)
{
    setVar( var );
    setValue( value );
}

BsAction::BsAction(BsVariable *var, BsObject *value, BsObject::BsOperation actionType)
{
    setValue( value );
    setVar( var );
    m_actionType = actionType;
}
