#include "QlEdgeWidget.h"
#include "ui_QlEdgeWidget.h"

QlEdgeWidget::QlEdgeWidget(QWidget *parent) :
    BaseEdgeWidget(parent),
    ui(new Ui::QlEdgeWidget)
{
    ui->setupUi(this);
    m_converter = new BsToESMAScriptConverter;
}

QlEdgeWidget::~QlEdgeWidget()
{
    delete ui;
    delete m_converter;
}

void QlEdgeWidget::ShowEdge(BaseEdge *edge)
{
    QlEdgeInfo * info;
    if( info = qobject_cast<QlEdgeInfo *>(edge->info())){
        ui->actionsEdit->setPlainText( m_converter->ConvertBlockSript(info->actions()));
        ui->conditionsEdit->setPlainText( m_converter->ConvertBsConditionStatement(info->expression()));
        ui->textEdit->setPlainText( info->text());
        ui->questionEdit->setPlainText( info->question());
        ui->initEdit->setPlainText( m_converter->ConvertQlPathStatementList( info->pathStatements() ) );
//        ui->edgeIdEdit->setText(info->id());
    }
}

void QlEdgeWidget::WriteEdge(BaseEdge *edge)
{
    QlEdgeInfo * info;
    if( info = qobject_cast<QlEdgeInfo *>(edge->info())){
//        info->setActions( ui->actionsEdit->toPlainText() );
//        info->setConditions( ui->conditionsEdit->toPlainText() );
//        info->setId( ui->edgeIdEdit->text() );
//        info->setText( ui->textEdit->toPlainText() );
//        info->setQuestion( ui->questionEdit->toPlainText() );
    }
}
