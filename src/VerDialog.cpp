#include "VerDialog.h"
#include "ui_VerDialog.h"

VerDialog::VerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerDialog)
{
    ui->setupUi(this);
    connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(buttonboxAccepted()));
}

VerDialog::~VerDialog()
{
    delete ui;
}

int VerDialog::ShowVer(BaseVer * ver)
{
    m_ver = ver;
    ui->verWidget->ShowVer( ver );
    return exec();
}

void VerDialog::buttonboxAccepted()
{
    ui->verWidget->WriteVer( m_ver );
}

void VerDialog::setVerWidget(BaseVerWidget *verWidget)
{
    delete ui->verWidget;
    ui->verWidget = verWidget;
//    ui->
}
