#ifndef ABSTRACTGRAPHREADER_H
#define ABSTRACTGRAPHREADER_H

#include "BaseGraph.h"
#include <QtCore>
#include <QtScript>
//#include "Exception.h"
using namespace Graphs;

class AbstractGraphReader;

//class ReaderError : public Error {
//public:
//    ReaderError( const QString & message):
//        Error( message ){}
//};


class AbstractGraphReader
{
//private:
//    AbstractQMInfoReader * m_infoReader;
public:
    AbstractGraphReader( /*AbstractQMInfoReader * infoReader = 0*/)/*:
        m_infoReader(infoReader)*/{}
    virtual Graph * ReadGraph(const QString & filename, Graph * graph = 0) = 0;
    virtual int type() const = 0;
//    void setInfoReader( AbstractQMInfoReader * infoReader ){ m_infoReader = infoReader; }
//    AbstractQMInfoReader * infoReader( void ) const { return m_infoReader; }
};





#endif // ABSTRACTGRAPHREADER_H
