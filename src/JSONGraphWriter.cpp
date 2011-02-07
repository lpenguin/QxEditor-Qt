#include "JSONGraphWriter.h"

QString Type2Str( LocationType type ){
        if( type == start	)
                return "start";
        if( type == odinary	)
                return "odinary";
        if( type == fail	)
                return "fail";
        if( type == win	)
                return "win";
        return "odinary";
}

QString Property2JSON(QString name, QString value){
    return "\""+name+"\""+":\""+value.replace("\"","\\\"").replace("\n", "\\n").replace("\t","\\t")+"\"";
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

        props<<Property2JSON("actions", graph->script())
                <<Property2JSON("name", graph->name())
                <<Property2JSON("description", graph->description())
                <<"\"vers\":[\n  "+versStrings .join(",\n  ")+"]";
        stream<<"{"+props.join(",\n ")+"}";
    }
}




QString JSONGraphWriter::Edge2JSON(Edge * edge){
    QStringList props;
    EdgeInfo info = edge->info();
    props<<Property2JSON("id", info.id)
            <<Property2JSON("actions", info.actions)
            <<Property2JSON("text", info.text)
            <<Property2JSON("conditions", info.conditions)
            <<Property2JSON("question", info.question)
            <<Property2JSON("nextVer", edge->v1()->info().id);
    return "{"+props.join(",\n    ")+"}";
}

QString JSONGraphWriter::Ver2JSON(Ver * ver){
    QStringList props;
    VerInfo info = ver->info();
    props<<Property2JSON("id", info.id)
            <<Property2JSON("actions", info.actions)
            <<Property2JSON("text", info.text)
            <<Property2JSON("type", Type2Str(info.type))
            <<Property2JSON("x", QString::number(ver->pos().x()))
            <<Property2JSON("y", QString::number(ver->pos().y()));
    QStringList edgesStrings;
    foreach(Edge * e, ver->parentGraph()->edges()){
        if(e->v0() == ver ){
            edgesStrings<<Edge2JSON( e );
        }
    }
    props<<"\"edges\":[\n   "+edgesStrings.join(",\n   ")+"]";
    return "{"+props.join(",\n   ")+"}";
}
