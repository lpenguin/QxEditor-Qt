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

void QlVerWidget::ShowVer(BaseVer *ver)
{
    QlVerInfo * info;
    if( info = qobject_cast<QlVerInfo *>(ver->info())){
        ui->actionsEdit->setPlainText( m_converter->ConvertBlockSript(info->actions()));
//        ui->verIdEdit->setText( info->id() );
        ui->textEdit->setPlainText(info->firstText());
        ui->initEdit->setPlainText( m_converter->ConvertQlLocationStatementList( info->locationStatements() ) );
//        type2radio( info->verType());
    }
}

void QlVerWidget::WriteVer(BaseVer *ver)
{
}
