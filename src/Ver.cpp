#include "Ver.h"

//LocationType Ver::Str2Type( QString type ){
	//if( type == "start"	)
		//return LocationType::start;
	//if( type == "odinary"	)
		//return LocationType::odinary;
	//if( type == "fail"	)
		//return LocationType::fail;
	//if( type == "win"	)
		//return LocationType::win;
	//return LocationType::odinary;
//}

Ver::Ver(VerInfo info, QPointF pos, QObject * parent )
	: m_info( info ), m_pos( pos ), QObject( parent )
{
}

Graph * Ver::parentGraph(){
    if( ! parent())
        return 0;
    return qobject_cast<Graph*>(parent());
}

//Ver::Ver(const Ver & ver){
	//this->m_actions = ver.m_actions;
	//this->m_name = ver.m_actions;
	//this->m_actions = ver.m_actions;
	//this->m_actions = ver.m_actions;
//}
