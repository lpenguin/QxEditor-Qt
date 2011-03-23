#include "ECMAScriptToBsConverter.h"

ECMAScriptToBsConverter::ECMAScriptToBsConverter()
{
    tagStart = "//!bs:";
    tagEnd = "//!bs:end";
    FillOperatorTypes();
    FillActionTypes();
    FillConditionTypes();
}

BlockScript * ECMAScriptToBsConverter::ConvertScript(const QStringList & list) throw( ParseError )
{
    BlockScript * script = new BlockScript;
    BsStatementList statements = ConvertStatements( list, 0, list.count() );
    script->AddStatements( statements );
    return script;
}

BsStatementList ECMAScriptToBsConverter::ConvertStatements(const QStringList &list, qint32 startIndex, qint32 endIndex)
{
    BsStatementList result;
    BsStatement * st;
    for( qint32 i = startIndex; i <= endIndex && i < list.count() ; i++){
        st = ConvertStatement( list, i);
        if( st )
            list << st;
    }
    return result;
}

//QString ECMAScriptToBsConverter::TagStart() const
//{
//    return "//!bs:";
//}

//QString ECMAScriptToBsConverter::TagEnd() const
//{
//    return "//!bs:end";
//}

qint32 ECMAScriptToBsConverter::FindTagEnd(const QStringList & list, qint32 startIndex) throw( ParseError )
{
    qint32 tagCounter = 1, i;
    for( i = startIndex + 1; i < list.count() && tagCounter; i++ ){
        QString line = list[i];
        if( line.startsWith( tagEnd ))
            tagCounter--;
        else if( line.startsWith( tagStart ) )
            tagCounter++;
    }
    if( tagCounter ){
        throw ParseError("Missing statement end", ParseError::MissingStatementEnd );
    }
    return i - 1;
}

qint32 ECMAScriptToBsConverter::tagType(QString tag)
{

}

QString ECMAScriptToBsConverter::tagName(QString tag)
{
    return tag.replace( QRegExp("\[.*"), "");
}

BsStatement * ECMAScriptToBsConverter::ConvertStatement(const QStringList &list, qint32 &startIndex) throw( ParseError )
{
//    BsStatement *
    QString line = list[startIndex];
    if( ! line.startsWith( tagStart ))
        return 0;

    line.replace(QRegExp(QString("^") + tagStart ), "");
    QString tag = tagName( line );
    if( tag == "act"){
        return ConvertAction(list, startIndex, line);
    } else if (tag == "if") {
        return ConvertIf(list, startIndex, line);
    } else if (tag == "user") {
        return ConvertUserString( line);
    }
}

BsIf * ECMAScriptToBsConverter::ConvertIf(const QStringList &list, qint32 &startIndex, const QString & line) throw( ParseError ){
    qint32 endIndex = FindTagEnd(list, startIndex );
    QStringList contents = tagContents( line );
    BsExpression  * ex = ConvertExpression( contents.takeFirst() );
    BsStatementList statements = ConvertStatements( list, startIndex + 1, endIndex );
    startIndex = endIndex;
    return new BsIf( ex, statements );
}

BsAction * ECMAScriptToBsConverter::ConvertAction(const QStringList &list, qint32 &startIndex, const QString & line) throw( ParseError ){
    qint32 endIndex = FindTagEnd(list, startIndex );
    QStringList contents = tagContents( line );
    QString actionType = contents.takeFirst();
    QString varName = contents.takeFirst();
    BsExpression * expr = ConvertExpression(  contents.takeFirst() );
    BsObject::BsOperation operation = ConvertActionOperation( actionType );
    startIndex = endIndex;
    return new BsAction( new BsVariable(varName), expr,  operation );
}

QStringList ECMAScriptToBsConverter::tagContents(const QString &tag)
{
//    / \( (?> [^)(]+ | (?R) )+ \) /x
    QRegExp rx( "/\[(?>[^\[\]+|(?R))+\]" );
    rx.indexIn(tag);
    return rx.cap(1).split(",");

}

BsExpression * ECMAScriptToBsConverter::ConvertExpression(const QString &tag)
{
    QString name = tagName( tag );
    if( name == "val"){
        return new BsValue( tagContents( tag ).takeFirst() );
    } else if( name == "var"){
        return new BsVariable( tagContents( tag ).takeFirst() );
    } else if( name == "null"){
        return new BsNull;
    } else if( name  == "expr"){
        return ConvertOperator( tag );
    } else if( name  == "cond"){
        return ConvertCondition( tag );
    } else if( name  == "ran"){
        return ConvertRange( tag );
    } else if( name  == "user"){
        return ConvertUserString(tag );
    } else if( name  == "func"){
        return ConvertFunction( tag );
    } else
        throw ParseError( QString("Unknown tag: %1").arg(name), ParseError::UnknownTag );
}


BsOperator * ECMAScriptToBsConverter::ConvertOperator(const QString &tag){
    QStringList contents = tagContents( tag );
    BsOperator::BsOperation type = ConvertOperationType( contents.takeFirst() );
    BsExpressionList arguments;
    foreach(QString item, contents){
        arguments<<ConvertExpression( item );
    }
    return new BsOperator( type, arguments );
}

BsCondition * ECMAScriptToBsConverter::ConvertCondition(const QString &tag)
{
    QStringList contents = tagContents( tag );
    BsCondition::BsConditionType type = ConvertConditionType( contents.takeFirst() );
    BsExpressionList arguments;
    foreach(QString item, contents){
        arguments<<ConvertExpression( item );
    }
    return new BsCondition( type, arguments );
}

BsRange * ECMAScriptToBsConverter::ConvertRange(const QString &tag)
{
    QStringList contents = tagContents( tag );
    return new BsRange( ConvertExpression( contents.takeFirst()),
                       ConvertExpression( contents.takeFirst() ));
}

BsUserString * ECMAScriptToBsConverter::ConvertUserString(const QString &tag)
{
    return tagContents( tag ).takeFirst();
}

BsFunction * ECMAScriptToBsConverter::ConvertFunction(const QString &tag)
{
    QStringList contents = tagContents( tag );
    QString name = contents.takeFirst();
    BsExpressionList arguments;
    foreach(QString item, contents){
        arguments<<ConvertExpression( item );
    }
    return new BsFunction( name, arguments );
}

BsObject::BsOperation ECMAScriptToBsConverter::ConvertActionOperation(const QString &operation)
{
    return m_actionTypes[operation];
}
BsCondition::BsConditionType ECMAScriptToBsConverter::ConvertConditionType(const QString &condition)
{
    return m_conditionTypes[condition];
}

BsOperator::BsOperation ECMAScriptToBsConverter::ConvertOperationType(const QString &operation)
{
    return m_operatorTypes[operation];
}
void ECMAScriptToBsConverter::FillOperatorTypes()
{
   // m_expressionTypes.insert( BsObject::Mov, "mov");
    m_operatorTypes.insert( "add", BsObject::Addition);
    m_operatorTypes.insert( "div", BsObject::Division);
    m_operatorTypes.insert( "sub", BsObject::Substraction);
    m_operatorTypes.insert( "mul", BsObject::Multiplication);

}

void ECMAScriptToBsConverter::FillActionTypes()
{
    m_actionTypes.insert( "madd", BsObject::Addition);
    m_actionTypes.insert( "mdiv", BsObject::Division);
    m_actionTypes.insert( "msub", BsObject::Substraction);
    m_actionTypes.insert( "mmul", BsObject::Multiplication);
    m_actionTypes.insert( "mov", BsObject::Mov);
    m_actionTypes.insert( "show", BsObject::Show);
    m_actionTypes.insert( "hide", BsObject::Hide);
}

void ECMAScriptToBsConverter::FillConditionTypes()
{
    m_conditionTypes.insert( "gt", BsCondition::Greater);
    m_conditionTypes.insert( "ge", BsCondition::GreaterEq);
    m_conditionTypes.insert( "lt", BsCondition::LowerEq);
    m_conditionTypes.insert( "le", BsCondition::Lower);
    m_conditionTypes.insert( "eq", BsCondition::Equals);
    m_conditionTypes.insert( "in", BsCondition::In);
    m_conditionTypes.insert( "mul", BsCondition::Multiple);
    m_conditionTypes.insert( "and", BsCondition::And);
    m_conditionTypes.insert( "or", BsCondition::Or);
    m_conditionTypes.insert( "not", BsCondition::Not);

}


