#ifndef QMREADER_H
#define QMREADER_H

#include "AbstractGraphReader.h"
#include "BaseGraph.h"
#include <QFile>
#include <QString>
#include "BinaryReader.h"
#include <iostream>
#include "QMGraph.h"
#define TGE_LAST_VERSION 1111111123
using namespace QMScript;
class QMReader
{
public:
    QMReader();
    QMGraph * ReadGraph(const QString & filename);
    QString errorString()const { return m_errorString; } ;
    QMLocation * FindLocation( qint32 number);
private:
    qint32 paramsCount;
    QString m_errorString;
    qint32 m_locCount;
    qint32 m_pathCount;

    QMPathList m_paths;
    QMLocationList m_locations;
    QMParametrList m_params;

    QMAction * ReadActionFromLocaion(  BinaryReader & stream, qint32 paramNumber);
    QMAction * ReadActionFromPath(BinaryReader &br, qint32 paramNumber);
    QMCondition * ReadCondition( BinaryReader &br, qint32 paramNumber);
    QMParametr * ReadParametr( BinaryReader & stream );
    QMPath * ReadPath( BinaryReader & stream );
    QMLocation * ReadLocation( BinaryReader & stream );

    QMAction::QMParametrActionType ReadActionType( BinaryReader & stream );
    QMLocation::QMLocationType ReadLocationType( BinaryReader & stream );
    QMParametrRange ReadParametrRange( BinaryReader & stream );
    QMAction::QMParamterVisible IntToQMParamterVisible(qint32 vis);
    QMParametr::QMCritValue IntToQMCritValue(int critVal);
    QMParametr::QMParametrType IntToQMParametrType(int type);

    void ReadHeader(BinaryReader & stream);
    QMStringReplaces ReadStringReplaces(BinaryReader & stream);
    QMParametrList ReadParametrs(BinaryReader & stream);
    QMLocationList  ReadLocations(BinaryReader & stream);
    QMPathList ReadPaths(BinaryReader & stream);

};

#endif // QMGRAPHREADER_H
