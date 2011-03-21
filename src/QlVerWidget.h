#ifndef QLVERWIDGET_H
#define QLVERWIDGET_H

#include <QWidget>
#include "BaseWidgets.h"
#include "BaseGraph.h"
#include "QlGraph.h"
#include "BsToESMAScriptConverter.h"


namespace Ui {
    class QlVerWidget;
}

class QlVerWidget : public BaseVerWidget
{
    Q_OBJECT

public:
    explicit QlVerWidget(QWidget *parent = 0);
    ~QlVerWidget();
    void ShowVer(BaseVer *ver);
    void WriteVer(BaseVer *ver);
private:
    Ui::QlVerWidget *ui;
    BsToESMAScriptConverter * m_converter;
};

#endif // QLVERWIDGET_H
