#include "QMGraph.h"
namespace QMScript{

QMGraph::QMGraph(QMParametrList params, QMLocationList locations, QMPathList paths , QMStringReplaces stringReplaces)
    :m_params( params ), m_locations( locations ), m_paths(paths), m_stringReplaces( stringReplaces )
{

}

}
