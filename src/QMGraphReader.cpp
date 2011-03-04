#include "QMGraphReader.h"

QMGraphReader::QMGraphReader()
{
}

Graph * QMGraphReader::ReadGraph(const QString & filename, Graph * graph ){
    if( ! graph ) graph = new Graph();
    QMReader reader;
    QMGraph * qmGraph = reader.ReadGraph( filename );
    if( !qmGraph ){
        qDebug()<<QObject::tr("Error in loading graph: %1").arg(reader.errorString());
        return 0;
    }
    QMGraphConverter converter;
    return converter.Convert(qmGraph);
}
