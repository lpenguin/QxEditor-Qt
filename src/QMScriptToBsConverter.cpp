#include "QMScriptToBsConverter.h"

QMScriptToBsConverter::QMScriptToBsConverter(QMParametrList qmGlobals):
    m_qmGlobals( qmGlobals )
{
    setQmGlobals( qmGlobals );
}

BsScript * QMScriptToBsConverter::ConvertQMActions(QMActionList qmActions)
{
    BsStatementList instructions;
    foreach( QMAction * action, qmActions ){
        instructions.append( ConvertQMAction( action ));
    }
    return new BsScript( instructions );
}

BsVariable * QMScriptToBsConverter::ConvertQMParametrToVariable(QMParametr * qmParametr)
{
    qmParametr->name = Transliter::Translate( qmParametr->name );
    qmParametr->name = qmParametr->name.replace("(", "lb").
            replace(")", "rb")
            .replace(" ","_")
            .replace(".","dt")
            .replace("*","ml")
            .replace("+","pl")
            .replace("/","dv")
            .replace("\"","qt");

    if( QRegExp("^[A-Za-z_]\\w*$").indexIn(qmParametr->name) == -1 ){
        QString newName = QInputDialog::getText(0,
                              QString("Choose correct variable name"),
                              QString("Current variable name: %1 is not correct, choose correct one").arg(qmParametr->name),
                              QLineEdit::Normal,
                              QString(qmParametr->name));
        if( newName.isEmpty() )
            qmParametr->name = QString("p")+QString::number(qmParametr->parNumber);
        else
            qmParametr->name = newName;
    }

    return new BsVariable(  qmParametr->name );
}

BsStatementList QMScriptToBsConverter::ConvertQMAction(QMAction * qmAction)
{
    BsVariable * var = m_varMap[qmAction->param];
    qDebug()<<QString("Variable %1 (%2)").arg(qmAction->param->name).arg(qmAction->param->parNumber) ;
    if( !var )
        throw( Error(QString("Variable %1 (%2) not found").arg(qmAction->param->name).arg(qmAction->param->parNumber)) );
    BsAction *  action = new BsAction( var );
    BsStatementList list;
    switch(qmAction->type){
    case QMAction::Mov:
        action->setActionType( BsObject::Mov );
        action->setValue(new BsValue( QString::number(qmAction->addNumber )));
        list<<action;
        break;
    case QMAction::Number:
        if( !qmAction->addNumber )
            break;
        else if( qmAction->addNumber > 0 )
            action->setActionType( BsObject::Addition);
        else
            action->setActionType( BsObject::Substraction);
        action->setValue(new BsValue( QString::number( abs( qmAction->addNumber ) )));
        list<<action;
        break;
    case QMAction::Equation:
        action->setActionType(BsObject::Mov);
        action->setValue(ConvertQMEquation(qmAction->equation));
        list<<action;
        break;
     case QMAction::Procent:
        action->setActionType(BsObject::Mov);
        QString str = QString::number(qmAction->addNumber);
        BsValue * val = new BsValue(str);/*{
            BsFunction * f = new BsFunction;
            f->setName( QString("prc") );
            f->setArguments( BsExpressionList() << var << val );
            action->setValue( f );
        }*/
        action->setValue(new BsFunction( QString("prc"), BsExpressionList() << var << val));
        list<<action;
        break;
    }

    if( qmAction->show == QMAction::Show){
        BsAction * action = new BsAction( var );
        action->setActionType(BsObject::Show);
        action->setValue( new BsNull );
        list<<action;
    }else if(qmAction->show == QMAction::Hide){
        BsAction *  action = new BsAction( var );
        action->setActionType(BsObject::Hide);
        action->setValue( new BsNull );
        list<<action;
    }


    return list;
}

BsExpression * QMScriptToBsConverter::ConvertQMEquation(QString equation)
{
    QMapIterator<QMParametr *, BsVariable *> i(m_varMap);
    QString parName;
    while(i.hasNext()){
        i.next();
        parName = QString("p") + QString::number( i.key()->parNumber+1);
        equation = equation.replace( QRegExp(parName+"(?=\\D)"),
                                    i.value()->name());
    }
    return m_eqConverter.parseExpression( equation );
}

void QMScriptToBsConverter::setQmGlobals(QMParametrList qmGlobals)
{
    BsVariable * var;
    m_qmGlobals = qmGlobals;
    foreach( QMParametr * par, qmGlobals){
        var = ConvertQMParametrToVariable( par );
        m_globals.append( var);
        m_varMap.insert(par, var);
    }

}

BsConditionList QMScriptToBsConverter::ConvertQMCondition(QMCondition *qmCondition)
{
    BsConditionList result;
    BsVariable * var = m_varMap[qmCondition->param];
    if( qmCondition->maxDiap != qmCondition->param->max ||
            qmCondition->minDiap != qmCondition->param->min){
        BsCondition * cond = new BsCondition( BsCondition::In,
                                             BsExpressionList() <<
                                                var <<
                                                new BsRange(
                                                 new BsValue( QString::number(qmCondition->minDiap)),
                                                 new BsValue( QString::number(qmCondition->maxDiap)),
                                                 false)
                                                 );
        result<<cond;
    }
    if( qmCondition->equals.count() ){
        BsExpressionList list;
        list<<var;
        foreach( int v, qmCondition->equals){
            list<<new BsValue( QString::number( v ));
        }

        BsCondition * cond = new BsCondition( BsCondition::In, list);
        if( ! qmCondition->isEquals ){
            cond = new BsCondition(BsCondition::Not, BsExpressionList() << cond);
        }
        result<<cond;
    }
    if( qmCondition->kraten.count() ){
        BsExpressionList list;
        list<<var;
        foreach( int v, qmCondition->kraten){
            list<<new BsValue( QString::number( v ));
        }

        BsCondition * cond = new BsCondition( BsCondition::Multiple, list);
        if( ! qmCondition->isKraten ){
            cond = new BsCondition(BsCondition::Not, BsExpressionList() << cond);
        }
        result<<cond;
    }

    return result;

}

BsExpression * QMScriptToBsConverter::ConvertQMConditions(QMConditionList qmConditions)
{
    BsConditionList result;
    foreach(QMCondition * cond, qmConditions){
        result<<ConvertQMCondition(cond);
    }
    if( result.count() > 1 )
        return new BsCondition( BsCondition::And, BsCondition::ConditionsToExpressions(result));
    else if (result.count() == 1 )
        return result.takeFirst();
    else
        return new BsNull;
}

BsExpression * QMScriptToBsConverter::ConvertQMLocaigalCondition(QString condition)
{
    return ConvertQMEquation( condition );//new BsCondition( BsCondition::UserString, BsExpressionList() << new BsUserString( condition ));
}

QlParametr *  QMScriptToBsConverter::ConvertQMParametr(QMParametr *qmParametr)
{
    BsVariable * var = m_varMap[ qmParametr ];
    QlParamStatementList list;
    list<<new QlConstraint( var, new BsValue( QString::number(qmParametr->min)), new BsValue( QString::number(qmParametr->max)))
        <<new QlShowVariable( var, ConvertQMRanges( qmParametr->ranges),  ConvertQMRangesTexts(qmParametr->ranges, var->name()),
                                   qmParametr->showOnZero )
        <<new QlIntConstraint(var);


    if( qmParametr->type != QMParametr::Odinary){
        QlBoundTrigger * trig = new QlBoundTrigger();
        trig->setText( qmParametr->critText);
        trig->setVar( var );
        if( qmParametr->critValue == QMParametr::Max ){
            trig->setBoundType(QlBoundTrigger::Max);
            trig->setValue( new BsValue(QString::number(qmParametr->max)));
        }else{
            trig->setBoundType(QlBoundTrigger::Min);
            trig->setValue( new BsValue(QString::number(qmParametr->min)));
        }
        list << trig ;
    }
    BsExpression * startValue = ConvertQMEquation( qmParametr->start );
    return new QlParametr( var, startValue, list );
}

BsRangeList QMScriptToBsConverter::ConvertQMRanges(QMParametrRangeList ranges)
{
    BsRangeList list;
    foreach( QMParametrRange range, ranges){
        list<<new BsRange( new BsValue(QString::number( range.min)), new BsValue(QString::number( range.max)), false);
    }
    return list;
}

QStringList QMScriptToBsConverter::ConvertQMRangesTexts(QMParametrRangeList ranges, const QString & varName)
{
    QStringList list;
    QString text;
    foreach( QMParametrRange range, ranges){
        text = range.text.replace("<>", QString("{%1}").arg(varName));
        text = ConvertQMEquationsInText( text );
        list<<text;
    }
    return list;
}

QString QMScriptToBsConverter::ConvertQMParametrType(QMParametr::QMParametrType type)
{
    switch(type){
    case QMParametr::Fail:
    return "fail";
    case QMParametr::Success:
    return "win";
    case QMParametr::Odinary:
    return "odinary";
    case QMParametr::Death:
    return "fail";
    default:
        return "[ERROR]";
    }

}

QString QMScriptToBsConverter::ConvertQMEquationsInText(const QString &text)
{
    QString eq = text;
    qint32 index;
    qint32 from = 0, nextBracket;
    while((index = eq.indexOf("{", from)) != -1 ){
        nextBracket = FindBracketEnd(eq, index, QChar('{'), QChar('}'));
        QString part = eq.mid(index+1, nextBracket - index - 1);
        BsExpression * exp = ConvertQMEquation(part);
        part = m_bsConverter.ConvertBsExpression(exp);
        eq.replace(index + 1, nextBracket - index - 1, part);
        from = index + part.length() + 2;
    }
    return eq;
}
