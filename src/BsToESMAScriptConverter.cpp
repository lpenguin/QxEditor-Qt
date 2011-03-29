#include "BsToESMAScriptConverter.h"

BsToESMAScriptConverter::BsToESMAScriptConverter()
{
    FillOperatorTypes();
    FillActionTypes();
    FillConditionTypes();
}

QString BsToESMAScriptConverter::ConvertBsStatements(BsStatementList instructions)
{
    QStringList result;
    foreach( BsStatement * instruction, instructions){
        result<<ConvertBsStatement(instruction);
    }
    return result.join( QString("\n"));
}

QString BsToESMAScriptConverter::ConvertBsStatement(BsStatement *instruction)
{
    switch( instruction->type()){
    case BsObject::Action:
        return ConvertBsAction( (BsAction *) instruction);
    case BsObject::FunctionCall:
        return ConvertBsFunctionCall( (BsFunctionCall * ) instruction );
    case BsObject::VariableDefinition:
        return ConvertBsVariableDefinition( (BsVariableDefinition * ) instruction );
    case BsObject::UserString:
        return ConvertBsUserString( (BsUserString * ) instruction );
    case BsObject::If:
        return ConvertBsIf( (BsIf * ) instruction );
    case QlType::Constraint:
        return ConvertQlConstraint( (QlConstraint * ) instruction );
    case QlType::Trigger:
        return ConvertQlTrigger( (QlTrigger * ) instruction );
    case QlType::ShowVariable:
        return ConvertQlShowVariable( (QlShowVariable * ) instruction );
    case QlType::BoundTrigger:
        return ConvertQlBoundTrigger( (QlBoundTrigger *) instruction );
    case QlType::PathPassability:
        return ConvertQlPathPassability( (QlPathPassability*) instruction);
    case QlType::PathPriority:
        return ConvertQlPathPriority( (QlPathPriority*) instruction);
    case QlType::PathShowOrder:
        return ConvertQlPathShowOrder( (QlPathShowOrder*) instruction);
    case QlType::LocationTexts:
        return ConvertQlLocationTexts( (QlLocationTexts*) instruction );
    default:
        return QString("[ERROR]");
    }
}

QString BsToESMAScriptConverter::ConvertBsAction(BsAction *action)
{
    QStringList result;
    QString value =  ConvertBsExpression(action->value());
    result << m_tagConverter.TagStart()+m_tagConverter.ActionTag( action );
    if( action->actionType() == BsAction::Show ){
        result<<QString("show('%1');").arg( action->var()->name());
    }else if( action->actionType() == BsAction::Hide){
        result<<QString("hide('%1');").arg( action->var()->name());
    }else{
        QString operation = ActionTypeToString(action->actionType());
        result<<QString("%1 %2 %3;")
                 .arg(action->var()->name())
                 .arg( operation )
                 .arg( value );
        result<<QString("CheckConstraints('%1');")
                 .arg(action->var()->name());
    }
    result<<m_tagConverter.TagEnd();
    return result.join("\n");
}

QString BsToESMAScriptConverter::ConvertBsFunction(BsFunction *function)
{
    QStringList arguments;
    QStringList result;
    result << m_tagConverter.TagStart()+m_tagConverter.FunctionTag( function );
    foreach( BsExpression * obj, function->arguments()){
        arguments<<ConvertBsExpression( obj );
    }
    result<<QString("%1(%2);").arg(function->name()).arg(arguments.join(","));
    result<<m_tagConverter.TagEnd();
    return result.join("\n");
}

QString BsToESMAScriptConverter::ConvertBsVariableDefinition(BsVariableDefinition *varDef)
{
    QString value =  ConvertBsExpression(varDef->value());
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

QString BsToESMAScriptConverter::ConvertBsOperator(BsOperator *oper)
{
    QStringList args;
    foreach( BsExpression * expr, oper->arguments() )
        args << ConvertBsExpression( expr );
    return args.join( m_operatorTypes[ oper->operation() ]);
}

QString BsToESMAScriptConverter::ConvertBsUserString(BsUserString *userString)
{
    return userString->string();
}
QString BsToESMAScriptConverter::ConvertBsExpression(BsExpression *obj)
{
    switch( obj->type()){
    case BsObject::Value:
        return ConvertBsValue( (BsValue * ) obj);
    case BsObject::Variable:
        return ConvertBsVariable( (BsVariable * ) obj );
    case BsObject::Operator:
        return ConvertBsOperator(( BsOperator *) obj );
    case BsObject::Function:
        return ConvertBsFunction(( BsFunction * )obj );
    case BsObject::Condition:
        return ConvertBsCondition(( BsCondition * )obj );
    case BsObject::Set:
        return ConvertBsSet(( BsSet * )obj );
    case BsObject::Range:
        return ConvertBsRange(( BsRange * )obj );
    case BsObject::UserString:
        return ConvertBsUserString( (BsUserString*)obj);
    case BsObject::Null:
        return QString();
    default:
        return QString("[ERROR]");
    }
}

QString BsToESMAScriptConverter::ExpressionTypeToString(BsObject::BsOperation operation)
{
    return m_operatorTypes[ operation ];
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

void BsToESMAScriptConverter::FillOperatorTypes()
{
   // m_expressionTypes.insert( BsObject::Mov, "=");
    m_operatorTypes.insert( BsObject::Addition, "+");
    m_operatorTypes.insert( BsObject::Division, "/");
    m_operatorTypes.insert( BsObject::Substraction, "-");
    m_operatorTypes.insert( BsObject::Multiplication, "*");

}

void BsToESMAScriptConverter::FillActionTypes()
{
    m_actionTypes.insert( BsObject::Addition, "+=");
    m_actionTypes.insert( BsObject::Division, "/=");
    m_actionTypes.insert( BsObject::Substraction, "-=");
    m_actionTypes.insert( BsObject::Multiplication, "*=");
    m_actionTypes.insert( BsObject::Mov, "=");
}

QString BsToESMAScriptConverter::ConvertBsConditionStatement(BsExpression *object)
{
    QString res =  m_tagConverter.ConditionTagStart()+
            m_tagConverter.ExpressionTag( object )+
            m_tagConverter.ConditionTagEnd();
    res+="\n";
    res+=ConvertBsExpression( object );
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
        QString arg1 = ConvertBsExpression( condition->arguments().at(0));
        QString arg2 = ConvertBsExpression( condition->arguments().at(1));
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
        foreach( BsExpression * obj, condition->arguments()){
            args<<QString("( %1 )").arg(ConvertBsExpression( obj ));
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
                .arg(ConvertBsExpression( condition->arguments().at(0)));
    case BsCondition::In:
    {
        if( condition->arguments().count() < 2 )
            return "[ERROR]";
        QStringList args;
//        QString firstStr;
//        BsExpression * first = condition->arguments().at(0);

//        if( first->type() == BsObject::Variable ){
//            BsVariable * var = (BsVariable*)(first);
//            firstStr = QString("'%1'").arg(var->name());
//        }
//        else
//            firstStr = ConvertBsExpression(first);
        foreach( BsExpression * obj, condition->arguments()){
            args<<ConvertBsExpression( obj );
        }
//        args[0] = firstStr;
        return QString("In(%1)").arg(args.join(","));
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
            .arg(ConvertBsExpression( range->min()))
            .arg(ConvertBsExpression( range->max()));
}

QString BsToESMAScriptConverter::ConvertBsSet(BlockScript::BsSet *set)
{
    QStringList arguments;
    foreach( BsExpression * obj, set->elems()){
        arguments<<ConvertBsExpression( obj );
    }
    return QString("[%1]").arg(arguments.join(","));
}

QString BsToESMAScriptConverter::ConvertBlockSript(BsScript *script)
{
    return ConvertBsStatements( script->statements() );
}

QString BsToESMAScriptConverter::ConvertBsIf(BsIf *if_)
{
    QStringList result;
    QString expr =  ConvertBsExpression(if_->expression());
    result << m_tagConverter.TagStart()+m_tagConverter.IfTag( if_ );
    result << QString("if( %1 ){").arg(expr);
    result<<ConvertBsStatements(if_->staements());
    result << QString("}");
    result<<m_tagConverter.TagEnd();
    return result.join("\n");
}

QString BsToESMAScriptConverter::ConvertQlConstraint(QlConstraint *con)
{
    QStringList result;
    result << m_tagConverter.TagStart()+m_tagConverter.ConstraintTag( con );
    result << QString("AddConstraint('%1', %2, %3);")
              .arg(con->var()->name())
              .arg(ConvertBsExpression(con->min()))
              .arg(ConvertBsExpression(con->max()));
    result<<m_tagConverter.TagEnd();
    return result.join("\n");
}

QString BsToESMAScriptConverter::ConvertQlTrigger(QlTrigger *trig)
{
    QStringList result;
    result << m_tagConverter.TagStart()+m_tagConverter.TriggerTag( trig );
    result << ConvertBsIf( trig );
    result<<m_tagConverter.TagEnd();
    return result.join("\n");
}

QString BsToESMAScriptConverter::ConvertQlShowVariable(QlShowVariable *sv)
{
    QStringList result;
    QStringList ranges;
    QStringList texts;
    foreach( BsRange * ran, sv->ranges()){
        ranges<<ConvertBsRange( ran );
    }
    foreach( QString str, sv->strings()){
        texts<<QString("'%1'").arg(str);
    }
    result << m_tagConverter.TagStart()+m_tagConverter.ShowVariableTag( sv );
    result << QString("AddShowRanges('%1', [%2], [%3], %4);")
              .arg(sv->var()->name())
              .arg( ranges.join(","))
              .arg( texts.join(","))
              .arg( sv->showOnZero() );
    result<<m_tagConverter.TagEnd();
    return result.join("\n");
}

QString BsToESMAScriptConverter::ConvertQlBoundTrigger(QlBoundTrigger *trig)
{
    QStringList result;
    QString type;
    if( trig->boundType() == QlBoundTrigger::Min){
        type = "min";
    }else{
        type = "max";
    }

    result << m_tagConverter.TagStart()+m_tagConverter.BoundTriggerTag( trig );
    result << QString("AddBound('%1','%2', %3, '%4');")
              .arg(trig->var()->name())
              .arg(type)
              .arg(trig->value()->value())
              .arg(trig->text());
    result<<m_tagConverter.TagEnd();
    return result.join("\n");
}

QString BsToESMAScriptConverter::ConvertBsFunctionCall(BsFunctionCall *function)
{
    QStringList arguments;
    QStringList result;
    result << m_tagConverter.TagStart()+m_tagConverter.FunctionCallTag( function );
    foreach( BsExpression * obj, function->arguments()){
        arguments<<ConvertBsExpression( obj );
    }
    result<<QString("%1(%2);").arg(function->name()).arg(arguments.join(","));
    result<<m_tagConverter.TagEnd();
    return result.join("\n");
}

QString BsToESMAScriptConverter::ConvertQlParametr(QlParametr *parametr)
{
    QStringList result;
    result << m_tagConverter.TagStart() + m_tagConverter.ParametrTag(parametr);
    result << QString("var %1 = %2;").arg( parametr->var()->name() ).arg( ConvertBsExpression( parametr->startValue() ));
    foreach (QlParamStatement * statement, parametr->paramStatements()) {
        result << ConvertBsStatement( statement );
    }
    result << m_tagConverter.TagEnd();
    return result.join("\n");
}

QString BsToESMAScriptConverter::ConvertQlParametrList(QlParametrList list)
{
    QStringList result;
    foreach( QlParametr * par, list){
        result << ConvertQlParametr( par );
    }
    return result.join("\n");
}

QString BsToESMAScriptConverter::ConvertQlLocationTexts(QlLocationTexts *texts)
{
    QStringList result;
    result << m_tagConverter.TagStart() + m_tagConverter.LocationTextsTag( texts );
    result << QString("AddLocationTexts( '%1', function(){ return %2; }, [\"%3\"] );")
              .arg( texts->locationId() )
              .arg(ConvertBsExpression( texts->expr()))
              .arg( texts->texts().join("\",\""));
    result << m_tagConverter.TagEnd();
    return result.join("\n");
}

QString BsToESMAScriptConverter::ConvertQlPathPriority(QlPathPriority *priority)
{
    QStringList result;
    result << m_tagConverter.TagStart() + m_tagConverter.PathPriorityTag( priority );
    result << QString("SetPathPriority( '%1', %2 );")
              .arg( priority->pathId() )
              .arg( priority->priority() );
    result << m_tagConverter.TagEnd();
    return result.join("\n");
}

QString BsToESMAScriptConverter::ConvertQlPathShowOrder(QlPathShowOrder *order)
{
    QStringList result;
    result << m_tagConverter.TagStart() + m_tagConverter.PathShowOrderTag( order );
    result << QString("SetPathShowOrder( '%1', %2 );")
              .arg( order->pathId() )
              .arg( order->showOrder() );
    result << m_tagConverter.TagEnd();
    return result.join("\n");
}

QString BsToESMAScriptConverter::ConvertQlPathPassability(QlPathPassability *pass)
{
    QStringList result;
    result << m_tagConverter.TagStart() + m_tagConverter.PathPassabilityTag( pass );
    result << QString("SetPathPassability( '%1', %2 );")
              .arg( pass->pathId() )
              .arg( pass->passability() );
    result << m_tagConverter.TagEnd();
    return result.join("\n");
}

QString BsToESMAScriptConverter::ConvertQlPathStatementList(QlPathStatementList list)
{
    QStringList result;
    foreach( QlPathStatement * stat, list){
        result << ConvertBsStatement( stat );
    }
    return result.join("\n");
}

QString BsToESMAScriptConverter::ConvertQlLocationStatementList(QlLocationStatementList list)
{
    QStringList result;
    foreach( QlLocationStatement * stat, list){
        result << ConvertBsStatement( stat );
    }
    return result.join("\n");
}


//QString BsToESMAScriptConverter::ConvertQlParametrStatement(QlParamStatement *statement)
//{
//    switch(statement->type()){
//        case QlType::Constraint:

//    }
//}

//QStringList BsToESMAScriptConverter::ConvertBsObjectList(BsObjectList list)
//{

//}

