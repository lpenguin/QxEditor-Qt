#include "QlVerWidget.h"
#include "ui_QlVerWidget.h"

QlVerWidget::QlVerWidget(QWidget *parent) :
    BaseVerWidget(parent),
    ui(new Ui::QlVerWidget)
{
    ui->setupUi(this);
    m_bsToEsConverter = new BsToESMAScriptConverter;
    m_esToBsConverter = new ECMAScriptToBsConverter;
}

QlVerWidget::~QlVerWidget()
{
    delete ui;
    delete m_bsToEsConverter;
    delete m_esToBsConverter;
}

void QlVerWidget::ShowVer(Ver *ver)
{
    QlVerInfo * info;
    if( info = qobject_cast<QlVerInfo *>(ver->info())){
        ui->actionsEdit->setPlainText( m_bsToEsConverter->ConvertBlockSript(info->actions()));
        ui->textEdit->setPlainText(info->text());
        ui->initEdit->setPlainText( m_bsToEsConverter->ConvertQlLocationStatementList( info->locationStatements() ) );
        ui->verId->setText( info->id());
    }
}

void QlVerWidget::WriteVer(Ver *ver)
{
    QlVerInfo * info;
    if( info = qobject_cast<QlVerInfo *>(ver->info())){
        info->setActions( m_esToBsConverter->ConvertScript(ui->actionsEdit->toPlainText().split("\n")));
        info->setText( ui->textEdit->toPlainText() );
        info->setLocationStatements( m_esToBsConverter->ConvertLocationStatements( ui->initEdit->toPlainText().split("\n") ));
        info->setId( ui->verId->text() );
    }
}
