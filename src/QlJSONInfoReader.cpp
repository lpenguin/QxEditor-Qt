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

BaseVerInfo * QlJSONInfoReader::ReadVerInfo(QScriptValue value)
{
    QlVerInfo * info = new QlVerInfo();
    try{
        BlockScript * actions = m_converter.ConvertScript( value.property("actions").toString().split("\n") );
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
    }catch(ParseError & e ){
        qDebug()<<QString("Parse error: %1").arg(e.message());
        throw ReaderError(QString("Parse error: %1").arg(e.message()));
    }
    return info;

}


BaseEdgeInfo * QlJSONInfoReader::ReadEdgeInfo(QScriptValue value)
{
    QlEdgeInfo * info = new QlEdgeInfo();
    try{

        QlPathStatementList pathStatements = m_converter.ConvertPathStatementList( value.property("init").toString().split("\n") );
        BlockScript * actions = m_converter.ConvertScript( value.property("actions").toString().split("\n") );
        BsExpression * ex = m_converter.ConvertExpressionStatement( value.property("conditions").toString() );
        info->setId( value.property("id").toString() );
        info->setQuestion( value.property("question").toString() );
        info->setText( value.property("text").toString() );
        info->setPathStatements( pathStatements );
        info->setActions( actions );
        info->setExpression( ex );
    }catch(ParseError & e ){
        qDebug()<<QString("Parse error: %1").arg(e.message());
        throw ReaderError(QString("Parse error: %1").arg(e.message()));
    }
    return info;
}

BaseGraphInfo * QlJSONInfoReader::ReadGraphInfo(QScriptValue value)
{
    QlGraphInfo * info = new QlGraphInfo();
    try{
        QlParametrList paramList = m_converter.ConvertParametrList(  value.property("init").toString().split("\n") );
        BlockScript * actions = m_converter.ConvertScript( value.property("actions").toString().split("\n") );
        info->setId( value.property("id").toString() );
        info->setName( value.property("name").toString() );
        info->setDescription( value.property("description").toString() );
        info->setParametrList( paramList );
        info->setActions( actions );
    }catch(ParseError & e ){
        qDebug()<<QString("Parse error: %1").arg(e.message());
        throw ReaderError(QString("Parse error: %1").arg(e.message()));
    }
    return info;
}
