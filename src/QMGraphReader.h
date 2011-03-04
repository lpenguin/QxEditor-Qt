#ifndef QMGRAPHREADER_H
#define QMGRAPHREADER_H
#include "AbstractGraphReader.h"
#include "Graph.h"
#include "QMGraph.h"
#include "QMReader.h"
#include "QMGraphConverter.h"

enum eQMGraphReaderType {
    QMGraphReaderType = 2
};

class QMGraphReader : public AbstractGraphReader
{
//private:
//    qint32 m_paramsCount;
public:
//    void setParamsCount( qint32 value){ m_paramsCount = value; }
//    qint32 paramsCount( void ) const { return m_paramsCount; }
    QMGraphReader( );
    virtual Graph * ReadGraph(const QString & filename, Graph * graph = 0);
    virtual int type() const { return QMGraphReaderType; }
};

#endif // QMGRAPHREADER_H
