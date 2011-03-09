#include "BsToTagConverter.h"

BsToTagConverter::BsToTagConverter()
{
    FillExpressionTypes();
    FillActionTypes();
    FillConditionTypes();
}

QString BsToTagConverter::TagStart() const
{
    return QString("//!bs:");
}

QString BsToTagConverter::TagEnd() const
{
    return QString("//!bs:end");
}


QString BsToTagConverter::VariableTag(BsVariable * variable)
{
    return QString("var[%1]").arg( variable->name());
}

QString BsToTagConverter::FunctionTag(BsFunction * function)
{
    QStringList arguments;
    foreach ( BsObject * obj, function->arguments()) {
        arguments<<ObjectTag(obj);
    }
    return QString("func[%1,%2]").arg(function->name()).arg(arguments.join(","));
}

QString BsToTagConverter::VariableDefinitionTag(BsVariableDefinition * varDef)
{
    return QString("vdef[%1,%2]").arg( VariableTag(varDef->var())).arg(ObjectTag(varDef->value()));
}

QString BsToTagConverter::UserStringTag(BsUserString * userString)
{
    return QString("user[%1]").arg( userString->string() );
}

QString BsToTagConverter::ValueTag(BsValue * value)
{
    return QString("val[%1]").arg( value->value());
}

QString BsToTagConverter::ExpressionTag( BsOperator * expression)
{
    QStringList args;
    foreach (BsObject * obj, expression->arguments()) {
        args<<ObjectTag( obj );
    }
    return QString("expr[%1,%2]")
            .arg(ExpressionTypeToString( expression->operation()))
            .arg( args.join(QString(",")));
}

QString BsToTagConverter::ObjectTag(BsObject *obj)
{
    switch( obj->type()){
    case BsObject::Value:
        return ValueTag( (BsValue * )obj);
    case BsObject::Variable:
        return VariableTag( (BsVariable * ) obj );
    case BsObject::Expression:
        return ExpressionTag(( BsOperator *) obj );
    case BsObject::Function:
        return FunctionTag(( BsFunction * )obj );
    case BsObject::Null:
        return NullTag( ( BsNull * )obj);
    case BsObject::Condition:
        return ConditionTag( ( BsCondition * )obj);
    case BsObject::Range:
        return RangeTag( ( BsRange * )obj);
    default:
        return QString("[ERROR]");
    }
}

QString BsToTagConverter::ExpressionTypeToString(BsObject::BsOperation operation)
{
    return m_expressionTypes[ operation ];
}
QString BsToTagConverter::ActionTypeToString(BsObject::BsOperation operation)
{
    return m_actionTypes[ operation ];
}
void BsToTagConverter::FillExpressionTypes()
{
   // m_expressionTypes.insert( BsObject::Mov, "mov");
    m_expressionTypes.insert( BsObject::Addition, "add");
    m_expressionTypes.insert( BsObject::Division, "div");
    m_expressionTypes.insert( BsObject::Substraction, "sub");
    m_expressionTypes.insert( BsObject::Multiplication, "mul");

}

void BsToTagConverter::FillActionTypes()
{
    m_actionTypes.insert( BsObject::Addition, "madd");
    m_actionTypes.insert( BsObject::Division, "mdiv");
    m_actionTypes.insert( BsObject::Substraction, "msub");
    m_actionTypes.insert( BsObject::Multiplication, "mmul");
    m_actionTypes.insert( BsObject::Mov, "mov");
    m_actionTypes.insert( BsObject::Show, "show");
    m_actionTypes.insert( BsObject::Hide, "hide");
}

void BsToTagConverter::FillConditionTypes()
{
    m_conditionTypes.insert( BsCondition::Greater, "gt");
    m_conditionTypes.insert( BsCondition::GreaterEq, "ge");
    m_conditionTypes.insert( BsCondition::LowerEq, "lt");
    m_conditionTypes.insert( BsCondition::Lower, "le");
    m_conditionTypes.insert( BsCondition::Equals, "eq");
    m_conditionTypes.insert( BsCondition::In, "in");
    m_conditionTypes.insert( BsCondition::Multiple, "mul");
    m_conditionTypes.insert( BsCondition::And, "and");
    m_conditionTypes.insert( BsCondition::Or, "or");
    m_conditionTypes.insert( BsCondition::Not, "not");

}

QString BsToTagConverter::ConditionTypeToString(BsCondition::BsConditionType condition)
{
     return m_conditionTypes[ condition ];
}



QString BsToTagConverter::ActionTag(BsAction *action)
{
    return QString("act[%1,%2,%3]")
            .arg(ActionTypeToString(action->actionType()))
            .arg(VariableTag(action->var()))
            .arg(ObjectTag(action->value()));
}

QString BsToTagConverter::NullTag( BsNull * null)
{
    return "null";
}

QString BsToTagConverter::ConditionTagStart() const
{
    return "/*!bs:";
}

QString BsToTagConverter::ConditionTagEnd() const
{
    return ":!bs*/";
}

QString BsToTagConverter::ConditionTag(BsCondition *condition)
{
    QStringList args;
    foreach (BsObject * obj, condition->arguments()) {
        args<<ObjectTag( obj );
    }
    return QString("cond[%1,%2]")
            .arg(ConditionTypeToString( condition->condition()))
            .arg( args.join(QString(",")));


}

QString BsToTagConverter::RangeTag(BsRange *range)
{
    return QString("ran[%1,%2]")
            .arg(ObjectTag( range->min() ))
            .arg(ObjectTag( range->max() ));
}





