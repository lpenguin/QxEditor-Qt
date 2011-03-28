#include "QmEqToBsConverter.h"

QmEqToBsConverter::QmEqToBsConverter()
{
    FillOperations();
    FillConditionTypes();
    FillOperationTypes();
}

void QmEqToBsConverter::FillOperations()
{
    m_operations    << OperatorPair( Or,    ( QStringList() << "or") )
                    << OperatorPair( And,   ( QStringList() << "and" ) )
                    << OperatorPair( Comp,  ( QStringList() << ">=" << "<=" << "=" << "<>" << "<" << ">" ) )
                    << OperatorPair( In,    ( QStringList() << "in" ) )
                    << OperatorPair( To,    ( QStringList() << "to" ) )
                    << OperatorPair( Math,  ( QStringList() << "+" << "-" << "*" << "/" << "mod" << "div" ) );

}

BlockScript::BsExpression * QmEqToBsConverter::parseExpression(const QString &equation) throw( ParseError )
{
    foreach( OperatorPair operatorPair, m_operations ){
        QStringList operatorGroup = operatorPair.second;
        QString oper = findOperator( equation, operatorGroup );
        if( !oper.isEmpty() ){
            QStringList slices = splitSmart( equation, oper );
            BsExpressionList exprs = parseExpressions( slices );
            switch( operatorPair.first ){
            case And:
//                return new BsCondition( BsCondition::And, exprs );
//                break;
            case Or:
//                return new BsCondition( BsCondition::Or, exprs );
//                break;
            case Comp:
//                if( exprs.count() != 2)
//                    throw new Error(QString("Invalid arguments count for '%1' (%2)").arg(oper).arg(equation));
//                return new BsCondition( m_conditionTypes[oper], exprs );
//                break;
            case In:
                return new BsCondition( m_conditionTypes[oper], exprs );
//                if( exprs.count() != 2)
//                    throw new Error(QString("Invalid arguments count for '%1' (%2)").arg(oper).arg(equation));
                break;
            case To:
                if( exprs.count() != 2)
                    throw new Error(QString("Invalid arguments count for '%1' (%2)").arg(oper).arg(equation));
                return new BsRange( exprs.takeFirst(), exprs.takeFirst() );
            case Math:
                //qDebug()<<oper<<" "<<m_operationTypes[oper];
                return new BsOperator( m_operationTypes[oper], exprs );
            }
        }
    }
    return parseArg( equation );
}

QString QmEqToBsConverter::findOperator(const QString &expr, const QStringList &operators)
{
    foreach( QString oper, operators ){
        //qDebug() << expr << oper ;
        if( FindNextDelim( expr, 0, oper) != -1 )
            return oper;
    }
    return QString("");
}

BlockScript::BsExpressionList QmEqToBsConverter::parseExpressions(const QStringList &exprs) throw( ParseError )
{
    BsExpressionList result;
    foreach( QString expr, exprs )
        result << parseExpression( expr );
    return result;
}

void QmEqToBsConverter::FillConditionTypes()
{
    m_conditionTypes.insert( ">", BsCondition::Greater);
    m_conditionTypes.insert( ">=", BsCondition::GreaterEq);
    m_conditionTypes.insert( "<", BsCondition::LowerEq);
    m_conditionTypes.insert( "<=", BsCondition::Lower);
    m_conditionTypes.insert( "=", BsCondition::Equals);
    m_conditionTypes.insert( "<>", BsCondition::NotEquals);
    m_conditionTypes.insert( "in", BsCondition::In);
//    m_conditionTypes.insert( "mul", BsCondition::Multiple);
    m_conditionTypes.insert( "and", BsCondition::And);
    m_conditionTypes.insert( "or", BsCondition::Or);
    //    m_conditionTypes.insert( "not", BsCondition::Not);
}

void QmEqToBsConverter::FillOperationTypes()
{
    m_operationTypes.insert( "+", BsObject::Addition);
    m_operationTypes.insert( "/", BsObject::Division);
    m_operationTypes.insert( "-", BsObject::Substraction);
    m_operationTypes.insert( "*", BsObject::Multiplication);
    m_operationTypes.insert( "div", BsObject::Div);
    m_operationTypes.insert( "mod", BsObject::Mod);
}

bool QmEqToBsConverter::isVariable(const QString &arg)
{
    return QRegExp("^\\w+[\\d\\w]*$").indexIn( arg ) != -1;
}

bool QmEqToBsConverter::isRange(const QString &arg)
{
    return QRegExp("\\.\\.").indexIn( arg ) != -1;
}

bool QmEqToBsConverter::isSet(const QString &arg)
{
    return QRegExp("^[^\\]^\\[]+;[^\\]^\\[]+$").indexIn( arg ) != -1;
}

bool QmEqToBsConverter::isValue(const QString &arg)
{
    return QRegExp("^\\d+$").indexIn( arg ) != -1;
}

BlockScript::BsExpression * QmEqToBsConverter::parseArg(const QString &arg) throw( ParseError )
{
    QString str = arg;
    str = str.remove(QRegExp("^\\[")).remove(QRegExp("\\]$"));
    qDebug()<< str;
    if( isVariable( str ) ){
        return parseVariable( str );
    } else if( isSet( str )){
        return parseSet( str );
    } else if( isRange( str )){
        return parseRange( str );
    } else if( isValue( str )){
        return parseValue( str );
    } else
        throw( ParseError(QString("Unknown tag: %1").arg(arg), ParseError::UnknownTag));
}

BlockScript::BsVariable * QmEqToBsConverter::parseVariable(const QString &arg) throw( ParseError )
{
    return new BsVariable(arg );
}

BlockScript::BsRange * QmEqToBsConverter::parseRange(const QString &arg) throw( ParseError )
{
    QStringList items = arg.split("..");
    return new BsRange( parseExpression(items.takeFirst()), parseExpression(items.takeLast()));
}

BlockScript::BsSet * QmEqToBsConverter::parseSet(const QString &arg) throw( ParseError )
{
    QStringList items = arg.split(";");
    return new BsSet(parseExpressions(items));
}

BlockScript::BsValue * QmEqToBsConverter::parseValue(const QString &arg) throw( ParseError )
{
    return new BsValue( arg );
}
