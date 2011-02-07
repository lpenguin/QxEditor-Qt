#include "Graph.h"

Graph::Graph( QObject * object ):QObject( object ){

}

//void Graph::Load(QXmlStreamReader & xml){
//	Clean();

//    xml.readNextStartElement();
//        //xml.readNext();
//	LoadMain(xml);
//	xml.device()->reset();
//	xml.setDevice(xml.device());
//	LoadEdges(xml);
//}

//Edge * Graph::LoadEdge(QXmlStreamReader & xml, Ver * v0)
//{
//	Q_ASSERT(xml.isStartElement() && xml.name() == "path");
//	EdgeInfo info;
//	//QString id = xml.attributes().value("id");
//	info.id = xml.attributes().value("id").toString();
//	Ver * v1 =  FindVer(xml.attributes().value("loc_id").toString());
//	while (!xml.atEnd()) {
//         xml.readNext();
//		 qDebug()<<xml.name();
//         if (xml.isEndElement())
//             break;

//         if (xml.isStartElement()) {
//   			if( xml.name() == "actions" )
//   				info.actions = xml.readElementText();
//   			if( xml.name() == "conditions" || xml.name() == "cond")
//   				info.conditions = xml.readElementText();
//   			if( xml.name() == "question" )
//   			   	info.question = xml.readElementText();
//   			if( xml.name() == "text" )
//   			   	info.text = xml.readElementText();
//         }
//     }
//     if( xml.hasError()){
//     	qDebug()<<"error in load edge: "<<xml.errorString();
//     }
//     return new Edge(info, v0, v1, this);
//}


//Ver * Graph::LoadVer(QXmlStreamReader & xml)
//{
//	Q_ASSERT(xml.isStartElement() && xml.name() == "loc");
//	VerInfo info;
//	//QString id = xml.attributes().value("id");
//	info.id = xml.attributes().value("id").toString();
//	info.type = Str2Type(xml.attributes().value("type").toString());
	
//	QPointF pos( xml.attributes().value("x").toString().toFloat(),
//				xml.attributes().value("y").toString().toFloat() );
	
//	while (!xml.atEnd()) {
//         xml.readNext();

//         if (xml.isEndElement() && xml.name() == "loc")
//             break;

//         if (xml.isStartElement()) {
//   			if( xml.name() == "actions" )
//   				info.actions = xml.readElementText();
//   			if( xml.name() == "text" )
//   				info.text = xml.readElementText();
//         }
//     }
//     if( xml.hasError()){
//     	qDebug()<<"error in load ver: "<<xml.errorString();
//     }
//     return new Ver(info, pos, this);
//}


Ver * Graph::FindVer(QString id)
{
	Ver * v;
	foreach(v, m_vers){
		if( v->info().id == id )
			return v;
	}
 	return 0;
}

QString Graph::GetNewVerId(  ){
    QString prefix = "L";
    QString intString;
    int maxId = 0;
    int id;

    bool ok;
    foreach(Ver * ver, m_vers){
        intString = ver->info().id;
        intString.replace(QRegExp("^"+prefix),"");
        id = intString.toInt( &ok );
        if( ok && maxId < id){
            maxId = id;
        }
    }

    return prefix+QString::number(++maxId);
}

QString Graph::GetNewEdgeId(  ){
    QString prefix = "P";
    QString intString;
    int maxId = 0;
    int id;

    bool ok;
    foreach(Edge * edge, m_edges){
        intString = edge->info().id;
        intString.replace(QRegExp("^"+prefix),"");
        id = intString.toInt( &ok );
        if( ok && maxId < id){
            maxId = id;
        }
    }
    return prefix+QString::number(++maxId);
}

//LocationType Str2Type( QString type ){
//	if( type == "start"	)
//		return start;
//	if( type == "odinary"	)
//		return odinary;
//	if( type == "fail"	)
//		return fail;
//	if( type == "win"	)
//		return win;
//	return odinary;
//}



Graph::~Graph()
{
	qDebug()<<"graph desturctor";
}


//void Graph::LoadMain(QXmlStreamReader & xml)
//{
//	while (!xml.atEnd()) {
//         if (xml.isStartElement()) {
//   			if( xml.name() == "loc" ){
//   				m_vers.append( LoadVer( xml ) );
//  			}
//  			if( xml.name() == "script" ){
//  				m_script += xml.readElementText() + "\n";
//  			}
   				
//        }
//        xml.readNext();
//        }
//     if( xml.hasError()){
//     	qDebug()<<"error in load main: "<<xml.errorString();
//     }
//}


//void Graph::LoadEdges(QXmlStreamReader & xml)
//{
// 	QList<Ver *>::iterator i = m_vers.begin();
//    //xml.readNextStartElement();
//	while (!xml.atEnd()) {

//         if (xml.isEndElement() && xml.name() == "loc"){
//         	i++;
         			
//        }
//             //i++;

//         if (xml.isStartElement()) {
//   			if( xml.name() == "path" ){
//   				m_edges.append( LoadEdge( xml, *i ) );
//  			}
//         }
//         xml.readNext();
//     }
//     if( xml.hasError()){
//     	qDebug()<<"error in load edges: "<<xml.errorString();
//     }
//}



void Graph::AddVer(Ver * ver)
{
	ver->setParent(this);
	m_vers.append( ver );
}


void Graph::AddEdge(Edge * edge)
{
	qDebug()<<"Add edge";
	edge->setParent(this);
	m_edges.append( edge );
}


void Graph::Clean()
{
	qDebug()<<"Graph::Clean";
	qDebug()<<"Graph:: Deleting vers";
	while (!m_vers.isEmpty())
		delete m_vers.takeFirst();
	qDebug()<<"Graph:: Deleting edges";
	while (!m_edges.isEmpty())
		delete m_edges.takeFirst();
	qDebug()<<"Graph:: deleted all";
}

void Graph::RemoveVer(Ver * ver)
{
	Edge * e;
	foreach( e, m_edges ){
		if( e->Have( ver ) ){
			m_edges.removeOne( e );
			delete e;
		}
	}
	m_vers.removeOne( ver );
	delete ver;

//	return;
//	foreach( e, deletedEdges ){
//
//		m_edges.removeOne( e );
//		delete e;
//	}
//
}

void Graph::RemoveEdge(Edge * edge)
{
	m_edges.removeOne( edge );
	delete edge;
}
