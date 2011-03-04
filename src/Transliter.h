#ifndef TRANSLITER_H
#define TRANSLITER_H
#include <QMap>

class TransliterInstance;

class Transliter{
private:
    static TransliterInstance transliterInstance;
public:
    static QString Translate(QString source);
};

class TransliterInstance
{
private:
    QMap<QString, QString> words;
public:
    TransliterInstance();
};

#endif // TRANSLITER_H
