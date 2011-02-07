#ifndef JSONGRAPHWRITER_H
#define JSONGRAPHWRITER_H

#include "Graph.h"
#include "AbstractGraphWriter.h"
#include <QtCore>
#include <QtScript>
//#include <parser.h>

class JSONGraphWriter : public AbstractGraphWriter
{
public:
    virtual void WriteGraph( Graph * graph, const QString & filename );
    QString Edge2JSON(Edge * edge);
    QString Ver2JSON(Ver * ver);
};

#endif // JSONGRAPHWRITER_H
