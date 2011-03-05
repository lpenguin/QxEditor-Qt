#include "BsToESMAScriptConverter.h"

BsToESMAScriptConverter::BsToESMAScriptConverter()
{
    FillExpressionTypes();
    FillActionTypes();
    FillConditionTypes();
}

QString BsToESMAScriptConverter::ConvertBsInstructions(BsInstructionList instructions)
{
    QStringList result;
    foreach( BsInstruction * instruction, instructions){
        result<<ConvertBsInstruction(instruction);
    }
    return result.join( QString("\n"));
}

QString BsToESMAScriptConverter::ConvertBsInstruction(BsInstruction *instruction)
{
    switch( instruction->type()){
    case BsObject::Action:
        return ConvertBsAction( (BsAction *) instruction);
    case BsObject::Function:
        return ConvertBsFunction( (BsFunction * ) instruction );
    case BsObject::VariableDefinition:
        return ConvertBsVariableDefinition( (BsVariableDefinition * ) instruction );
    case BsObject::UserString:
        return ConvertBsUserString( (BsUserString * ) instruction );
    default:
        return QString("[ERROR]");
    }
}

QString BsToESMAScriptConverter::ConvertBsAction(BsAction *action)
{
    QStringList result;
    QString value =  ConvertBsObject(action->value());
    result << m_tagConverter.TagStart()+m_tagConverter.ActionTag( action );
    if( action->actionType() == BsAction::Show ){
        result<<QString("show(%1);").arg( action->var()->name());
    }else if( action->actionType() == BsAction::Hide){
        result<<QString("hide(%1);").arg( action->var()->name());
    }else{
        QString operation = ActionTypeToString(action->actionType());
        result<<QString("%1 %2 %3;")
                 .arg(action->var()->name())
                 .arg( operation )
                 .arg( value );
    }
    result<<m_tagConverter.TagEnd();
    return result.join("\n");
}

QString BsToESMAScriptConverter::ConvertBsFunction(BsFunction *function)
{
    QStringList arguments;
    QStringList result;
    result << m_tagConverter.TagStart()+m_tagConverter.FunctionTag( function );
    foreach( BsObject * obj, function->arguments()){
        arguments<<ConvertBsObject( obj );
    }
    result<<QString("%1(%2);").arg(function->name()).arg(arguments.join(","));
    result<<m_tagConverter.TagEnd();
    return result.join("\n");
}

QString BsToESMAScriptConverter::ConvertBsVariableDefinition(BsVariableDefinition *varDef)
{
    QString value =  ConvertBsObject(varDef->value());
    QStringList result;
    result << m_tagConverter.TagStart()+m_tagConverter.VariableDefinitionTag( varDef );
    result<<QString("var %1 = %2;").arg(varDef->var()->name()).arg(value);
    result<<m_tagConverter.TagEnd();
    return result.join("\n");
}

QString BsToESMAScriptConverter::ConvertBsVariable(BsVariable *variable)
{
    return variable->name();
}

QString BsToESMAScriptConverter::ConvertBsValue(BsValue *value)
{
    return value->value();
}

QString BsToESMAScriptConverter::ConvertBsExpression(BsExpression *expression)
{
    return "[Not yet realized]";
}

QString BsToESMAScriptConverter::ConvertBsUserString(BsUserString *userString)
{
    return userString->string();
}
QString BsToESMAScriptConverter::ConvertBsObject(BsObject *obj)
{
    switch( obj->type()){
    case BsObject::Value:
        return ConvertBsValue( (BsValue * ) obj);
    case BsObject::Variable:
        return ConvertBsVariable( (BsVariable * ) obj );
    case BsObject::Expression:
        return ConvertBsExpression(( BsExpression *) obj );
    case BsObject::Function:
        return ConvertBsFunction(( BsFunction * )obj );
    case BsObject::Condition:
        return ConvertBsCondition(( BsCondition * )obj );
    case BsObject::Range:
        return ConvertBsRange(( BsRange * )obj );
    default:
        return QString("[ERROR]");
    }
}

QString BsToESMAScriptConverter::ExpressionTypeToString(BsObject::BsOperation operation)
{
    return m_expressionTypes[ operation ];
}
QString BsToESMAScriptConverter::ActionTypeToString(BsObject::BsOperation operation)
{
    return m_actionTypes[ operation ];
}


QString BsToESMAScriptConverter::ConditionTypeToString(BsCondition::BsConditionType conditionType)
{
    QString res = m_conditionTypes[ conditionType ];
    return m_conditionTypes[ conditionType ];
}
void BsToESMAScriptConverter::FillConditionTypes()
{
    m_conditionTypes.insert( BsCondition::Greater, ">");
    m_conditionTypes.insert( BsCondition::GreaterEq, ">=");
    m_conditionTypes.insert( BsCondition::LowerEq, "<");
    m_conditionTypes.insert( BsCondition::Lower, "<=");
    m_conditionTypes.insert( BsCondition::Equals, "==");
    m_conditionTypes.insert( BsCondition::And, "&&");
    m_conditionTypes.insert( BsCondition::Or, "||");
    m_conditionTypes.insert( BsCondition::Not, "!");
//    m_conditionTypes.insert( BsCondition::In, "in");
//    m_conditionTypes.insert( BsCondition::Multiple, "mul");
}

void BsToESMAScriptConverter::FillExpressionTypes()
{
   // m_expressionTypes.insert( BsObject::Mov, "=");
    m_expressionTypes.insert( BsObject::Addition, "+");
    m_expressionTypes.insert( BsObject::Division, "/");
    m_expressionTypes.insert( BsObject::Substraction, "-");
    m_expressionTypes.insert( BsObject::Multiplication, "*");

}

void BsToESMAScriptConverter::FillActionTypes()
{
    m_actionTypes.insert( BsObject::Addition, "+=");
    m_actionTypes.insert( BsObject::Division, "/=");
    m_actionTypes.insert( BsObject::Substraction, "-=");
    m_actionTypes.insert( BsObject::Multiplication, "*=");
    m_actionTypes.insert( BsObject::Mov, "=");
}

QString BsToESMAScriptConverter::ConvertBsConditionInstruction(BsObject *object)
{
    QString res =  m_tagConverter.ConditionTagStart()+
            m_tagConverter.ObjectTag( (BsObject*)object)+
            m_tagConverter.ConditionTagEnd();
    res+="\n";
    res+=ConvertBsObject( object );
    return res;
}

QString BsToESMAScriptConverter::ConvertBsCondition(BsCondition *condition)
{

    switch( condition->condition()){
    case BsCondition::Greater:
    case BsCondition::GreaterEq:
    case BsCondition::Lower:
    case BsCondition::LowerEq:
    case BsCondition::Equals:
    {
        if( condition->arguments().count() != 2 )
            return "[ERROR]";
        QString arg1 = ConvertBsObject( condition->arguments().at(0));
        QString arg2 = ConvertBsObject( condition->arguments().at(1));
        return QString("%1 %2 %3")
                .arg( arg1 )
                .arg( ConditionTypeToString( condition->condition() ))
                .arg( arg2 );
    }
        break;
    case BsCondition::And:
    case BsCondition::Or:
    {
        QStringList args;
        foreach( BsObject * obj, condition->arguments()){
            args<<QString("( %1 )").arg(ConvertBsObject( obj ));
        }
        return args.join(
                    QString(" %1 ")
                        .arg( ConditionTypeToString( condition->condition() ))
                    );
    }
    case BsCondition::Not:
        if( condition->arguments().count() != 1 )
            return "[ERROR]";
        return QString("not ( %1 )")
                .arg(ConvertBsObject( condition->arguments().at(0)));
    case BsCondition::In:
    {
        if( condition->arguments().count() < 2 )
            return "[ERROR]";
        QStringList args;
        foreach( BsObject * obj, condition->arguments()){
            args<<ConvertBsObject( obj );
        }
        return QString("in(%1)").arg(args.join(","));
        //BsObject * target = condition->arguments().takeFirst();

    }
        break;
    default:
        return "[ERROR]";
    }
}

QString BsToESMAScriptConverter::ConvertBsRange(BsRange *range)
{
    return QString("range(%1, %2)")
            .arg(ConvertBsObject( range->min()))
            .arg(ConvertBsObject( range->max()));
}

//QStringList BsToESMAScriptConverter::ConvertBsObjectList(BsObjectList list)
//{

//}

