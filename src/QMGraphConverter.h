#ifndef QMGRAPHCONVERTER_H
#define QMGRAPHCONVERTER_H

#include <QtCore>

#include "BaseGraph.h"
#include "QMGraph.h"
#include "QMGraphReader.h"

#include "BsToESMAScriptConverter.h"
#include "QMScriptToBsConverter.h"

class QMGraphConverter
{
private:
    BaseGraph * m_graph;
    QMGraph * m_qmGraph;
    QMScriptToBsConverter m_qmToBs;
    BsToESMAScriptConverter m_BsToESMA;
public:
    QMGraphConverter();
    BaseGraph * Convert( QMGraph * qmGraph);
    void ConvertLocations(  QMLocationList locations );
    void ConvertPaths(  QMPathList paths );

    Ver * ConvertLocation( QMLocation * location );
    Edge * ConvertPath( QMPath * path, Ver * v0, Ver * v1 );

    QString ConvertAction( QMAction * action );
    QString ConvertCondition( QMCondition * condition );
    QString ConvertActions( QMActionList actions );
    QString ConvertConditions( QMConditionList conditions );
    QString ConvertParams( QMParametrList params );
    QString ConvertPathConditions( QMPath * path );
    LocationType ConvertLocationType(QMLocation::QMLocationType);

    Ver * FindVer( QMLocation * location);

};

#endif // QMGRAPHCONVERTER_H
