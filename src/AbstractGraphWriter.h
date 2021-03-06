#ifndef ABSTRACTGRAPHWRITER_H
#define ABSTRACTGRAPHWRITER_H

#include "BaseGraph.h"
#include <QtCore>

using namespace Graphs;

class AbstractGraphWriter
{
//private:
//    AbstractInfoWriter * m_infoWriter;
public:
    AbstractGraphWriter(/* AbstractInfoWriter * infoWriter = 0*/)/*:*/
        /*m_infoWriter( infoWriter )*/{}
    virtual void WriteGraph( Graph * graph, const QString & filename ) = 0;
//    void setInfoWriter( AbstractInfoWriter * infoWriter ){ m_infoWriter = infoWriter; }
//    AbstractInfoWriter * infoWriter( void ) const { return m_infoWriter; }
};

#endif // ABSTRACTGRAPHWRITER_H
