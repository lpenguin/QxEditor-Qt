#include "ECMAScriptToBsConverter.h"

ECMAScriptToBsConverter::ECMAScriptToBsConverter()
{
    tagStart = "//!bs:";
    tagEnd = "//!bs:end";
    expTagStart = "/*!bs:";
    expTagEnd = ":!bs*/";

    FillOperatorTypes();
    FillActionTypes();
    FillConditionTypes();
    FillCharMap();
}

BsScript * ECMAScriptToBsConverter::ConvertScript(const QStringList & list) throw( ParseError )
{
    BsScript * script = new BsScript;
    BsStatementList statements = ConvertStatements( list, 0, list.count() );
    script->AddStatements( statements );
    return script;
}

BsExpression * ECMAScriptToBsConverter::ConvertExpressionStatement(const QString &str) throw( ParseError )
{
    qint32 startPos = str.indexOf( expTagStart );
    if( startPos == -1 )
        throw ParseError(QString("Missing tag start: %1").arg(str), ParseError::MissingExpressionTagStart);
    startPos += expTagStart.count();
    qint32 endPos = str.indexOf( expTagEnd );

    if( endPos == -1 )
        throw ParseError(QString("Missing tag end: %1").arg(str), ParseError::MissingExpressionTagEnd);
    QString tag = str.mid( startPos, endPos - startPos );
    return ConvertExpression( tag );
}


QlLocationStatementList ECMAScriptToBsConverter::ConvertLocationStatements(const QStringList &list)  throw( ParseError )
{
    QlLocationStatementList result;
    BsStatementList statements = ConvertStatements( list, 0, list.count() );
    foreach( BsStatement * st, statements ){
        if( st->type() == QlType::LocationTexts )
            result << ( QlLocationStatement * )st;
    }

    return result;
}

QlPathStatementList ECMAScriptToBsConverter::ConvertPathStatementList(const QStringList &list) throw( ParseError )
{
    QlPathStatementList result;
    BsStatementList statements = ConvertStatements( list, 0, list.count() );
    foreach( BsStatement * st, statements ){
        if( st->type() == QlType::PathPassability )
            result << ( QlPathPassability * )st;
        else if( st->type() == QlType::PathPriority )
            result << ( QlPathPriority * )st;
        else if( st->type() == QlType::PathShowOrder )
            result << ( QlPathShowOrder * )st;
    }

    return result;
}

QlParametrList ECMAScriptToBsConverter::ConvertParametrList(const QStringList &list) throw( ParseError )
{
    QlParametrList result;
    BsStatementList statements = ConvertStatements( list, 0, list.count() );
    foreach( BsStatement * st, statements ){
        if( st->type() == QlType::Parametr )
            result << ( QlParametr * )st;
    }

    return result;
}


BsStatementList ECMAScriptToBsConverter::ConvertStatements(const QStringList &list, qint32 startIndex, qint32 endIndex)  throw( ParseError )
{
    BsStatementList result;
    BsStatement * st;
    for( qint32 i = startIndex; i <= endIndex && i < list.count() ; i++){
        st = ConvertStatement( list, i);
        if( st )
            result << st;
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

qint32 ECMAScriptToBsConverter::FindTagEnd(const QStringList & list, qint32 startIndex) const throw( ParseError )
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
    return tag.replace( QRegExp("\\(.*"), "");
}

BsStatement * ECMAScriptToBsConverter::ConvertStatement(const QStringList &list, qint32 &startIndex) throw( ParseError )
{
//    BsStatement *
    QString line = list[startIndex];
    if( ! line.startsWith( tagStart ))
        return 0;

    if( line.startsWith( tagEnd ))
        return 0;

    line.replace(QRegExp(QString("^") + tagStart ), "");
    QString tag = tagName( line );
int a;
    if( tag == "ql.show"){
         a = 0;
    }
    qint32 endIndex = FindTagEnd(list, startIndex );
    QStringList tags = tagArguments( line );
    BsStatementList statements = ConvertStatements( list, startIndex + 1, endIndex );
    startIndex = endIndex;


    if( tag == "act"){
        return ConvertAction(tags );
    } else if (tag == "if") {
        return ConvertIf( tags, statements);
    } else if (tag == "user") {
        return ConvertUserString( line );
    } else if (tag == "func") {
        return ConvertFunctionCall( tags );
    } else if (tag == "vdef") {
        return ConvertVariableDefinition( tags );
    } else if (tag == "ql.cons") {
        return ConvertConstraint( tags );
    } else if (tag == "ql.icons") {
        return ConvertIntConstraint( tags );
    } else if (tag == "ql.trig") {
        return ConvertTrigger( tags, statements );
    } else if (tag == "ql.bound") {
        return ConvertBoundTrigger( tags, statements );
    } else if (tag == "ql.show") {
        return ConvertShowVariable( tags );
    } else if (tag == "ql.param") {
        return ConvertParametr( tags, statements );
    } else if (tag == "ql.texts") {
        return ConvertLocationTexts( tags );
    } else if (tag == "ql.prior") {
        return ConvertPathPriority( tags );
    } else if (tag == "ql.pass") {
        return ConvertPathPassability( tags );
    } else if (tag == "ql.showord") {
        return ConvertPathShowOrder( tags );
    } else if (tag == "ql.empty") {
        return ConvertLocationEmpty( tags );
    } else if( tag == "ql.alwshow") {
        return ConvertPathAlwaysShow( tags );
    }else
        throw ParseError( QString("Unknown tag: %1").arg(tag), ParseError::UnknownTag );
}

BsIf * ECMAScriptToBsConverter::ConvertIf( QStringList tags, BsStatementList statements ){
    BsExpression  * ex = ConvertExpression( tags.takeFirst() );
    return new BsIf( ex, statements );
}

BsAction * ECMAScriptToBsConverter::ConvertAction(QStringList tags ) {
    QString actionType = tags.takeFirst();
    QString varName = tags.takeFirst();
    BsExpression * expr = ConvertExpression(  tags.takeFirst() );
    BsObject::BsOperation operation = ConvertActionOperation( actionType );
    return new BsAction( new BsVariable(varName), expr,  operation );
}

QStringList ECMAScriptToBsConverter::tagArguments(const QString &tag)
{
    QString argStr = tag;
    argStr = argStr.replace( QRegExp("^[^\(]*"), "" );
    argStr = argStr.mid( 1 , argStr.count() - 2);
    return splitSmart( argStr );
}

BsExpression * ECMAScriptToBsConverter::ConvertExpression(const QString &tag)
{
    QString name = tagName( tag );
    if( name == "val"){
        return ConvertValue( tag );
    } else if( name == "var"){
        return ConvertVariable( tag );
    } else if( name == "null"){
        return new BsNull;
    } else if( name  == "expr"){
        return ConvertOperator( tag );
    } else if( name  == "cond"){
        return ConvertCondition( tag );
    } else if( name  == "ran"){
        return ConvertRange( tag );
    } else if( name  == "cran"){
        return ConvertCalcRange( tag );
    } else if( name  == "user"){
        return ConvertUserString(tag );
    } else if( name  == "func"){
        return ConvertFunction( tag );
    } else
        throw ParseError( QString("Unknown tag: %1").arg(name), ParseError::UnknownTag );
}


BsOperator * ECMAScriptToBsConverter::ConvertOperator(const QString &tag){
    QStringList tags = tagArguments( tag );
    BsOperator::BsOperation type = ConvertOperationType( tags.takeFirst() );
    BsExpressionList arguments;
    foreach(QString item, tags){
        arguments<<ConvertExpression( item );
    }
    return new BsOperator( type, arguments );
}

BsCondition * ECMAScriptToBsConverter::ConvertCondition(const QString &tag)
{
    QStringList tags = tagArguments( tag );
    BsCondition::BsConditionType type = ConvertConditionType( tags.takeFirst() );
    BsExpressionList arguments;
    foreach(QString item, tags){
        arguments<<ConvertExpression( item );
    }
    return new BsCondition( type, arguments );
}

BsRange * ECMAScriptToBsConverter::ConvertRange(const QString &tag)
{
    QStringList tags = tagArguments( tag );
    return new BsRange( ConvertExpression( tags.takeFirst()),
                        ConvertExpression( tags.takeFirst() ),
                        false);
}

BsUserString * ECMAScriptToBsConverter::ConvertUserString(const QString &tag)
{
    return new BsUserString( tagArguments( tag ).takeFirst() );
}

BsFunction * ECMAScriptToBsConverter::ConvertFunction(const QString &tag)
{
    QStringList tags = tagArguments( tag );
    QString name = tags.takeFirst();
    BsExpressionList arguments;
    foreach(QString item, tags){
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
//    m_operatorTypes.insert( "mod", BsObject::`);

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

void ECMAScriptToBsConverter::FillCharMap()
{
    m_charMap.insert( "&comm;", ","  );
    m_charMap.insert( "&lb;", "(");
    m_charMap.insert( "&rb;", ")");
    m_charMap.insert( "&lsb;", "[");
    m_charMap.insert( "&rsb;", "]");
    m_charMap.insert( "&nl;", "\n");
    m_charMap.insert( "&rl;", "\r");
    m_charMap.insert( "&tb;", "\t");
    m_charMap.insert( "&sq;", "\'");
    m_charMap.insert( "&dq;", "\"");
}

BsFunctionCall * ECMAScriptToBsConverter::ConvertFunctionCall( QStringList tags )
{
    QString functionName = tags.takeFirst();
    BsExpressionList arguments;
    foreach(QString str, tags)
        arguments << ConvertExpression( str );
    return new BsFunctionCall( functionName, arguments  );
}

BsVariableDefinition * ECMAScriptToBsConverter::ConvertVariableDefinition(QStringList tags )
{
    QString varTag = tags.takeFirst();
    BsExpression * value = ConvertExpression(  tags.takeFirst() );
    return new BsVariableDefinition(  ConvertVariable(varTag ), value  );
}

QlTrigger * ECMAScriptToBsConverter::ConvertTrigger(QStringList tags, BsStatementList statements)
{
//    qint32 endIndex = FindTagEnd(list, startIndex );
//    QStringList tags = tagContents( line );
//    QString varTag = tags.takeFirst();
//    BsExpression * value = ConvertExpression(  tags.takeFirst() );
//    startIndex = endIndex;
//    return new BsVariableDefinition( new BsVariable(
//                                        tagContents( varTag ).takeFirst()), value );

    BsExpression  * ex = ConvertExpression( tags.takeFirst() );
    return new QlTrigger( ex, statements );
}

QlBoundTrigger * ECMAScriptToBsConverter::ConvertBoundTrigger( QStringList tags, BsStatementList statements )
{
//    QString type;
//    if( trig->boundType() == QlBoundTrigger::Min){
//        type = "min";
//    }else{
//        type = "max";
//    }
//    return QString("ql.bound(%1, %2, %3, '%4')")
//            .arg(VariableTag(trig->var()))
//            .arg( type )
//            .arg(ValueTag(trig->value()))
//            .arg(  trig->text() );
    BsVariable * var = ConvertVariable( tags.takeFirst() );
    QString typeStr = tags.takeFirst();
    QlBoundTrigger::BoundType type;
    if( typeStr == "min")
        type = QlBoundTrigger::Min;
    else
        type = QlBoundTrigger::Max;
    BsValue * val = ConvertValue( tags.takeFirst() );
    QString text = ConvertString( tags.takeFirst() );
    return new QlBoundTrigger( var, val, type,text );
}

QlConstraint * ECMAScriptToBsConverter::ConvertConstraint( QStringList tags )
{
    return new QlConstraint( ConvertVariable( tags.takeFirst() ),
                             ConvertExpression(  tags.takeFirst() ),
                             ConvertExpression(  tags.takeFirst() )
                            );
}

QlLocationTexts * ECMAScriptToBsConverter::ConvertLocationTexts( QStringList tags )
{
    QString locationId = ConvertString( tags.takeFirst() );
    BsExpression * ex = ConvertExpression( tags.takeFirst() );
    QStringList texts, tagTextsContents;
    tagTextsContents = parseList( tags.takeFirst() );
    foreach( QString str, tagTextsContents )
        texts << ConvertString( str );
    return new QlLocationTexts( locationId, texts, ex );
}

QlShowVariable * ECMAScriptToBsConverter::ConvertShowVariable( QStringList tags )
{
    BsVariable * var = ConvertVariable( tags.takeFirst() );
    QStringList rangesTags = parseList( tags.takeFirst() );
    BsRangeList ranges;
    foreach (QString str, rangesTags) {
        ranges << ConvertRange( str );
    }
    QString textsStr = tags.takeFirst();
//    qDebug()<<textsStr;
    QStringList texts, textsTags = splitSmart( midStr( textsStr, 1, 1) );
    foreach( QString str, textsTags )
        texts << ConvertString( str );
//    qDebug()<<texts.count();
    bool showOnZero = tags.takeFirst() == "true";
    return new QlShowVariable( var, ranges, texts, showOnZero );
}

QlPathPassability * ECMAScriptToBsConverter::ConvertPathPassability(  QStringList tags )
{
    QString pathId = ConvertString( tags.takeFirst() );
    qint32 passability = tags.takeFirst().toInt();
    return new QlPathPassability(pathId, passability );
}


QlPathPriority * ECMAScriptToBsConverter::ConvertPathPriority( QStringList tags )
{
    QString pathId = ConvertString( tags.takeFirst() );
    qreal priority = tags.takeFirst().toDouble();
    return new QlPathPriority(pathId, priority );
}

QlPathShowOrder * ECMAScriptToBsConverter::ConvertPathShowOrder( QStringList tags )
{
    QString pathId = ConvertString( tags.takeFirst() );
    qint32 showOrder = tags.takeFirst().toInt();
    return new QlPathShowOrder(pathId, showOrder );
}

BsVariable * ECMAScriptToBsConverter::ConvertVariable(const QString &tag)
{
    return new BsVariable( tagArguments( tag ).takeFirst() );
}

BsValue * ECMAScriptToBsConverter::ConvertValue(const QString &tag)
{
    QString v = tagArguments( tag ).takeFirst();
    return new BsValue( v );
}

QString ECMAScriptToBsConverter::ConvertString(QString value)
{
    value = unpackSpecialChars( value );
    return value.replace(QRegExp("^\'"),"").replace(QRegExp("\'$"),"");
}

QlParametr * ECMAScriptToBsConverter::ConvertParametr(QStringList tags, BsStatementList statements)
{
    BsVariable * var = ConvertVariable( tags.takeFirst() );
    BsExpression * startValue = ConvertExpression( tags.takeFirst() );
    QlParamStatementList paramStatements;
    foreach(BsStatement * st, statements){
        switch( st->type()){
        case  QlType::Constraint:
            paramStatements << (QlConstraint *) st;
            break;
        case  QlType::BoundTrigger:
            paramStatements << (QlBoundTrigger *) st;
            break;
        case  QlType::ShowVariable:
            paramStatements << (QlShowVariable *) st;
            break;
        default:
            throw ParseError( "Invalid statement", ParseError::InvalidStatement);
        }
    }
    return new QlParametr( var, startValue, paramStatements );
}

//QScriptValue ECMAScriptToBsConverter::parseTag(QString tag)
//{
//    QScriptValue sc;
//    QScriptEngine engine;
//    sc = engine.evaluate("("+ tag +")");
//    sc
//}


QStringList ECMAScriptToBsConverter::parseList(const QString &str) const
{
    QString mid = midStr( str, 1, 1 );
    return splitSmart( mid );
}

QString ECMAScriptToBsConverter::unpackSpecialChars(const QString &str) const  {
    QMapIterator<QString, QString> i(m_charMap);
    QString s = str;
    while(i.hasNext()){
        i.next();
        s = s.replace(i.key(), i.value());
    }
    return s;
}

BlockScript::QlLocationEmpty * ECMAScriptToBsConverter::ConvertLocationEmpty(QStringList tags)
{
    QString locationId = ConvertString( tags.takeFirst() );
    return new QlLocationEmpty(locationId);
}

BlockScript::BsRange * ECMAScriptToBsConverter::ConvertCalcRange(const QString &tag)
{
    QStringList tags = tagArguments( tag );
    return new BsRange( ConvertExpression( tags.takeFirst()),
                       ConvertExpression( tags.takeFirst() ),
                       true);
}

BlockScript::QlIntConstraint * ECMAScriptToBsConverter::ConvertIntConstraint(QStringList tags)
{
    return new QlIntConstraint( ConvertVariable( tags.takeFirst() ) );
}

BlockScript::QlPathAlwaysShow * ECMAScriptToBsConverter::ConvertPathAlwaysShow(QStringList tags)
{
    QString pathId = ConvertString( tags.takeFirst() );
    return new QlPathAlwaysShow(pathId );
}
