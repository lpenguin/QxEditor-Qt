#include "QuestActionsDialog.h"
#include "ui_QuestActionsDialog.h"

GraphDialog::GraphDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestActionsDialog)
{
    ui->setupUi(this);
    connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(buttonBoxTriggered()));
}

GraphDialog::~GraphDialog()
{
    delete ui;
}
int GraphDialog::ShowGraph(Graph * graph){
    m_graph = graph;
    ui->graphWidget->ShowGraph(graph);
    return exec();
}

void GraphDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void GraphDialog::setGraphWidget(BaseGraphWidget *widget)
{
    if( ui->graphWidget ){
        ui->verticalLayout_2->removeWidget( ui->graphWidget  );
        delete ui->graphWidget;
    }
    ui->graphWidget = widget;
    ui->verticalLayout_2->insertWidget(0, widget );
}

void GraphDialog::buttonBoxTriggered()
{
    ui->graphWidget->WriteGraph( m_graph );
}
