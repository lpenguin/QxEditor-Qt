#include "QMGraphReader.h"

QMGraphReader::QMGraphReader(qint32 paramsCount):m_paramsCount(paramsCount)
{
}

Graph * QMGraphReader::ReadGraph(const QString & filename, Graph * graph ){
    if( ! graph ) graph = new Graph();
    QMReader reader( m_paramsCount );
    QMGraph * qmGraph = reader.ReadGraph( filename );
    if( !qmGraph ){
        qDebug()<<QObject::tr("Error in loading graph: %1").arg(reader.errorString());
        return 0;
    }
    QMGraphConverter converter;
    return converter.Convert(qmGraph);
}
