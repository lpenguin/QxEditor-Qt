#include "JSONGraphWriter.h"

QString Type2Str( SimpleVerInfo::VerType type ){
        if( type == SimpleVerInfo::start	)
                return "start";
        if( type == SimpleVerInfo::odinary	)
                return "odinary";
        if( type == SimpleVerInfo::fail	)
                return "fail";
        if( type == SimpleVerInfo::win	)
                return "win";
        return "odinary";
}

QString Property2JSON(QString name, QString value){
    return "\""+name+"\""+":\""+value.replace("\"","\\\"").replace("\n", "\\n").replace("\t","\\t")+"\"";
}

void JSONGraphWriter::WriteGraph( BaseGraph * graph, const QString & filename ){
    QFile file( filename );
    if ( file.open(  QIODevice::WriteOnly ) ) {

        QTextStream stream( &file );
        QStringList props;
        QStringList versStrings;
        foreach(BaseVer * v, graph->vers()){
            versStrings<<Ver2JSON(v);
        }

        props<< m_infoWriter->GraphInfo2JSON( graph->info())
                <<"\"vers\":[\n  "+versStrings .join(",\n  ")+"]";
        stream<<"{"+props.join(",\n ")+"}";
    }
}




QString JSONGraphWriter::Edge2JSON(BaseEdge * edge){
    QStringList props;
    props << m_infoWriter->EdgeInfo2JSON( edge->info())
             << Property2JSON("nextVer", edge->v1()->info()->id());
    return "{"+props.join(",\n  ")+"}";
}

QString JSONGraphWriter::Ver2JSON(BaseVer * ver){
    QStringList props;
    props<<m_infoWriter->VerInfo2JSON(ver->info());
    QStringList edgesStrings;
    foreach(BaseEdge * e, ver->parentGraph()->edges()){
        if(e->v0() == ver ){
            edgesStrings<<Edge2JSON( e );
        }
    }
    props<<"\"edges\":[\n   "+edgesStrings.join(",\n   ")+"]";
    return "{"+props.join(",\n   ")+"}";
}

QStringList SimpleJSONInfoWriter::VerInfo2JSON(BaseVerInfo *info)
{
    QStringList props;
    SimpleVerInfo * simpleInfo = (SimpleVerInfo *)info;
    props<<Property2JSON("id", simpleInfo->id())
            <<Property2JSON("actions", simpleInfo->actions())
            <<Property2JSON("text", simpleInfo->text())
            <<Property2JSON("type", Type2Str(simpleInfo->verType()));
    return props;
}

QStringList SimpleJSONInfoWriter::EdgeInfo2JSON(BaseEdgeInfo *info)
{
    QStringList props;
    SimpleEdgeInfo * simpleInfo = (SimpleEdgeInfo *)info;
    props<<Property2JSON("id", simpleInfo->id())
            <<Property2JSON("actions", simpleInfo->actions())
            <<Property2JSON("text", simpleInfo->text())
            <<Property2JSON("conditions", simpleInfo->conditions())
            <<Property2JSON("question", simpleInfo->question());

    return props;
}

QStringList SimpleJSONInfoWriter::GraphInfo2JSON(BaseGraphInfo *info)
{
    QStringList props;
    SimpleGraphInfo * simpleInfo = (SimpleGraphInfo *)info;
    props<<Property2JSON("actions", simpleInfo->actions())
            <<Property2JSON("name", simpleInfo->name())
            <<Property2JSON("description", simpleInfo->description());
    return props;
}
