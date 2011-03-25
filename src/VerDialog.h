#ifndef VERDIALOG_H
#define VERDIALOG_H

#include <QDialog>
#include "BaseGraph.h"
#include "BaseWidgets.h"

namespace Ui {
    class VerDialog;
}

class VerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VerDialog(QWidget *parent = 0);
    ~VerDialog();
    int ShowVer(Ver * ver);
    void setVerWidget( BaseVerWidget * verWidget );
private:
    Ui::VerDialog *ui;
    Ver * m_ver;
public slots:
    void buttonboxAccepted();
};

#endif // VERDIALOG_H
