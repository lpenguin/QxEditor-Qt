#include "QuestLogic.h"

void QlParametr::setList( QlParamStatementList & list, QlParamStatementList value ){
    list.clear();
    foreach( BsRange * obj, value ){
        add( list, obj);
    }
}
void QlParametr::add( QlParamStatementList & list, QlParamStatement * value){
    list.append( value );
    if( value && isLocal((BsObjectP) value ))
        value->setParent( this );
}
