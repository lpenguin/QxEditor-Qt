#ifndef QLQMINFOREADER_H
#define QLQMINFOREADER_H

#include "AbstractGraphReader.h"
#include "BlockScript.h"
#include "QuestLogic.h"
#include "QlGraph.h"
#include "QMScriptToBsConverter.h"

class QlQMInfoReader : public AbstractQMInfoReader{
private:
    QMScriptToBsConverter * m_qmToBs;
public:
    BaseInfo * ReadVerInfo( QMLocation * location );
    virtual BaseInfo * ReadEdgeInfo( QMPath * path );
    virtual BaseInfo * ReadGraphInfo( QMGraph * graph );
private:
    QlLocationTexts * ConvertLocationTexts(QMLocation * location);

    QlParametrList ConvertParametrs(QMParametrList params );
    QlParametr * ConvertParametr( QMParametr * parametr);
    BlockScript * ConvertActions(QMActionList actions);
    BsExpression * ConvertConditions(QMConditionList conditions);
    QMLocation::QMLocationType ConvertLocationType(QMLocation::QMLocationType type);
};

#endif // QLQMINFOREADER_H
