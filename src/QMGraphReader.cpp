#include "QMGraphReader.h"

QMGraphReader::QMGraphReader( qint32 paramsCount )
{
    this->paramsCount = paramsCount;
}

Graph * QMGraphReader::ReadGraph(const QString &filename, Graph *graph)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    MyDataStream br(&file);
    qint32 locCount;
    qint32 pathCount;
    int i;
    try{
        try{
            qint32 xGridSize = br.ReadInt32();//10(51) - vbig,15(34) - big,22(23) - medium,30(17) - small
            qint32 yGridSize = br.ReadInt32();//8(89-44) - vbig,12(59-88) -big,18(39-58) - medium,24(29-43) - small

        }catch(std::exception& e){
           m_errorString = QObject::tr("Error in reading header of qm file: %1").arg(e.what());
           return 0;
        }
        try{
            br.skipRawData(57);
            for (i = 0; i < paramsCount; i++)
            {
                QMParametr par = ReadParametr(br);
//                par.parNumber = i;
                m_params.append(par);
            }
        }
        catch (std::exception&  e)
        {
            m_errorString = QObject::tr("Error in reading parametrs: %1").arg(e.what());
            return 0;
        }
        try{
            br.ReadInt32();
            m_stringReplaces.toStar = br.ReadString();
            br.skipRawData(56);
            m_stringReplaces.toPlanet = br.ReadString();
            br.ReadInt32();
            m_stringReplaces.date = br.ReadString();
            br.ReadInt32();
            m_stringReplaces.money = br.ReadString();
            br.ReadInt32();
            m_stringReplaces.fromPlanet = br.ReadString();
            br.ReadInt32();
            m_stringReplaces.fromStar = br.ReadString();
            br.ReadInt32();
            m_stringReplaces.ranger = br.ReadString();
            locCount = br.ReadInt32();
            pathCount = br.ReadInt32();
            br.ReadInt32();
            m_congString = br.ReadString();
            br.ReadInt32();
            m_missionString = br.ReadString();
        }
        catch (std::exception&  e){
            m_errorString = QObject::tr("Error in reading string replaces: %1").arg(e.what());
            return 0;
        }

        try{
            br.skipRawData(8);
            for (i = 0; i < locCount; i++)
            {
                QMLocation loc = ReadLocation(br);
                //ProcessActions(loc);
                m_locations.append(loc);
            }
        }
        catch (std::exception&  e)
        {
            m_errorString = QObject::tr("Error in reading location (%1): %2").arg(i).arg(e.what());
            return 0;
        }

        try
        {
            for (i = 0; i < pathCount; i++)
            {
                QMPath path = ReadPath(br);
               // ProcessActions(path);
                //ProcessPathConditions(path);
                m_paths.append(path);
            }
        }
        catch (std::exception& e)
        {
            m_errorString = QObject::tr("Error in reading path (%1): %2").arg(i).arg(e.what());
            return 0;
        }

    }catch(std::exception& e){
        m_errorString = QObject::tr("Error in reading file: %1").arg(e.what());
        return 0;
    }
    file.close();

}

QMAction QMGraphReader::ReadActionFromLocaion(MyDataStream &br, qint32 paramNumber)
{
    QMAction action;
    br.skipRawData(12);
    action.addNumber = br.ReadInt32();
    action.show = IntToQMParamterVisible( br.ReadInt32() );
    action.type = ReadActionType( br );
    br.ReadInt32();
    action.equation = br.ReadString();
    br.skipRawData(14);
    QString ts = br.ReadString();
    if( m_params.count() > paramNumber)
        action.param = &(m_params[paramNumber]);
    else
        throw( QMException(QObject::tr("Parametr with number %1 does not exists").arg(paramNumber)) );

    return action;
}

QMAction::QMParametrActionType QMGraphReader::ReadActionType(MyDataStream &br)
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

QMAction::QMParamterVisible QMGraphReader::IntToQMParamterVisible(qint32 vis)
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

QMAction QMGraphReader::ReadActionFromPath(MyDataStream &br, qint32 paramNumber )
{
    QMAction action;
    action.addNumber = br.ReadInt32();
    action.show = IntToQMParamterVisible(br.ReadInt32());
    action.type = ReadActionType(br);
    br.ReadInt32();
    action.equation = br.ReadString();
    if( m_params.count() > paramNumber)
        action.param = &(m_params[paramNumber]);
    else
        throw( QMException(QObject::tr("Parametr with number %1 does not exists").arg(paramNumber)));

    return action;
}

QMCondition QMGraphReader::ReadCondition(MyDataStream &br, qint32 paramNumber)
{
    //TODO: Check kraten and equals reading
    QMCondition condition;
    int len = br.ReadInt32();
    condition.isEquals = br.ReadByte() == 1;

    condition.isEquals = condition.isEquals && len != 0;

    for (int i = 0; i < len; i++)
        condition.equals.push_front( br.ReadInt32() );
    len = br.ReadInt32();
    condition.isKraten = br.ReadByte() == 1;
//    condition.kraten = new Int32[len];
    condition.isKraten = condition.isKraten && len != 0;
    for (int i = 0; i < len; i++)
        condition.equals.push_front( br.ReadInt32() );

    if( m_params.count() > paramNumber)
        condition.param = &(m_params[paramNumber]);
    else
        throw( QMException(QObject::tr("Parametr with number %1 does not exists").arg(paramNumber)) );
    return condition;
}

QMLocation QMGraphReader::ReadLocation(MyDataStream &br)
{
    QMLocation location;
    location.incDay = br.ReadInt32() == 1;
    location.x = br.ReadInt32();
    location.y = br.ReadInt32();

    location.locNumber = br.ReadInt32();
    location.type = ReadLocationType(br);
    QString temp;
    QMAction tAction;

    for (int i = 0; i < paramsCount; i++)
    {
        tAction = ReadActionFromLocaion( br, i );
        if(tAction.notEmpty())
            location.actions.append(tAction);
    }

    for (int i = 0; i < 10; i++)
    {
        br.ReadInt32();
        temp = br.ReadString();
        if (!temp.isEmpty())
            location.texts.append(temp);
    }
    location.selectTextByFormula = br.ReadByte() == 1;
    br.skipRawData(8);
    temp = br.ReadString();
    br.ReadInt32();
    temp = br.ReadString();
    br.skipRawData(4);
    location.textFormula =br.ReadString();
    return location;
}



QMLocation::QMLocationType QMGraphReader::ReadLocationType(MyDataStream &br)
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
}

QMPath QMGraphReader::ReadPath(MyDataStream &br)
{
    QMPath path;
    path.priority = br.ReadReal();
    path.incDay = br.ReadInt32() == 1;
    path.pathNumber = br.ReadInt32();
    path.ownerLocNumber = br.ReadInt32();
    path.nextLocNumber = br.ReadInt32();
    br.ReadByte();
    path.alwaysShow = br.ReadByte() == 1;
    path.prohodimost = br.ReadInt32();
    path.showOrder = br.ReadInt32();
    qint32 maxDiap, minDiap;
    QMCondition q;
    QString temp;
    for (int i = 0; i < paramsCount; i++){
        br.ReadInt32();
        minDiap = br.ReadInt32();
        maxDiap = br.ReadInt32();
        QMAction tmpAction = ReadActionFromPath( br, i );
        if( tmpAction.notEmpty())
            path.actions.append( tmpAction );
        q = ReadCondition( br, i );
        q.maxDiap = maxDiap;
        q.minDiap = minDiap;
        if( q.notEmpty() )
            path.conditions.append(q);
        br.skipRawData(4);
        temp = br.ReadString();
    }
    br.ReadInt32();
    path.logicalCondition = br.ReadString();
    br.ReadInt32();
    path.question = br.ReadString();
    br.ReadInt32();
    path.text = br.ReadString();
    return path;
}

QMParametrRange QMGraphReader::ReadParametrRange(MyDataStream &br)
{
    QMParametrRange range;
    range.min = br.ReadInt32();
    range.max = br.ReadInt32();
    br.ReadInt32();
    range.text = br.ReadString();
    return range;
}

QMParametr::QMCritValue QMGraphReader::IntToQMCritValue(int critVal)
{
    if (critVal == 0)
        return QMParametr::Max;
    return QMParametr::Min;
}

QMParametr::QMParametrType QMGraphReader::IntToQMParametrType(int type)
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

QMParametr QMGraphReader::ReadParametr(MyDataStream &br)
{
    QMParametr parametr;
    parametr.min = br.ReadInt32();
    parametr.max = br.ReadInt32();
    br.ReadInt32();

    parametr.type = IntToQMParametrType(br.ReadByte());
    br.ReadInt32();
    parametr.showOnZero = br.ReadBool();
    parametr.critValue = IntToQMCritValue(br.ReadByte());
    parametr.active = br.ReadBool();
    parametr.numStrings = br.ReadInt32();
    parametr.isMoney = br.ReadBool();
    br.ReadInt32();
    parametr.name = br.ReadString();
//    name = Transliter.Translate(name).Replace(' ','_');
    int len;
    for (int i = 0; i < parametr.numStrings; i++)
        parametr.ranges.append(ReadParametrRange(br));
    br.ReadInt32();
    len = br.ReadInt32();
    if (len == 0)
    {
        parametr.critText = QString("");

    }
    else
        parametr.critText = br.ReadChars(len);
    br.ReadInt32();
    parametr.start = br.ReadString(); ;
}
