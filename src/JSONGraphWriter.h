#ifndef JSONGRAPHWRITER_H
#define JSONGRAPHWRITER_H

#include "BaseGraph.h"
#include "AbstractGraphWriter.h"
#include <QtCore>
#include <QtScript>
#include "SimpleGraph.h"
//#include <parser.h>

QString Type2Str( SimpleVerInfo::VerType type );
QString Property2JSON(QString name, QString value);

class AbstractJSONInfoWriter{
public:
    virtual QStringList VerInfo2JSON( BaseVerInfo * info ) = 0;
    virtual QStringList EdgeInfo2JSON( BaseEdgeInfo * info ) = 0;
    virtual QStringList GraphInfo2JSON( BaseGraphInfo * info ) = 0;
};

class SimpleJSONInfoWriter : public AbstractJSONInfoWriter{
public:
    virtual QStringList VerInfo2JSON( BaseVerInfo * info );
    virtual QStringList EdgeInfo2JSON( BaseEdgeInfo * info );
    virtual QStringList GraphInfo2JSON( BaseGraphInfo * info );
};

class JSONGraphWriter : public AbstractGraphWriter
{
private:
    AbstractJSONInfoWriter * m_infoWriter;
public:
    JSONGraphWriter( AbstractJSONInfoWriter * infoWriter = 0 ):
        m_infoWriter( infoWriter ){}
    void setInfoWriter( AbstractJSONInfoWriter * infoWriter ){
        m_infoWriter = infoWriter;
    }

    AbstractJSONInfoWriter * infoWriter()const{
        return m_infoWriter;
    }

    virtual void WriteGraph( BaseGraph * graph, const QString & filename );
    QString Edge2JSON(BaseEdge * edge);
    QString Ver2JSON(BaseVer * ver);
};

#endif // JSONGRAPHWRITER_H
