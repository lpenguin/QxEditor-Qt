#ifndef ABSTRACTGRAPHREADER_H
#define ABSTRACTGRAPHREADER_H

#include "Graph.h"
#include <QtCore>
class AbstractGraphReader
{
public:
    AbstractGraphReader();
    virtual Graph * ReadGraph(const QString & filename, Graph * graph = 0) = 0;
};

#endif // ABSTRACTGRAPHREADER_H
