#ifndef ABSTRACTGRAPHREADER_H
#define ABSTRACTGRAPHREADER_H

#include "BaseGraph.h"
#include <QtCore>
#include <QtScript>

class AbstractGraphReader;

class ReaderError  {
public:

    ReaderError( QString message = QString() ):
        m_message(message){}

//    ~ParseError() throw() {}

    QString message() const {
        return m_message;
    }

    void setMessage( QString message ){
        m_message = message;
    }
private:
    QString m_message;
};


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
