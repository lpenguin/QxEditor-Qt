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
    BaseVerInfo * ReadVerInfo( QMLocation * location );
    virtual BaseEdgeInfo * ReadEdgeInfo( QMPath * path );
    virtual BaseGraphInfo * ReadGraphInfo( QMGraph * graph );
private:
    QlLocationTexts * ConvertLocationTexts(QMLocation * location);

    QlParametrList ConvertParametrs(QMParametrList params );
    QlParametr * ConvertParametr( QMParametr * parametr);
    BlockScript * ConvertActions(QMActionList actions);
    BsExpression * ConvertConditions(QMConditionList conditions);
    BaseVerInfo::VerType ConvertLocationType(QMLocation::QMLocationType type);
};

#endif // QLQMINFOREADER_H
