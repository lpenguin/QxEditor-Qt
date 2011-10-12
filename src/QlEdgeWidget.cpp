#include "QlEdgeWidget.h"
#include "ui_QlEdgeWidget.h"

QlEdgeWidget::QlEdgeWidget(QWidget *parent) :
    BaseEdgeWidget(parent),
    ui(new Ui::QlEdgeWidget)
{
    ui->setupUi(this);
    m_bsToEsConverter = new BsToESMAScriptConverter;
    m_esToBsConverter = new ECMAScriptToBsConverter;

}
QlEdgeWidget::~QlEdgeWidget()
{
    delete ui;
    delete m_bsToEsConverter;
    delete m_esToBsConverter;
}

void QlEdgeWidget::ShowEdge(Edge *edge)
{
    QlEdgeInfo * info;
    if( info = qobject_cast<QlEdgeInfo *>(edge->info())){
        ui->actionsEdit->setPlainText( m_bsToEsConverter->ConvertBlockSript(info->actions()));
        ui->conditionsEdit->setPlainText( m_bsToEsConverter->ConvertBsConditionStatement(info->expression()));
        ui->textEdit->setPlainText( info->text());
        ui->questionEdit->setPlainText( info->question());
        ui->initEdit->setPlainText( m_bsToEsConverter->ConvertQlPathStatementList( info->pathStatements() ) );
        ui->edgeId->setText( info->id() );
//        ui->edgeIdEdit->setText(info->id());
    }
}

void QlEdgeWidget::WriteEdge(Edge *edge)
{
    QlEdgeInfo * info;
    if( info = qobject_cast<QlEdgeInfo *>(edge->info())){
        info->setActions( m_esToBsConverter->ConvertScript(ui->actionsEdit->toPlainText().split("\n")));
        info->setExpression( m_esToBsConverter->ConvertExpressionStatement(ui->conditionsEdit->toPlainText()));
        info->setText( ui->textEdit->toPlainText() );
        info->setQuestion( ui->questionEdit->toPlainText() );
        info->setPathStatements( m_esToBsConverter->ConvertPathStatementList(  ui->initEdit->toPlainText().split("\n") ));
        info->setId( ui->edgeId->text() );
    }
}
