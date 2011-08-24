#include "QlVerWidget.h"
#include "ui_QlVerWidget.h"

QlVerWidget::QlVerWidget(QWidget *parent) :
    BaseVerWidget(parent),
    ui(new Ui::QlVerWidget)
{
    ui->setupUi(this);
    m_converter = new BsToESMAScriptConverter;
}

QlVerWidget::~QlVerWidget()
{
    delete ui;
    delete m_converter;
}

void QlVerWidget::ShowVer(Ver *ver)
{
    QlVerInfo * info;
    if( info = qobject_cast<QlVerInfo *>(ver->info())){
        ui->actionsEdit->setPlainText( m_converter->ConvertBlockSript(info->actions()));
        ui->textEdit->setPlainText(info->text());
        ui->initEdit->setPlainText( m_converter->ConvertQlLocationStatementList( info->locationStatements() ) );
    }
}

void QlVerWidget::WriteVer(Ver *ver)
{
}
