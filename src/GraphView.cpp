#include "GraphView.h"
#define VER_SIZE 20
#define GRID_SIZE 150
//
GraphView::GraphView(   QWidget * parent   )
        : QGraphicsView( parent), m_verSize( VER_SIZE ), m_gridSize( GRID_SIZE )
{

	setScene( new QGraphicsScene() );
	setMouseTracking( true );
	setRenderHint( QPainter::Antialiasing );
	setSceneRect( this->rect());
	markedVer = 0;
	movingVer = 0;
        m_graph = new BaseGraph(this);
}
//

void GraphView::LoadGraph( BaseGraph * graph)
{
    foreach(BaseVer * v, graph->vers() ){
        AppendVer( v, v->pos() );
    }
	
    VerItem * v1;
    VerItem * v0;
    qDebug()<<"Loading";
    foreach(BaseEdge * e, graph->edges() ){
            v1 = FindVer( e->v1() );
            v0 = FindVer( e->v0() );
//            qDebug()<<v0->ver()->info()->id()<<" "<<v1->ver()->info()->id();
            AppendEdge( e, v0->pos(), v1->pos());
    }
}


void GraphView::CleanGraph()
{
	qDebug()<<"GraphView::CleanGraph";
	qDebug()<<"GraphView:: Deleting vers";
	VerItem * ver;
	EdgeItem* edge;
	while (!m_vers.isEmpty()){
		ver = m_vers.takeFirst();
		scene()->removeItem( ver );
		delete ver;
	}
		
	qDebug()<<"GraphView:: Deleting edges";
	while (!m_edges.isEmpty()){
		edge = m_edges.takeFirst();
		scene()->removeItem( edge );
		delete edge;
	}
		
	//qDebug()<<"GraphView:: Cleaning graph";
	//m_graph->Clean();
	qDebug()<<"GraphView:: deleted all";
}


GraphView::~GraphView()
{
	qDebug()<<"graphView desturctor";
	//CleanGraph();
	//qDebug()<<"GraphView:: deleting graph";
	//delete m_graph;
	//qDebug()<<"GraphView:: deleted graph";
}



VerItem * GraphView::FindVer(BaseVer * v)
{
	VerItem * t;
	foreach(t, m_vers){		
		if( t->ver() == v )
			return t;
	}
	return 0;
}


//void GraphView::setGraph(Graph * graph)
//{
//	m_graph = graph;
//	LoadGraph( graph );
//}
void GraphView::mouseMoveEvent ( QMouseEvent * e ){

	if( ! markedVer ){
		QPoint p = e->pos();
		//qDebug()<<p<<mapToScene(p)<<"scene pos";	
		QGraphicsItem * item;
		QList<QGraphicsItem *> its;
		//qDebug()<<"nbew";
		EdgeItem * edge;
		scene()->clearSelection();
		
		
		qreal dist, minDist = 999;	
		QGraphicsItem * minItem = 0;
		foreach(item, items( p )){
				if( item->type() == EdgeType ){
					edge = 	(EdgeItem*)item;
					dist = edge->Distance( edge->mapFromScene( p ) );
					if( minDist > dist )
						minItem = edge;
				}
				if( item->type() == VerType ){
					minItem = item;
					break;
				}
		}
		if( minItem )
			minItem->setSelected(true);
	}else{
		if( movingVer ){
			markedVer->setPos( mapToScene(e->pos()) );
                        markedVer->ver()->setPos( e->pos() );
			EdgeItem * edge;
			foreach( edge, m_edges){				
				if( edge->edge()->v0() == markedVer->ver()){
					edge->setPos(markedVer->pos());
					edge->UpdatePath();
					edge->update();
				}					
				else if( edge->edge()->v1() == markedVer->ver()){
                                        edge->setEndPoint(markedVer->pos());
					edge->UpdatePath();
					edge->update();					
				}
					
			}
		}
			
	}

	QGraphicsView::mouseMoveEvent(e);
}
void GraphView::mousePressEvent ( QMouseEvent * e ){
	
	QGraphicsItem * item = itemAt( e->pos());
	if( item ){
		if( item->type() == VerType ){
			markedVer = (VerItem * )item;
			if( e->modifiers() & Qt::ControlModifier )
				movingVer = true;
			else 
				movingVer = false;
				
		}
	}
	QGraphicsView::mousePressEvent(e);
}
void GraphView::mouseReleaseEvent ( QMouseEvent * e ){
	QGraphicsItem * item = itemAt( e->pos());
	if( item ){
		if( markedVer ) {
			if( ! movingVer ){
				if( item->type() == VerType){
					if( item == markedVer ){//same ver			
						//qDebug()<<"emitted VerClicked: "<<(void*)item<<", "<<e->button();
						emit( VerClicked( (VerItem * )item, e->button() ));
					}else{//differet vers
						qDebug()<<"emitted VersConnected: "<<(void*)markedVer<<", "<<(void*)item<<", "<<e->button();
						emit( VersConnected( markedVer, (VerItem * )item ) );
					}
						
				}
				movingVer = false;
			}
			markedVer = 0;
		}else{
			if( item->type() == EdgeType) {//EdgeType
				qDebug()<<"emitted EdgeClicked: "<<(void*)item<<", "<<e->button();
				emit( EdgeClicked( (EdgeItem * )item, e->button() ) );
			}
		}
	}else{
		if( ! markedVer ){
			qDebug()<<"emitted AreaClicked: "<<e->pos();	
			emit(AreaClicked( e->pos(), e->button()));
		}		
	}

	QGraphicsView::mouseReleaseEvent(e);
}
void GraphView::AppendEdge( BaseEdge * edge, QPointF pos, QPointF endPoint ){
	EdgeItem * edgeItem = new EdgeItem( edge, endPoint, 0, 5);
	edgeItem->setPos( pos );
        edgeItem->setCurvature( Curvature(edgeItem) );
	edgeItem->setZValue( 0 );
        m_edges.append( edgeItem );
	scene()->addItem( edgeItem );
}
void GraphView::AppendVer( BaseVer * ver, QPointF pos ){
	VerItem * verItem = new VerItem( ver,  QSizeF(m_verSize, m_verSize)  );
	verItem->setZValue( 1 );
	scene()->addItem( verItem );
	verItem->setPos( mapToScene(pos.toPoint()) );
	m_vers.append( verItem );
        qDebug()<<"Pos for new verItem: "<<verItem->pos();
}

void GraphView::AddVer( BaseVer * ver, QPointF pos){
        ver->setPos( pos );
        qDebug()<<"Pos for new ver: "<<ver->pos();

        AppendVer( ver, pos );
	m_graph->AddVer( ver );
}
void GraphView::AddEdge( BaseEdge * edge, QPointF pos, QPointF endPoint ){
	AppendEdge( edge, pos, endPoint );
	m_graph->AddEdge( edge );
}
void GraphView::Load( const QString & filename, int type  ){
        CleanGraph();
        m_graph->Clean();
        //m_graph->Load( xml );
        if( type == JSONGraphReaderType ){
            JSONGraphReader reader;
            m_graph = reader.ReadGraph(filename);
        }else if( type == QMGraphReaderType ){
            QMGraphReader reader;
//            if( QMessageBox::question(this, tr("Select params count"), tr("Choose params count"), QString("48"), QString("24") ))
//                reader.setParamsCount(48);
//            else
//                reader.setParamsCount(24);
            reader.setReader( new QlQMInfoReader );
            m_graph = reader.ReadGraph(filename);
        }
        if( m_graph )
            LoadGraph( m_graph );
}
    
void GraphView::Save(const QString & filename){
    JSONGraphWriter writer( new SimpleJSONIngoWriter );
    writer.WriteGraph(m_graph, filename);
}

int GraphView::Curvature(EdgeItem * edge)
{
    EdgeItem * t;
    int maxCurve = 0;
    foreach(t, m_edges){
        if(  edge->edge()->ConnectSame( t->edge())  ){
            if( ! maxCurve )
                maxCurve = 1;
            else{
                if(maxCurve < 0 ){
                    maxCurve--;
                    maxCurve*=-1;
                }else{
                    maxCurve*=-1;
                }
           }

        }
    }

    if (atan2(edge->pos().x() - edge->endPoint().x(), edge->pos().y() - edge->endPoint().y()) >= 0)
                    maxCurve = -maxCurve;

    return maxCurve * 15;
}

void GraphView::RemoveVer(VerItem * ver)
{
	//	CleanGraph();
//	LoadGraph( m_graph );
	EdgeItem * e;
//	QList<EdgeItem * > deletedEdges;
	foreach( e, m_edges ){
		if( e->edge()->Have( ver->ver() ) ){
			m_edges.removeOne(e);
			scene()->removeItem(e);
			delete e;
		}
	}
	m_vers.removeOne( ver );
	m_graph->RemoveVer( ver->ver() );
	delete ver;
//	foreach( e, deletedEdges ){
//		m_edges.removeOne( e );
//		delete e;
//	}
//
//	m_vers.removeOne( ver );
//	scene()->removeItem( ver );
//	m_graph->RemoveVer( ver->ver() );
//	delete ver;
}


void GraphView::RemoveEdge(EdgeItem * edge)
{
	m_edges.removeOne( edge );
	scene()->removeItem( edge );
	m_graph->RemoveEdge( edge->edge() );
	delete edge;
}

