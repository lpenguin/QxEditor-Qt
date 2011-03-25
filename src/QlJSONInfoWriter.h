#ifndef QLJSONINFOWRITER_H
#define QLJSONINFOWRITER_H
#include "JSONGraphWriter.h"
#include "QlGraph.h"
#include "BaseGraph.h"
#include "BsToESMAScriptConverter.h"

class QlJSONInfoWriter : public AbstractJSONInfoWriter
{
public:
    QlJSONInfoWriter();
    QStringList VerInfo2JSON(VerInfo *info);
    QStringList EdgeInfo2JSON(EdgeInfo *info);
    QStringList GraphInfo2JSON(GraphInfo *info);
private:
    BsToESMAScriptConverter m_converter;
};

#endif // QLJSONINFOWRITER_H
