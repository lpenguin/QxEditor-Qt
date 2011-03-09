#include "BsToTagConverter.h"

BsToTagConverter::BsToTagConverter()
{
    FillOperatorTypes();
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
    foreach ( BsExpression * obj, function->arguments()) {
        arguments<<ExpressionTag(obj);
    }
    return QString("func[%1,%2]").arg(function->name()).arg(arguments.join(","));
}

QString BsToTagConverter::VariableDefinitionTag(BsVariableDefinition * varDef)
{
    return QString("vdef[%1,%2]").arg( VariableTag(varDef->var())).arg(ExpressionTag(varDef->value()));
}

QString BsToTagConverter::UserStringTag(BsUserString * userString)
{
    return QString("user[%1]").arg( userString->string() );
}

QString BsToTagConverter::ValueTag(BsValue * value)
{
    return QString("val[%1]").arg( value->value());
}

QString BsToTagConverter::OperatorTag( BsOperator * expression)
{
    QStringList args;
    foreach (BsExpression * obj, expression->arguments()) {
        args<<ExpressionTag( obj );
    }
    return QString("expr[%1,%2]")
            .arg(ExpressionTypeToString( expression->operation()))
            .arg( args.join(QString(",")));
}

QString BsToTagConverter::ExpressionTag(BsExpression *obj)
{
    switch( obj->type()){
    case BsObject::Value:
        return ValueTag( (BsValue * )obj);
    case BsObject::Variable:
        return VariableTag( (BsVariable * ) obj );
    case BsObject::Operator:
        return OperatorTag(( BsOperator *) obj );
    case BsObject::Function:
        return FunctionTag(( BsFunction * )obj );
    case BsObject::Null:
        return NullTag( ( BsNull * )obj);
    case BsObject::Condition:
        return ConditionTag( ( BsCondition * )obj);
    case BsObject::Range:
        return RangeTag( ( BsRange * )obj);
    case BsObject::UserString:
        return UserStringTag(( BsUserString * )obj);
    default:
        return QString("[ERROR]");
    }
}

QString BsToTagConverter::ExpressionTypeToString(BsObject::BsOperation operation)
{
    return m_operatorTypes[ operation ];
}
QString BsToTagConverter::ActionTypeToString(BsObject::BsOperation operation)
{
    return m_actionTypes[ operation ];
}
void BsToTagConverter::FillOperatorTypes()
{
   // m_expressionTypes.insert( BsObject::Mov, "mov");
    m_operatorTypes.insert( BsObject::Addition, "add");
    m_operatorTypes.insert( BsObject::Division, "div");
    m_operatorTypes.insert( BsObject::Substraction, "sub");
    m_operatorTypes.insert( BsObject::Multiplication, "mul");

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
            .arg(ExpressionTag(action->value()));
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
    foreach (BsExpression * obj, condition->arguments()) {
        args<<ExpressionTag( obj );
    }
    return QString("cond[%1,%2]")
            .arg(ConditionTypeToString( condition->condition()))
            .arg( args.join(QString(",")));


}

QString BsToTagConverter::RangeTag(BsRange *range)
{
    return QString("ran[%1,%2]")
            .arg(ExpressionTag( range->min() ))
            .arg(ExpressionTag( range->max() ));
}

QString BsToTagConverter::IfTag(BsIf *if_)
{
    return QString("if[%1]")
            .arg(ExpressionTag(if_->expression()));
}

QString BsToTagConverter::ConstraintTag(QlConstraint *con)
{
    return QString("ql.cons[%1, %2, %3]")
            .arg(VariableTag(con->var()))
            .arg(ExpressionTag(con->min()))
            .arg(ExpressionTag(con->max()));
}

QString BsToTagConverter::TriggerTag(QlTrigger *trig)
{
    return QString("ql.trig[%1, %2]")
            .arg(VariableTag(trig->var()))
            .arg(IfTag(trig->if_()));
}

QString BsToTagConverter::ShowVariableTag(QlShowVariable *sv)
{
    QStringList ranges;
    QStringList texts;
    foreach( BsRange * ran, sv->ranges()){
        ranges<< RangeTag( ran );
    }
    foreach( QString str, sv->strings()){
        texts<<QString("'%1'").arg(str);
    }

    return QString("ql.show[%1, [%2], [%3] ]")
            .arg( VariableTag(sv->var()))
            .arg( ranges.join(", ") )
            .arg( texts.join(", ") );
}

QString BsToTagConverter::BoundTriggerTag(QlBoundTrigger *trig)
{
    QString type;
    if( trig->boundType() == QlBoundTrigger::Min){
        type = "min";
    }else{
        type = "max";
    }
    return QString("ql.bound[%1, %2, %3, '%4']")
            .arg(VariableTag(trig->var()))
            .arg( type )
            .arg(ValueTag(trig->value()))
            .arg(  trig->text() );
}





