#ifndef QMGRAPHCONVERTER_H
#define QMGRAPHCONVERTER_H

#include "Graph.h"
#include "QMGraph.h"
#include "QMGraphReader.h"
#include <QtCore>

class QMGraphConverter
{
private:
    Graph * m_graph;
    QMGraph * m_qmGraph;
public:
    QMGraphConverter();
    Graph * Convert( QMGraph * qmGraph);
    void ConvertLocations(  QMLocationList locations );
    void ConvertPaths(  QMPathList paths );

    Ver * ConvertLocation( QMLocation * location );
    Edge * ConvertPath( QMPath * path, Ver * v0, Ver * v1 );

    QString ConvertAction( QMAction * action );
    QString ConvertCondition( QMCondition * condition );
    QString ConvertActions( QMActionList actions );
    QString ConvertConditions( QMConditionList conditions );
    QString ConvertParams( QMParametrList params );

    LocationType ConvertLocationType(QMLocation::QMLocationType);

    Ver * FindVer( QMLocation * location);

};

#endif // QMGRAPHCONVERTER_H
