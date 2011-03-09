#ifndef QUESTLOGIC_H
#define QUESTLOGIC_H


#include "BlockScript.h"
class QlObject;
class QlConstraint;
class QlTrigger;
class QlShowVariable;
class QlLocationTexts;

class QlObject{
public:
    void set( BsObjectP & obj, BsObjectP value );
};

class QlConstraint : public QlObject{
private:
    BsVariable * m_var;
    BsExpression * m_min;
    BsExpression * m_max;
public:
    void setVar(BsVariable * var){ }
};

#endif // QUESTLOGIC_H
