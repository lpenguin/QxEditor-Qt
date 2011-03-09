#include "BlockScript.h"

BlockScript::BlockScript(QObject *parent) :
    QObject(parent)
{
}

BsVariableDefinition::BsVariableDefinition(BsVariable *var, BsExpression *value)
{
    setVar( var );
    setValue( value );
}

BsAction::BsAction(BsVariable *var, BsExpression *value, BsObject::BsOperation actionType)
{
    setValue( value );
    setVar( var );
    m_actionType = actionType;
}

void BsObject::set( BsObjectP & obj, BsObjectP value ){
    obj = value;
    if( obj && isLocal( obj ))
        obj->setParent( this );
}
void BsObject::setList( BsObjectList & list, BsObjectList value ){
    list.clear();
    foreach( BsObject * obj, value ){
        add( list, obj);
    }
}
void BsObject::setList( BsExpressionList & list, BsExpressionList value ){
    list.clear();
    foreach( BsExpression * obj, value ){
        add( list, obj);
    }
}

void BsObject::add( BsExpressionList & list, BsExpression * value){
    list.append( value );
    if( value && isLocal((BsObjectP) value ))
        value->setParent( this );
}
void BsObject::add( BsObjectList & list, BsObject * value){
    list.append( value );
    if( value && isLocal( value ))
        value->setParent( this );
}
