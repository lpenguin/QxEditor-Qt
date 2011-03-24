#include "QlJSONInfoWriter.h"

QlJSONInfoWriter::QlJSONInfoWriter()
{
}


QStringList QlJSONInfoWriter::VerInfo2JSON(BaseVerInfo *info)
{
    QStringList props;
    QlVerInfo * qlInfo = (QlVerInfo *)info;
    QString text = qlInfo->firstText();
    QString jText = Property2JSON("text", text);
    props<<Property2JSON("id", qlInfo->id())
            <<Property2JSON("actions", m_converter.ConvertBlockSript( qlInfo->actions() ))
            <<Property2JSON("init", m_converter.ConvertQlLocationStatementList( qlInfo->locationStatements() ))
            <<Property2JSON("text", text)
            <<Property2JSON("type", Type2Str(qlInfo->verType()));
    return props;
}

QStringList QlJSONInfoWriter::EdgeInfo2JSON(BaseEdgeInfo *info)
{
    QStringList props;
    QlEdgeInfo * qlInfo = (QlEdgeInfo *)info;
    props<<Property2JSON("id", qlInfo->id())
            <<Property2JSON("actions", m_converter.ConvertBlockSript( qlInfo->actions() ))
            <<Property2JSON("init", m_converter.ConvertQlPathStatementList( qlInfo->pathStatements() ))
            <<Property2JSON("text", qlInfo->text())
            <<Property2JSON("conditions", m_converter.ConvertBsConditionStatement( qlInfo->expression() ))
            <<Property2JSON("question", qlInfo->question());

    return props;
}

QStringList QlJSONInfoWriter::GraphInfo2JSON(BaseGraphInfo *info)
{
    QStringList props;
    QlGraphInfo * qlInfo = (QlGraphInfo *)info;
    props<<Property2JSON("actions",m_converter.ConvertQlParametrList( qlInfo->parametrList() ))
            <<Property2JSON("name", qlInfo->name())
            <<Property2JSON("description", qlInfo->description());
    return props;
}
