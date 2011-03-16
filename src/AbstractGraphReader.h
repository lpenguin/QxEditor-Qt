#ifndef ABSTRACTGRAPHREADER_H
#define ABSTRACTGRAPHREADER_H

#include "BaseGraph.h"
#include <QtCore>
#include <QtScript>

class AbstractGraphReader;


class AbstractGraphReader
{
//private:
//    AbstractQMInfoReader * m_infoReader;
public:
    AbstractGraphReader( /*AbstractQMInfoReader * infoReader = 0*/)/*:
        m_infoReader(infoReader)*/{}
    virtual BaseGraph * ReadGraph(const QString & filename, BaseGraph * graph = 0) = 0;
    virtual int type() const = 0;
//    void setInfoReader( AbstractQMInfoReader * infoReader ){ m_infoReader = infoReader; }
//    AbstractQMInfoReader * infoReader( void ) const { return m_infoReader; }
};





#endif // ABSTRACTGRAPHREADER_H
