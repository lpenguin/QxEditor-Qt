#include "QlJSONInfoReader.h"

QlJSONInfoReader::QlJSONInfoReader()
{
}
QlLocationTexts * QlJSONInfoReader::getLocationTexts( QlLocationStatementList statements  ){

    foreach( QlLocationStatement * st, statements ){
        if( st->type() == QlType::LocationTexts ){
            QlLocationTexts * texts = (QlLocationTexts*) st;
            return texts;
        }
    }
    return 0;
}

VerInfo * QlJSONInfoReader::ReadVerInfo(QScriptValue value)
{
    QlVerInfo * info = new QlVerInfo();
    BsScript * actions = m_converter.ConvertScript( value.property("actions").toString().split("\n") );
    QlLocationStatementList sts = m_converter.ConvertLocationStatements( value.property("init").toString().split("\n") );
    QString text;
    QlLocationTexts * texts = getLocationTexts( sts );
    if( texts ){
        //        QlLocationStatementList statements;
        if( texts->texts().count() == 1 )
            sts.clear();
        text = texts->firstText();
    }else
        text = value.property("text").toString();
    info->setActions( actions );
    info->setText( text );
    info->setLocationStatements( sts );
    info->setId( value.property("id").toString() );
    info->setVerType( Str2Type( value.property("type").toString() ) );

    return info;

}


EdgeInfo * QlJSONInfoReader::ReadEdgeInfo(QScriptValue value)
{
    QlEdgeInfo * info = new QlEdgeInfo();
    QlPathStatementList pathStatements = m_converter.ConvertPathStatementList( value.property("init").toString().split("\n") );
    BsScript * actions = m_converter.ConvertScript( value.property("actions").toString().split("\n") );
    BsExpression * ex = m_converter.ConvertExpressionStatement( value.property("conditions").toString() );
    info->setId( value.property("id").toString() );
    info->setQuestion( value.property("question").toString() );
    info->setText( value.property("text").toString() );
    info->setPathStatements( pathStatements );
    info->setActions( actions );
    info->setExpression( ex );
    return info;
}

GraphInfo * QlJSONInfoReader::ReadGraphInfo(QScriptValue value)
{
    QlGraphInfo * info = new QlGraphInfo();
    QlParametrList paramList = m_converter.ConvertParametrList(  value.property("init").toString().split("\n") );
    BsScript * actions = m_converter.ConvertScript( value.property("actions").toString().split("\n") );
    info->setId( value.property("id").toString() );
    info->setName( value.property("name").toString() );
    info->setDescription( value.property("description").toString() );
    info->setParametrList( paramList );
    info->setActions( actions );
    return info;
}
