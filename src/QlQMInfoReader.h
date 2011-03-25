#ifndef QLQMINFOREADER_H
#define QLQMINFOREADER_H

#include "AbstractGraphReader.h"
#include "BlockScript.h"
#include "QuestLogic.h"
#include "QlGraph.h"
#include "QMScriptToBsConverter.h"
#include "QMGraphReader.h"

class QlQMInfoReader : public AbstractQMInfoReader{
private:
    QMScriptToBsConverter m_qmToBs;
public:
    VerInfo * ReadVerInfo( QMLocation * location );
    virtual EdgeInfo * ReadEdgeInfo( QMPath * path );
    virtual GraphInfo * ReadGraphInfo( QMGraph * graph );
private:
    QlLocationTexts * ConvertLocationTexts(QMLocation * location);

    QlPathStatementList ConvertPathStatements( QMPath * path );
    QlParametrList ConvertParametrs(QMParametrList params );
    QlParametr * ConvertParametr( QMParametr * parametr);
    BsScript * ConvertActions(QMActionList actions);
    BsExpression * ConvertConditions(QMConditionList conditions);
    VerInfo::VerType ConvertLocationType(QMLocation::QMLocationType type);
//    QString pathId( QMPath * path );
};

#endif // QLQMINFOREADER_H
