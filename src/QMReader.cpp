#include "QMReader.h"

QMReader::QMReader( qint32 paramsCount )
{
    this->paramsCount = paramsCount;
}

QMGraph * QMReader::ReadGraph(const QString &filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    BinaryReader br(&file);

    QMStringReplaces stringReplaces;
//    QList<QMParametr> params;
//    QList<QMPath> paths;
//    QList<QMLocation> locations;
    try{
        ReadHeader(br);
        m_params = ReadParametrs(br);
        stringReplaces = ReadStringReplaces(br);
        m_locations = ReadLocations(br);
        m_paths = ReadPaths(br);

    }catch(std::exception& e){
        m_errorString = QObject::tr("Error in reading file: %1").arg(e.what());
        return 0;
    }
    file.close();
    return new QMGraph(m_params, m_locations, m_paths, stringReplaces );
}

QMAction * QMReader::ReadActionFromLocaion(BinaryReader &br, qint32 paramNumber)
{
    QMAction * action = new QMAction();
    br.skipRawData(12);
    action->addNumber = br.ReadInt32();
    action->show = IntToQMParamterVisible( br.ReadInt32() );
    action->type = ReadActionType( br );
    br.ReadInt32();
    action->equation = br.ReadString();
    br.skipRawData(14);
    QString ts = br.ReadString();
    if( m_params.count() > paramNumber)
        action->param = m_params[paramNumber];
    else
        throw( QMException(QObject::tr("Parametr with number %1 does not exists").arg(paramNumber)) );

    return action;
}

QMAction::QMParametrActionType QMReader::ReadActionType(BinaryReader &br)
{
    QMAction::QMParametrActionType type;
    br.ReadByte();
    type = QMAction::Number;
    if (br.ReadByte() == 1)
        type = QMAction::Procent;
    if (br.ReadByte() == 1)
        type = QMAction::Mov;
    if (br.ReadByte() == 1)
        type = QMAction::Equation;
    return type;

}

QMAction::QMParamterVisible QMReader::IntToQMParamterVisible(qint32 vis)
{
    switch (vis)
    {
        case 0:
            return QMAction::DontTouch;
        case 1:
            return QMAction::Show;
        case 2:
            return QMAction::Hide;
    }
    return QMAction::DontTouch;
}

QMAction * QMReader::ReadActionFromPath(BinaryReader &br, qint32 paramNumber )
{
    QMAction * action = new QMAction();
    action->addNumber = br.ReadInt32();
    action->show = IntToQMParamterVisible(br.ReadInt32());
    action->type = ReadActionType(br);
    br.ReadInt32();
    action->equation = br.ReadString();
    if( m_params.count() > paramNumber)
        action->param = m_params[paramNumber];
    else
        throw( QMException(QObject::tr("Parametr with number %1 does not exists").arg(paramNumber)));

    return action;
}

QMCondition * QMReader::ReadCondition(BinaryReader &br, qint32 paramNumber)
{
    //TODO: Check kraten and equals reading
    QMCondition * condition = new QMCondition();
    int len = br.ReadInt32();
    condition->isEquals = br.ReadByte() == 1;

    condition->isEquals = condition->isEquals && len != 0;

    for (int i = 0; i < len; i++)
        condition->equals.push_front( br.ReadInt32() );
    len = br.ReadInt32();
    condition->isKraten = br.ReadByte() == 1;
//    condition->kraten = new Int32[len];
    condition->isKraten = condition->isKraten && len != 0;
    for (int i = 0; i < len; i++)
        condition->kraten.push_front( br.ReadInt32() );

    if( m_params.count() > paramNumber)
        condition->param = m_params[paramNumber];
    else
        throw( QMException(QObject::tr("Parametr with number %1 does not exists").arg(paramNumber)) );
    return condition;
}

QMLocation * QMReader::ReadLocation(BinaryReader &br)
{
    QMLocation * location = new QMLocation();
    location->incDay = br.ReadInt32() == 1;
    location->x = br.ReadInt32();
    location->y = br.ReadInt32();

    location->locNumber = br.ReadInt32();
    location->type = ReadLocationType(br);
    QString temp;
    QMAction * tAction;

    for (int i = 0; i < paramsCount; i++)
    {
        tAction = ReadActionFromLocaion( br, i );
        if(tAction->notEmpty())
            location->actions.append(tAction);
        else
            delete tAction;
    }

    for (int i = 0; i < 10; i++)
    {
        br.ReadInt32();
        temp = br.ReadString();
        if (!temp.isEmpty())
            location->texts.append(temp);
    }
    location->selectTextByFormula = br.ReadByte() == 1;
    br.skipRawData(8);
    temp = br.ReadString();
    br.ReadInt32();
    temp = br.ReadString();
    br.skipRawData(4);
    location->textFormula =br.ReadString();
    return location;
}



QMLocation::QMLocationType QMReader::ReadLocationType(BinaryReader &br)
{
    QMLocation::QMLocationType type =  QMLocation::Odinary;
    if (br.ReadByte() == 1)
        type =  QMLocation::Start;
    if (br.ReadByte() == 1)
        type =  QMLocation::Success;
    if (br.ReadByte() == 1)
        type =  QMLocation::Death;
    if (br.ReadByte() == 1)
        type =  QMLocation::Fail;
    if (br.ReadByte() == 1)
        type =  QMLocation::Empty;
    return type;
}

QMPath * QMReader::ReadPath(BinaryReader &br)
{
    QMPath * path = new QMPath();
    path->priority = br.ReadReal();
    path->incDay = br.ReadInt32() == 1;
    path->pathNumber = br.ReadInt32();
    qint32 ownerLocNumber = br.ReadInt32();
    qint32 nextLocNumber = br.ReadInt32();

    if( m_locations.count() > ownerLocNumber )
        path->ownerLoc = m_locations[ownerLocNumber];
    else
        throw QMException(QObject::tr("Location with number %1 doesnot exists").arg(ownerLocNumber));

    if( m_locations.count() > nextLocNumber )
        path->nextLoc = m_locations[nextLocNumber];
    else
        throw QMException(QObject::tr("Location with number %1 doesnot exists").arg(nextLocNumber));

    br.ReadByte();
    path->alwaysShow = br.ReadByte() == 1;
    path->prohodimost = br.ReadInt32();
    path->showOrder = br.ReadInt32();
    qint32 maxDiap, minDiap;
    QMCondition * q;
    QString temp;
    for (int i = 0; i < paramsCount; i++){
        br.ReadInt32();
        minDiap = br.ReadInt32();
        maxDiap = br.ReadInt32();
        QMAction * tmpAction = ReadActionFromPath( br, i );
        if( tmpAction->notEmpty())
            path->actions.append( tmpAction );
        else
            delete tmpAction;
        q = ReadCondition( br, i );
        q->maxDiap = maxDiap;
        q->minDiap = minDiap;
        if( q->notEmpty() )
            path->conditions.append(q);
        else
            delete q;
        br.skipRawData(4);
        temp = br.ReadString();
    }
    br.ReadInt32();
    path->logicalCondition = br.ReadString();
    br.ReadInt32();
    path->question = br.ReadString();
    br.ReadInt32();
    path->text = br.ReadString();
    return path;
}

QMParametrRange QMReader::ReadParametrRange(BinaryReader &br)
{
    QMParametrRange range;
    range.min = br.ReadInt32();
    range.max = br.ReadInt32();
    br.ReadInt32();
    range.text = br.ReadString();
    return range;
}

QMParametr::QMCritValue QMReader::IntToQMCritValue(int critVal)
{
    if (critVal == 0)
        return QMParametr::Max;
    return QMParametr::Min;
}

QMParametr::QMParametrType QMReader::IntToQMParametrType(int type)
{
    switch (type)
    {
    case 0:
        return QMParametr::Odinary;
    case 1:
        return QMParametr::Fail;
    case 2:
        return QMParametr::Success;
    case 3:
        return QMParametr::Death;
    default:
        return QMParametr::Odinary;
    }
}

QMParametr * QMReader::ReadParametr(BinaryReader &br)
{
    QMParametr * parametr = new QMParametr();
    parametr->min = br.ReadInt32();
//    br.ReadInt32();
//    br.ReadInt32();
//    parametr->start = br.ReadInt32();
//    parametr->max = br.ReadInt32();
    parametr->max = br.ReadInt32();
    br.ReadInt32();

    parametr->type = IntToQMParametrType(br.ReadInt32());//IntToQMParametrType(br.ReadByte());
    br.ReadInt32();
    parametr->showOnZero = br.ReadBool();
    parametr->critValue = IntToQMCritValue(br.ReadByte());
    parametr->active = br.ReadBool();
    parametr->numStrings = br.ReadInt32();
    parametr->isMoney = br.ReadBool();
    br.ReadInt32();
    parametr->name = br.ReadString();
//    name = Transliter.Translate(name).Replace(' ','_');
    int len;
    for (int i = 0; i < parametr->numStrings; i++)
        parametr->ranges.append(ReadParametrRange(br));
    br.ReadInt32();
    len = br.ReadInt32();
    if (len == 0)
    {
        parametr->critText = QString("");

    }
    else
        parametr->critText = br.ReadChars(len);
    br.ReadInt32();
    parametr->start = br.ReadString();
    return parametr;
}

QMStringReplaces QMReader::ReadStringReplaces(BinaryReader & br)
{
    QMStringReplaces stringReplaces;
    try{
        br.ReadInt32();
        stringReplaces.toStar = br.ReadString();
        br.skipRawData(56);
        stringReplaces.toPlanet = br.ReadString();
        br.ReadInt32();
        stringReplaces.date = br.ReadString();
        br.ReadInt32();
        stringReplaces.money = br.ReadString();
        br.ReadInt32();
        stringReplaces.fromPlanet = br.ReadString();
        br.ReadInt32();
        stringReplaces.fromStar = br.ReadString();
        br.ReadInt32();
        stringReplaces.ranger = br.ReadString();

        m_locCount = br.ReadInt32();
        m_pathCount = br.ReadInt32();

        br.ReadInt32();
        stringReplaces.congString = br.ReadString();
        br.ReadInt32();
        stringReplaces.missionString = br.ReadString();
    }
    catch (std::exception&  e){
        throw( QMException(QObject::tr("Error in reading string replaces: %1").arg(e.what())));
    }
    return stringReplaces;
}

QMParametrList QMReader::ReadParametrs(BinaryReader & br)
{
    QMParametrList params;
    int i;
    try{
        br.skipRawData(55);
        for ( i = 0; i < paramsCount; i++)
        {
//            QMParametr * par = ;
////                par.parNumber = i;
            params.append(ReadParametr(br));
        }
    }
    catch (std::exception&  e)
    {
        throw( QMException(QObject::tr("Error in reading parametr (%2): %1").arg(e.what()).arg(i)));
    }
    return params;
}

QMLocationList QMReader::ReadLocations(BinaryReader & br)
{
    QMLocationList locations;
    int i;
    try{
        br.skipRawData(8);
        for (i = 0; i < m_locCount; i++)
        {
//            QMLocation loc = ;
            //ProcessActions(loc);
            locations.append(ReadLocation(br));
        }
    }
    catch (std::exception&  e)
    {
        throw( QMException(QObject::tr("Error in reading location (%1): %2").arg(i).arg(e.what())));
    }
    return locations;
}

QMPathList QMReader::ReadPaths(BinaryReader & br)
{
    QMPathList paths;
    int i;
    try
    {
        for ( i = 0; i < m_pathCount; i++)
        {
//            QMPath path = ReadPath(br);
           // ProcessActions(path);
            //ProcessPathConditions(path);
            paths.append( ReadPath(br));
        }
    }
    catch (std::exception& e)
    {
        throw( QMException(QObject::tr("Error in reading path (%1): %2").arg(i).arg(e.what())));
    }
    return paths;
}

void QMReader::ReadHeader(BinaryReader & br)
{
    try{
        br.skipRawData(37);
        qint32 xGridSize = br.ReadInt32();//10(51) - vbig,15(34) - big,22(23) - medium,30(17) - small
        qint32 yGridSize = br.ReadInt32();//8(89-44) - vbig,12(59-88) -big,18(39-58) - medium,24(29-43) - small

    }catch(std::exception& e){
       throw( QMException(QObject::tr("Error in reading header of qm file: %1").arg(e.what())) );
    }
}
