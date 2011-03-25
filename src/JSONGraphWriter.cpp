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
    return "\""+name+"\""+":\""+value.replace("\"","\\\"").replace("\r\n", "\\n").replace("\n", "\\n").replace("\t","\\t")+"\"";
}

void JSONGraphWriter::WriteGraph( Graph * graph, const QString & filename ){
    QFile file( filename );
    if ( file.open(  QIODevice::WriteOnly ) ) {

        QTextStream stream( &file );
        QStringList props;
        QStringList versStrings;
        foreach(Ver * v, graph->vers()){
            versStrings<<Ver2JSON(v);
        }

        props<< m_infoWriter->GraphInfo2JSON( graph->info())
                <<"\"vers\":[\n  "+versStrings .join(",\n  ")+"]";
        stream<<"{"+props.join(",\n ")+"}";
    }
}




QString JSONGraphWriter::Edge2JSON(Edge * edge){
    QStringList props;
    props << m_infoWriter->EdgeInfo2JSON( edge->info())
             << Property2JSON("nextVer", edge->v1()->info()->id());
    return "{"+props.join(",\n  ")+"}";
}

QString JSONGraphWriter::Ver2JSON(Ver * ver){
    QStringList props;
    props<<m_infoWriter->VerInfo2JSON(ver->info());
    QStringList edgesStrings;
    foreach(Edge * e, ver->parentGraph()->edges()){
        if(e->v0() == ver ){
            edgesStrings<<Edge2JSON( e );
        }
    }
    props<<"\"edges\":[\n   "+edgesStrings.join(",\n   ")+"]";
    props<<Property2JSON("x", QString::number(ver->pos().x()));
    props<<Property2JSON("y", QString::number(ver->pos().y()));
    return "{"+props.join(",\n   ")+"}";
}

QStringList SimpleJSONInfoWriter::VerInfo2JSON(VerInfo *info)
{
    QStringList props;
    SimpleVerInfo * simpleInfo = (SimpleVerInfo *)info;
    props<<Property2JSON("id", simpleInfo->id())
            <<Property2JSON("actions", simpleInfo->actions())
            <<Property2JSON("text", simpleInfo->text())
            <<Property2JSON("type", Type2Str(simpleInfo->verType()));
    return props;
}

QStringList SimpleJSONInfoWriter::EdgeInfo2JSON(EdgeInfo *info)
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

QStringList SimpleJSONInfoWriter::GraphInfo2JSON(GraphInfo *info)
{
    QStringList props;
    SimpleGraphInfo * simpleInfo = (SimpleGraphInfo *)info;
    props<<Property2JSON("actions", simpleInfo->actions())
            <<Property2JSON("name", simpleInfo->name())
            <<Property2JSON("description", simpleInfo->description());
    return props;
}
