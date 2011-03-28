#ifndef QMEQUATIONDIALOG_H
#define QMEQUATIONDIALOG_H

#include <QDialog>
#include "QmEqToBsConverter.h"
#include "BsToESMAScriptConverter.h"

namespace Ui {
    class QmEquationDialog;
}

class QmEquationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QmEquationDialog(QWidget *parent = 0);
    ~QmEquationDialog();
public slots:
    void parse();
private:
    Ui::QmEquationDialog *ui;
    QmEqToBsConverter m_qmConverter;
    BsToESMAScriptConverter m_bsConvertter;
};

#endif // QMEQUATIONDIALOG_H
