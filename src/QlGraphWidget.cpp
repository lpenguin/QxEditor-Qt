#include "QlGraphWidget.h"
#include "ui_QlGraphWidget.h"

QlGraphWidget::QlGraphWidget(QWidget *parent) :
    BaseGraphWidget(parent),
    ui(new Ui::QlGraphWidget)
{
    ui->setupUi(this);
}

QlGraphWidget::~QlGraphWidget()
{
    delete ui;
}

void QlGraphWidget::ShowGraph(Graph *graph)
{
    QlGraphInfo * info;
    if( info = qobject_cast<QlGraphInfo *>(graph->info())){
        ui->actionsEdit->setPlainText( m_bsToEsConverter.ConvertQlParametrList( info->parametrList() ));
    }
}

void QlGraphWidget::WriteGraph(Graph *graph)
{
    QlGraphInfo * info;
    qDebug()<<ui->actionsEdit->toPlainText();
    if( info = qobject_cast<QlGraphInfo *>(graph->info())){
        QlParametrList paramList = m_esToBsConverter.ConvertParametrList(   ui->actionsEdit->toPlainText().split("\n" ) );
        info->setParametrList( paramList );
    }
}
