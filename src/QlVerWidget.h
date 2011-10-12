#ifndef QLVERWIDGET_H
#define QLVERWIDGET_H

#include <QWidget>
#include "BaseWidgets.h"
#include "BaseGraph.h"
#include "QlGraph.h"
#include "BsToESMAScriptConverter.h"
#include "ECMAScriptToBsConverter.h"

namespace Ui {
    class QlVerWidget;
}

class QlVerWidget : public BaseVerWidget
{
    Q_OBJECT

public:
    explicit QlVerWidget(QWidget *parent = 0);
    ~QlVerWidget();
    void ShowVer(Ver *ver);
    void WriteVer(Ver *ver);
private:
    Ui::QlVerWidget *ui;
    BsToESMAScriptConverter * m_bsToEsConverter;
    ECMAScriptToBsConverter * m_esToBsConverter;
};

#endif // QLVERWIDGET_H
