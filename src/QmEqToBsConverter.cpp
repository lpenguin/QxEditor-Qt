#include "QmEqToBsConverter.h"

QmEqToBsConverter::QmEqToBsConverter()
{
}

void QmEqToBsConverter::FillOperations()
{
    m_operations << OperatorPair( Or, (QStringList() << "or") );
//                    << ( And, ( QStringList() << "and" ) )
//                    << ( Comp, ( QStringList() << ">=" << "<=" << "=" << "<>" << "<" << ">" ) )
//                    << ( In, ( QStringList() << "in" ) )
//                    << ( To, ( QStringList() << "to" ) )
//                    << ( Math, ( QStringList() << "+" << "-" << "*" << "/" << "mod" << "div" ) );

}

BlockScript::BsExpression * QmEqToBsConverter::ParseEquation(const QString &equation) throw( ParseError )
{
    foreach( OperatorPair operatorPair, m_operations ){
        QStringList operatorGroup = operatorPair.second;
        QString oper = findOperator( equation, operatorGroup );
        if( !oper.isEmpty() ){
            QStringList slices = splitSmart( equation, oper );
            switch( operatorPair.first ){

            }
        }
    }
}

QString QmEqToBsConverter::findOperator(const QString &expr, const QStringList &operators)
{
    foreach( QString oper, operators ){
        if( FindNextDelim( expr, 0, oper) != -1 )
            return oper;
    }
    return QString("");
}
