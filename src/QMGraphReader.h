#ifndef QMGRAPHREADER_H
#define QMGRAPHREADER_H
#include "AbstractGraphReader.h"
#include "BaseGraph.h"
#include "QMGraph.h"
#include "QMReader.h"
#include "QlGraph.h"
#include "QMScriptToBsConverter.h"

class AbstractQMInfoReader{
public:
    virtual BaseVerInfo * ReadVerInfo( QMLocation * location ) = 0;
    virtual BaseEdgeInfo * ReadEdgeInfo( QMPath * path ) = 0;
    virtual BaseGraphInfo * ReadGraphInfo( QMGraph * graph ) = 0;
};

enum eQMGraphReaderType {
    QMGraphReaderType = 2
};

class QMGraphReader : public AbstractGraphReader
{
//private:
//    qint32 m_paramsCount;
private:
    BaseGraph * m_graph;
    QMGraph * m_qmGraph;
    AbstractQMInfoReader * m_infoReader;
public:
//    void setParamsCount( qint32 value){ m_paramsCount = value; }
//    qint32 paramsCount( void ) const { return m_paramsCount; }
    void setReader( AbstractQMInfoReader * infoReader ){
        m_infoReader = infoReader;
    }

    QMGraphReader( AbstractQMInfoReader * infoReader = 0 );
    virtual BaseGraph * ReadGraph(const QString & filename, BaseGraph * graph = 0);
    void ReadVers( );
    BaseVer * ReadVer( QMLocation * location);
    void ReadEdges();
    BaseEdge * ReadEdge( QMPath * path );
    void ReadGraphInfo();
    BaseVer * FindVer( QMLocation *location);
    virtual int type() const { return QMGraphReaderType; }
};

#endif // QMGRAPHREADER_H
