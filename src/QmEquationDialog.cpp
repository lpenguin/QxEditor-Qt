#include "QmEquationDialog.h"
#include "ui_QmEquationDialog.h"

QmEquationDialog::QmEquationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QmEquationDialog)
{
    ui->setupUi(this);

}

QmEquationDialog::~QmEquationDialog()
{
    delete ui;
}

void QmEquationDialog::parse()
{
    QString input = ui->inputEdit->toPlainText();
    try{
        BsExpression * res = m_qmConverter.parseExpression( input );
        ui->resultEdit->setPlainText( m_bsConvertter.ConvertBsExpression( res ));
    }catch( Error & e ){
        ui->resultEdit->setPlainText( e.message() );
    }

}
