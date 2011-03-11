#ifndef JSONGRAPHWRITER_H
#define JSONGRAPHWRITER_H

#include "BaseGraph.h"
#include "AbstractGraphWriter.h"
#include <QtCore>
#include <QtScript>
//#include <parser.h>

class JSONGraphWriter : public AbstractGraphWriter
{
public:
    JSONGraphWriter( AbstractInfoWriter * infoWriter):
        AbstractGraphWriter( infoWriter ){}
    virtual void WriteGraph( BaseGraph * graph, const QString & filename );
    QString Edge2JSON(BaseEdge * edge);
    QString Ver2JSON(BaseEdge * ver);
};

#endif // JSONGRAPHWRITER_H
