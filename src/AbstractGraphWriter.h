#ifndef ABSTRACTGRAPHWRITER_H
#define ABSTRACTGRAPHWRITER_H

#include "Graph.h"
#include <QtCore>
class AbstractGraphWriter
{
public:
    virtual void WriteGraph( Graph * graph, const QString & filename ) = 0;
};

#endif // ABSTRACTGRAPHWRITER_H
