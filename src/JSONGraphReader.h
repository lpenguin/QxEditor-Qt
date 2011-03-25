#ifndef JSONGRAPHREADER_H
#define JSONGRAPHREADER_H

#include "AbstractGraphReader.h"
#include "BaseGraph.h"
#include "SimpleGraph.h"

#include <QtCore>
#include <QtScript>
#include <QMessageBox>

VerInfo::VerType Str2Type( QString type );

enum eJSONGraphReaderType {
    JSONGraphReaderType = 1
};

class AbstractJSONInfoReader{
public:
    virtual VerInfo * ReadVerInfo( QScriptValue value ) = 0;
    virtual EdgeInfo * ReadEdgeInfo( QScriptValue value ) = 0;
    virtual GraphInfo * ReadGraphInfo( QScriptValue value ) = 0;
};

class SimpleJSONInfoReader : public AbstractJSONInfoReader{
public:
    VerInfo * ReadVerInfo( QScriptValue value );
    EdgeInfo * ReadEdgeInfo(  QScriptValue value );
    GraphInfo * ReadGraphInfo( QScriptValue value );
};

class JSONGraphReader : public AbstractGraphReader
{
private:
    AbstractJSONInfoReader * m_infoReader;
public:
    JSONGraphReader( AbstractJSONInfoReader * infoReader = 0);
    virtual Graph * ReadGraph(const QString & filename, Graph * graph = 0);
    virtual int type() const { return JSONGraphReaderType; };
    void setInfoReader( AbstractJSONInfoReader * infoReader );
private:
    Ver * LoadVer( QScriptValue value );
    void LoadVers( Graph * graph, QScriptValue value );
    void LoadEdges( Graph * graph, QScriptValue value );
    Edge * LoadEdge( Graph * graph, QScriptValue value, Ver * ver);
};

#endif // JSONGRAPHREADER_H
