#include "JSONGraphReader.h"

VerInfo::VerType Str2Type( QString type ){
        if( type == "start"	)
                return SimpleVerInfo::start;
        if( type == "odinary"	)
                return SimpleVerInfo::odinary;
        if( type == "fail"	)
                return SimpleVerInfo::fail;
        if( type == "win"	)
                return SimpleVerInfo::win;
        return SimpleVerInfo::odinary;
}

JSONGraphReader::JSONGraphReader(AbstractJSONInfoReader * infoReader):
   m_infoReader( infoReader )
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
        GraphInfo * gi;
        graph->setInfo( m_infoReader->ReadGraphInfo( sc ));
//        }catch(ReaderError & e){
//            qDebug()<<e.message();
//            return 0;
//        }
        //graph->setInfo( gi );
//        qDebug()<<gi->name();
//        graph->setInfo( gi );
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
//        try{
            Ver * ver = LoadVer(it.value());
            graph->AddVer(ver);
//        }catch(ReaderError & e){
//            qDebug()<<e.message();
//        }
    }
}

Ver * JSONGraphReader::LoadVer( QScriptValue value){
    VerInfo * info = m_infoReader->ReadVerInfo( value );
    QPoint point( value.property("x").toInteger(), value.property("y").toInteger());
    return new Ver(info, point);
}

Edge * JSONGraphReader::LoadEdge( Graph * graph, QScriptValue value, Ver * ver){
    Ver * v1 = graph->FindVer( value.property("nextVer").toString());
    EdgeInfo * info = m_infoReader->ReadEdgeInfo( value );
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
//            try{
                Edge * edge = LoadEdge( graph, edgeIt.value(),v);
                graph->AddEdge(edge);
//            }catch(ReaderError & e){
//                qDebug()<<e.message();
//            }
        }
    }
}

VerInfo * SimpleJSONInfoReader::ReadVerInfo(QScriptValue value)
{
    SimpleVerInfo * info = new SimpleVerInfo();

    info->setActions( value.property("actions").toString() );
    info->setId( value.property("id").toString() );
    info->setText( value.property("text").toString() );
    info->setVerType( Str2Type( value.property("type").toString() ) );

//    QPoint point( value.property("x").toInteger(), value.property("y").toInteger());
    return info;
}

EdgeInfo * SimpleJSONInfoReader::ReadEdgeInfo(QScriptValue value)
{
    SimpleEdgeInfo * info = new SimpleEdgeInfo();
    info->setActions( value.property("actions").toString() );
    info->setConditions( value.property("conditions").toString() );
    info->setId( value.property("id").toString() );
    info->setQuestion( value.property("question").toString() );
    info->setText( value.property("text").toString() );
    return info;
}

GraphInfo * SimpleJSONInfoReader::ReadGraphInfo(QScriptValue value)
{
    SimpleGraphInfo * info = new SimpleGraphInfo(value.property("name").toString(),
                                                 value.property("description").toString(),
                                                 value.property("actions").toString()
                                                 );
    return info;
}

void JSONGraphReader::setInfoReader(AbstractJSONInfoReader *infoReader)
{
    m_infoReader = infoReader;
}
