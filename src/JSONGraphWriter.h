#ifndef JSONGRAPHWRITER_H
#define JSONGRAPHWRITER_H

#include "BaseGraph.h"
#include "AbstractGraphWriter.h"
#include <QtCore>
#include <QtScript>
#include "SimpleGraph.h"
//#include <parser.h>

class AbstractJSONInfoWriter{
public:
    virtual QStringList VerInfo2JSON( BaseInfo * info ) = 0;
    virtual QStringList EdgeInfo2JSON( BaseInfo * info ) = 0;
    virtual QStringList GraphInfo2JSON( BaseInfo * info ) = 0;
};

class SimpleJSONIngoWriter : public AbstractJSONInfoWriter{
public:
    virtual QStringList VerInfo2JSON( BaseInfo * info );
    virtual QStringList EdgeInfo2JSON( BaseInfo * info );
    virtual QStringList GraphInfo2JSON( BaseInfo * info );
};

class JSONGraphWriter : public AbstractGraphWriter
{
private:
    AbstractJSONInfoWriter * m_infoWriter;
public:
    JSONGraphWriter( AbstractJSONInfoWriter * infoWriter):
        m_infoWriter( infoWriter ){}
    void setInfoWriter( AbstractJSONInfoWriter * infoWriter ){
        m_infoWriter = infoWriter;
    }

    AbstractJSONInfoWriter * infoWriter()const{
        return m_infoWriter;
    }

    virtual void WriteGraph( BaseGraph * graph, const QString & filename );
    QString Edge2JSON(BaseEdge * edge);
    QString Ver2JSON(BaseEdge * ver);
};

#endif // JSONGRAPHWRITER_H
