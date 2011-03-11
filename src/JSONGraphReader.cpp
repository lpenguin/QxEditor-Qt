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

JSONGraphReader::JSONGraphReader(AbstractInfoReader * infoReader):
    AbstractGraphReader( infoReader )
{
}

BaseGraph * JSONGraphReader::ReadGraph(const QString & filename, BaseGraph * graph){
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
            graph = new BaseGraph;

        LoadVers(graph, sc);
        LoadEdges(graph, sc);
        graph->setInfo( m_infoReader->ReadGraphInfo( sc ));
        file.close();

        return graph;
    }


    return 0;
}

void JSONGraphReader::LoadVers(  BaseGraph * graph, QScriptValue value ){
    QScriptValueIterator it(value.property("vers"));

    while (it.hasNext()) {
        it.next();
        if( ! it.value().isObject() )
            continue;
        Ver * ver = LoadVer(it.value());
        graph->AddVer(ver);
    }
}

BaseVer * JSONGraphReader::LoadVer( QScriptValue value){
    BaseInfo * info = m_infoReader->ReadVerInfo( value );
    QPoint point( value.property("x").toInteger(), value.property("y").toInteger());
    return new BaseVer(info, point);
}

BaseEdge * JSONGraphReader::LoadEdge( BaseGraph * graph, QScriptValue value, Ver * ver){
    BaseVer * v1 = graph->FindVer( value.property("nextVer").toString());
    BaseInfo * info = m_infoReader->ReadEdgeInfo( value );
    return new BaseEdge(info, ver, v1);
}

void JSONGraphReader::LoadEdges( BaseGraph * graph, QScriptValue value ){
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

BaseInfo * SimpleJSONInfoReader::ReadVerInfo(QScriptValue value)
{
    SimpleVerInfo * info = new SimpleVerInfo();

    info->setActions( value.property("actions").toString() );
    info->setId( value.property("id").toString() );
    info->setText( value.property("text").toString() );
    info->setType( Str2Type( value.property("type").toString() ) );

    QPoint point( value.property("x").toInteger(), value.property("y").toInteger());
    return info;
}

BaseInfo * SimpleJSONInfoReader::ReadEdgeInfo(QScriptValue value)
{
    SimpleEdgeInfo * info = new SimpleEdgeInfo();
    info->setActions( value.property("actions").toString() );
    info->setConditions( value.property("conditions").toString() );
    info->setId( value.property("id").toString() );
    info->setQuestion( value.property("question").toString() );
    info->setText( value.property("text").toString() );
    return info;
}

BaseInfo * SimpleJSONInfoReader::ReadGraphInfo(QScriptValue value)
{
    SimpleGraphInfo * info = new SimpleGraphInfo(value.property("name").toString(),
                                                 value.property("description"),
                                                 value.property("actions").toString()
                                                 );
    return info;
}
