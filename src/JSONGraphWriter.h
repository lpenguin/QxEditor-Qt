#ifndef JSONGRAPHWRITER_H
#define JSONGRAPHWRITER_H

#include "BaseGraph.h"
#include "AbstractGraphWriter.h"
#include <QtCore>
#include <QtScript>
//#include <parser.h>

class AbstractJSONInfoWriter{
public:
    virtual QString ReadVerInfo( BaseInfo * info ) = 0;
    virtual QString ReadEdgeInfo( BaseInfo * info ) = 0;
    virtual QString ReadGraphInfo( BaseInfo * info ) = 0;
};


class JSONGraphWriter : public AbstractGraphWriter
{
public:
    JSONGraphWriter( AbstractJSONInfoWriter * infoWriter):
        AbstractGraphWriter( infoWriter ){}
    virtual void WriteGraph( BaseGraph * graph, const QString & filename );
    QString Edge2JSON(BaseEdge * edge);
    QString Ver2JSON(BaseEdge * ver);
};

#endif // JSONGRAPHWRITER_H
