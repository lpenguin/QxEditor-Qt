#ifndef QLJSONINFOREADER_H
#define QLJSONINFOREADER_H

#include "JSONGraphReader.h"
#include "QlGraph.h"
#include "BaseGraph.h"
#include "ECMAScriptToBsConverter.h"

class QlJSONInfoReader : public AbstractJSONInfoReader
{
public:
    QlJSONInfoReader();
    VerInfo* ReadVerInfo(QScriptValue value);
    EdgeInfo* ReadEdgeInfo(QScriptValue value);
    GraphInfo* ReadGraphInfo(QScriptValue value);
private:
    ECMAScriptToBsConverter m_converter;
    QlLocationTexts * getLocationTexts(QlLocationStatementList statements);
};

#endif // QLJSONINFOREADER_H
