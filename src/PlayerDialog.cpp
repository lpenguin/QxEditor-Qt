#include "PlayerDialog.h"
#include "ui_PlayerDialog.h"

PlayerDialog::PlayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerDialog)
{
    ui->setupUi(this);
    connect( ui->webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
              this, SLOT(populateJavaScriptWindowObject()) );
    jsObject = new QObject();
}

PlayerDialog::~PlayerDialog()
{
    delete ui;
    delete jsObject;
}

void PlayerDialog::Play(const QString &path, const QString & playerPath)
{
//     ui->declarativeView->rootContext()->setContextProperty( "networkManager", &manager );
     //ui->declarativeView->setSource( QUrl::fromLocalFile(playerPath));
     //QObject * o = (QObject*)ui->declarativeView->rootObject();
     //o->setProperty("questPath", path);
    //QString indexPath = QString("%1%2index.html").arg(playerPath).arg(QDir::separator());
    //QString questInfoPath = QString("%1%2quest.info").arg(playerPath).arg(QDir::separator());

    //QFile file(questInfoPath);
    //if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    //         return;

    //QTextStream out(&file);
    //out << QString("{ \"path\" : \"%1\" }").arg(QUrl::fromLocalFile(path).toString());
    //file.close();
    jsObject->setProperty("questPath", QUrl::fromLocalFile(path).toString());
    QUrl url = QUrl::fromLocalFile(playerPath);//+QUrl::fromLocalFile(path).toString());
    ui->webView->load(url);


    qDebug()<<url.toString();
    ui->webView->show();
     //ui->declarativeView->rootContext()
     //ui->declarativeView->show();
    exec();
}

void PlayerDialog::populateJavaScriptWindowObject()
{
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("jsObject", jsObject);
}
