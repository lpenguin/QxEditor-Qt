#ifndef TRANSLITER_H
#define TRANSLITER_H
#include <QMap>
#include <QString>
class TransliterInstance;
extern QMap<QString, QString> words;

class Transliter{
private:
    public:
//    static TransliterInstance transliterInstance;

    static QString Translate(QString source);
};

//class TransliterInstance
//{
//private:

//public:
//        QMap<QString, QString> words;
//    TransliterInstance();
//};


void initTransliter();

#endif // TRANSLITER_H
