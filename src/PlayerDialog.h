#ifndef PLAYERDIALOG_H
#define PLAYERDIALOG_H

#include <QDialog>
#include <QDeclarativeContext>
#include <QtNetwork/QNetworkAccessManager>
#include <QWebFrame>

#include <QDir>
#include <QtCore>
namespace Ui {
    class PlayerDialog;
}

class PlayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerDialog(QWidget *parent = 0);
    ~PlayerDialog();
    void Play( const QString & path, const QString & playerPath );

private:
    Ui::PlayerDialog *ui;
    QObject * jsObject;
public slots:
    void populateJavaScriptWindowObject();
};

#endif // PLAYERDIALOG_H
