#include "JSONGraphReader.h"

LocationType Str2Type( QString type ){
        if( type == "start"	)
                return start;
        if( type == "odinary"	)
                return odinary;
        if( type == "fail"	)
                return fail;
        if( type == "win"	)
                return win;
        return odinary;
}

JSONGraphReader::JSONGraphReader()
{
}

Graph * JSONGraphReader::ReadGraph(const QString & filename, Graph * graph){
    QFile file( filename );
    if ( file.open(  QIODevice::ReadOnly ) ) {

        QTextStream stream( &file );
        QString str = stream.readAll();
        QScriptValue sc;
        QScriptEngine engine;
        sc = engine.evaluate("("+ str +")");
        if(engine.hasUncaughtException()){
            QMessageBox::warning(0,"Warning", "Warning\nException on line:"+QString(engine.uncaughtExceptionLineNumber())
                                 +"\n"+engine.uncaughtExceptionBacktrace().join("\n"));
            return 0;
        }
        if( !graph )
            graph = new Graph;

        LoadVers(graph, sc);
        LoadEdges(graph, sc);
        graph->setScript( sc.property("actions").toString());
        graph->setName( sc.property("name").toString());
        graph->setDescription( sc.property("description").toString());
        file.close();

        return graph;
    }


    return 0;
}

void JSONGraphReader::LoadVers(  Graph * graph, QScriptValue value ){
    QScriptValueIterator it(value.property("vers"));

    while (it.hasNext()) {
        it.next();
        if( ! it.value().isObject() )
            continue;
        Ver * ver = LoadVer(it.value());
        graph->AddVer(ver);
    }
}

Ver * JSONGraphReader::LoadVer( QScriptValue value){
    VerInfo info;

    info.actions = value.property("actions").toString();
    info.id = value.property("id").toString();
    info.text = value.property("text").toString();
    info.type = Str2Type( value.property("type").toString() );

    QPoint point( value.property("x").toInteger(), value.property("y").toInteger());
    return new Ver(info, point);
}

Edge * JSONGraphReader::LoadEdge( Graph * graph, QScriptValue value, Ver * ver){
    Ver * v1 = graph->FindVer( value.property("nextVer").toString());
    EdgeInfo info;
    info.actions = value.property("actions").toString();
    info.conditions = value.property("conditions").toString();
    info.id = value.property("id").toString();
    info.question = value.property("question").toString();
    info.text = value.property("text").toString();

    return new Edge(info, ver, v1);
}

void JSONGraphReader::LoadEdges( Graph * graph, QScriptValue value ){
    QScriptValueIterator verIt(value.property("vers"));
    QListIterator<Ver*> i(graph->vers());
    while (verIt.hasNext()) {
        verIt.next();
        Ver * v = i.next();
        if( ! verIt.value().isObject() )
            continue;

        QString id = verIt.value().property("id").toString();
        QScriptValueIterator edgeIt(verIt.value().property("edges"));
        while(edgeIt.hasNext()){
            edgeIt.next();
            if( !edgeIt.value().isObject() )
                continue;
            Edge * edge = LoadEdge( graph, edgeIt.value(),v);
            graph->AddEdge(edge);
        }
    }
}
