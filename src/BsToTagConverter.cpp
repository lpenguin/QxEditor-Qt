#include "BsToTagConverter.h"

BsToTagConverter::BsToTagConverter()
{
}

//QString BsToESMAScriptConverter::ConvertBsInstructions(BsInstructionList instructions)
//{
//    QStringList result;
//    foreach( BsInstruction * instruction, instructions){
//        result<<ConvertBsInstruction(instruction);
//    }
//    return result.join( QString("\n"));
//}

//QString BsToESMAScriptConverter::ConvertBsInstruction(BsInstruction *instruction)
//{
//    switch( instruction->type()){
//    case BsObject::Action:
//        return ConvertBsAction( (BsAction *) instruction);
//    case BsObject::Function:
//        return ConvertBsFunction( (BsFunction * ) instruction );
//    case BsObject::VariableDefinition:
//        return ConvertBsVariableDefinition( (BsVariableDefinition * ) instruction );
//    case BsObject::UserString:
//        return ConvertBsUserString( (BsUserString * ) instruction );
//    default:
//        return QString("[ERROR]");
//    }
//}

//QString BsToESMAScriptConverter::ConvertBsAction(BsAction *action)
//{

//}

//QString BsToESMAScriptConverter::ConvertBsFunction(BsFunction *function, bool asLocal)
//{
//    QString functionString;
//    QStringList arguments;

//}

//QString BsToESMAScriptConverter::ConvertBsVariableDefinition(BsVariableDefinition *varDef)
//{

//}

//QString BsToESMAScriptConverter::ConvertBsVariable(BsVariable *variable)
//{

//}

//QString BsToESMAScriptConverter::ConvertBsValue(BsValue *value)
//{

//}

//QString BsToESMAScriptConverter::ConvertBsExpression(BsExpression *expression)
//{

//}

//QString BsToESMAScriptConverter::ConvertBsUserString(BsUserString *userString)
//{

//}

QString BsToTagConverter::TagStart()
{
    return QString("//!bs:")
}

QString BsToTagConverter::TagEnd()
{
    return QString("//!bs:end")
}

QString BsToTagConverter::ConvertBsObject(BsObject *obj)
{

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
    return QString("vdef[%1,%2]").arg(varDef->var()->name()).arg(ObjectTag(varDef->value()));
}

QString BsToTagConverter::UserStringTag(BsUserString * userString)
{
    return QString("user[%1]").arg( userString->string() );
}

QString BsToTagConverter::ValueTag(BsValue * value)
{
    return QString("val[%1]").arg( value->value());
}

QString BsToTagConverter::ExpressionTag( BsExpression * expression)
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
        return ConvertBsValue( (BsValue * obj));
    case BsObject::Variable:
        return ConvertBsVariable( (BsVariable * obj ));
    case BsObject::Expression:
        return ConvertBsExpression(( BsExpression * obj ));
    case BsObject::Function:
        return ConvertBsFunction(( BsFunction * obj ));
    default:
        return QString("[ERROR]");
    }
}

QString BsToTagConverter::ExpressionTypeToString(BsObject::BsOperation operation)
{
    return m_expressionTypes[ operation ];
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

QString BsToTagConverter::ActionTag(BsAction *action)
{
    return QString("act[%1,%2,%3]")
            .arg(ActionTypeToString(action->actionType()))
            .arg(action->var()->name())
            .arg(ObjectTag(action->value()));
}

QString BsToTagConverter::ActionTypeToString(BsObject::BsOperation operation)
{
    return m_actionTypes[ operation ];
}

