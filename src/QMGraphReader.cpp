#include "QMGraphReader.h"

QMGraphReader::QMGraphReader()
{
}

BaseGraph * QMGraphReader::ReadGraph(const QString & filename, BaseGraph * graph ){
    if( ! graph ) graph = new BaseGraph();
    QMReader reader;
    QMGraph * qmGraph = reader.ReadGraph( filename );
    if( !qmGraph ){
        qDebug()<<QObject::tr("Error in loading graph: %1").arg(reader.errorString());
        return 0;
    }
    QMGraphConverter converter;
    return converter.Convert(qmGraph);
}
