#include "PlayerDialog.h"
#include "ui_PlayerDialog.h"

PlayerDialog::PlayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerDialog)
{
    ui->setupUi(this);

}

PlayerDialog::~PlayerDialog()
{
    delete ui;
}

void PlayerDialog::Play(const QString &path)
{
     ui->declarativeView->setSource( QUrl::fromLocalFile("/home/prian/src/QxEditor-Qt/src/qxplayer/Main.qml"));
     ui->declarativeView->show();
}
