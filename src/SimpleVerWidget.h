#ifndef SIMPLEVERWIDGET_H
#define SIMPLEVERWIDGET_H

#include <QWidget>
#include "BaseGraph.h"
#include "BaseWidgets.h"
#include "SimpleGraph.h"

namespace Ui {
    class SimpleVerWidget;
}

class SimpleVerWidget : public BaseVerWidget
{
    Q_OBJECT

public:
    explicit SimpleVerWidget(QWidget *parent = 0);
    ~SimpleVerWidget();
    void ShowVer(Ver *ver);
    void WriteVer(Ver *ver);

private:
    Ui::SimpleVerWidget *ui;
private:
    VerInfo::VerType radio2type ( void );
    void type2radio( VerInfo::VerType  type);
};

#endif // SIMPLEVERWIDGET_H
