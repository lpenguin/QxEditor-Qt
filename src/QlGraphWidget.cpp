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

void QlGraphWidget::ShowGraph(BaseGraph *graph)
{
    QlGraphInfo * info;
    if( info = qobject_cast<QlGraphInfo *>(graph->info())){
        ui->actionsEdit->setPlainText( m_converter.ConvertQlParametrList( info->parametrList() ));
//        ui->verIdEdit->setText( info->id() );
//        ui->textEdit->setPlainText(info->locationTexts()->firstText());
//        type2radio( info->verType());
    }
}

void QlGraphWidget::WriteGraph(BaseGraph *graph)
{
}
