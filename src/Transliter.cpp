#include "Transliter.h"

//TransliterInstance::TransliterInstance()
//{
//    words.insert( QString::fromUtf8( "а"), QString("a"));
//    words.insert( QString::fromUtf8( "б"), QString("b"));
//    words.insert( QString::fromUtf8( "в"), QString("v"));
//    words.insert( QString::fromUtf8( "г"), QString("g"));
//    words.insert( QString::fromUtf8( "д"), QString("d"));
//    words.insert( QString::fromUtf8( "е"), QString("e"));
//    words.insert( QString::fromUtf8( "ё"), QString("yo"));
//    words.insert( QString::fromUtf8( "ж"), QString("zh"));
//    words.insert( QString::fromUtf8( "з"), QString("z"));
//    words.insert( QString::fromUtf8( "и"), QString("i"));
//    words.insert( QString::fromUtf8( "й"), QString("j"));
//    words.insert( QString::fromUtf8( "к"), QString("k"));
//    words.insert( QString::fromUtf8( "л"), QString("l"));
//    words.insert( QString::fromUtf8( "м"), QString("m"));
//    words.insert( QString::fromUtf8( "н"), QString("n"));
//    words.insert( QString::fromUtf8( "о"), QString("o"));
//    words.insert( QString::fromUtf8( "п"), QString("p"));
//    words.insert( QString::fromUtf8( "р"), QString("r"));
//    words.insert( QString::fromUtf8( "с"), QString("s"));
//    words.insert( QString::fromUtf8( "т"), QString("t"));
//    words.insert( QString::fromUtf8( "у"), QString("u"));
//    words.insert( QString::fromUtf8( "ф"), QString("f"));
//    words.insert( QString::fromUtf8( "х"), QString("h"));
//    words.insert( QString::fromUtf8( "ц"), QString("c"));
//    words.insert( QString::fromUtf8( "ч"), QString("ch"));
//    words.insert( QString::fromUtf8( "ш"), QString("sh"));
//    words.insert( QString::fromUtf8( "щ"), QString("sch"));
//    words.insert( QString::fromUtf8( "ъ"), QString("j"));
//    words.insert( QString::fromUtf8( "ы"), QString("i"));
//    words.insert( QString::fromUtf8( "ь"), QString("j"));
//    words.insert( QString::fromUtf8( "э"), QString("e"));
//    words.insert( QString::fromUtf8( "ю"), QString("yu"));
//    words.insert( QString::fromUtf8( "я"), QString("ya"));
//    words.insert( QString::fromUtf8( "А"), QString("A"));
//    words.insert( QString::fromUtf8( "Б"), QString("B"));
//    words.insert( QString::fromUtf8( "В"), QString("V"));
//    words.insert( QString::fromUtf8( "Г"), QString("G"));
//    words.insert( QString::fromUtf8( "Д"), QString("D"));
//    words.insert( QString::fromUtf8( "Е"), QString("E"));
//    words.insert( QString::fromUtf8( "Ё"), QString("Yo"));
//    words.insert( QString::fromUtf8( "Ж"), QString("Zh"));
//    words.insert( QString::fromUtf8( "З"), QString("Z"));
//    words.insert( QString::fromUtf8( "И"), QString("I"));
//    words.insert( QString::fromUtf8( "Й"), QString("J"));
//    words.insert( QString::fromUtf8( "К"), QString("K"));
//    words.insert( QString::fromUtf8( "Л"), QString("L"));
//    words.insert( QString::fromUtf8( "М"), QString("M"));
//    words.insert( QString::fromUtf8( "Н"), QString("N"));
//    words.insert( QString::fromUtf8( "О"), QString("O"));
//    words.insert( QString::fromUtf8( "Р"), QString("R"));
//    words.insert( QString::fromUtf8( "П"), QString("P"));
//    words.insert( QString::fromUtf8( "С"), QString("S"));
//    words.insert( QString::fromUtf8( "Т"), QString("T"));
//    words.insert( QString::fromUtf8( "У"), QString("U"));
//    words.insert( QString::fromUtf8( "Ф"), QString("F"));
//    words.insert( QString::fromUtf8( "Х"), QString("H"));
//    words.insert( QString::fromUtf8( "Ц"), QString("C"));
//    words.insert( QString::fromUtf8( "Ч"), QString("Ch"));
//    words.insert( QString::fromUtf8( "Ш"), QString("Sh"));
//    words.insert( QString::fromUtf8( "Щ"), QString("Sch"));
//    words.insert( QString::fromUtf8( "Ъ"), QString("J"));
//    words.insert( QString::fromUtf8( "Ы"), QString("I"));
//    words.insert( QString::fromUtf8( "Ь"), QString("J"));
//    words.insert( QString::fromUtf8( "Э"), QString("E"));
//    words.insert( QString::fromUtf8( "Ю"), QString("Yu"));
//    words.insert( QString::fromUtf8( "Я"), QString("Ya"));
//}
//extern QMap<QString, QString> words;
QMap<QString, QString> words;
QString Transliter::Translate(QString source)
{
    QMapIterator<QString, QString> i(words);
    QString key, value;
    while (i.hasNext()) {
        i.next();
        key = i.key();
        value = i.value();
        source = source.replace( i.key(), i.value());
    }
    return source.replace(" ","_").replace("-","_");

}
void initTransliter(){
    words.insert( QString::fromUtf8("а"), QString("a"));
    words.insert( QString::fromUtf8( "б"), QString("b"));
    words.insert( QString::fromUtf8( "в"), QString("v"));
    words.insert( QString::fromUtf8( "г"), QString("g"));
    words.insert( QString::fromUtf8( "д"), QString("d"));
    words.insert( QString::fromUtf8( "е"), QString("e"));
    words.insert( QString::fromUtf8( "ё"), QString("yo"));
    words.insert( QString::fromUtf8( "ж"), QString("zh"));
    words.insert( QString::fromUtf8( "з"), QString("z"));
    words.insert( QString::fromUtf8( "и"), QString("i"));
    words.insert( QString::fromUtf8( "й"), QString("j"));
    words.insert( QString::fromUtf8( "к"), QString("k"));
    words.insert( QString::fromUtf8( "л"), QString("l"));
    words.insert( QString::fromUtf8( "м"), QString("m"));
    words.insert( QString::fromUtf8( "н"), QString("n"));
    words.insert( QString::fromUtf8( "о"), QString("o"));
    words.insert( QString::fromUtf8( "п"), QString("p"));
    words.insert( QString::fromUtf8( "р"), QString("r"));
    words.insert( QString::fromUtf8( "с"), QString("s"));
    words.insert( QString::fromUtf8( "т"), QString("t"));
    words.insert( QString::fromUtf8( "у"), QString("u"));
    words.insert( QString::fromUtf8( "ф"), QString("f"));
    words.insert( QString::fromUtf8( "х"), QString("h"));
    words.insert( QString::fromUtf8( "ц"), QString("c"));
    words.insert( QString::fromUtf8( "ч"), QString("ch"));
    words.insert( QString::fromUtf8( "ш"), QString("sh"));
    words.insert( QString::fromUtf8( "щ"), QString("sch"));
    words.insert( QString::fromUtf8( "ъ"), QString("j"));
    words.insert( QString::fromUtf8( "ы"), QString("i"));
    words.insert( QString::fromUtf8( "ь"), QString("j"));
    words.insert( QString::fromUtf8( "э"), QString("e"));
    words.insert( QString::fromUtf8( "ю"), QString("yu"));
    words.insert( QString::fromUtf8( "я"), QString("ya"));
    words.insert( QString::fromUtf8( "А"), QString("A"));
    words.insert( QString::fromUtf8( "Б"), QString("B"));
    words.insert( QString::fromUtf8( "В"), QString("V"));
    words.insert( QString::fromUtf8( "Г"), QString("G"));
    words.insert( QString::fromUtf8( "Д"), QString("D"));
    words.insert( QString::fromUtf8( "Е"), QString("E"));
    words.insert( QString::fromUtf8( "Ё"), QString("Yo"));
    words.insert( QString::fromUtf8( "Ж"), QString("Zh"));
    words.insert( QString::fromUtf8( "З"), QString("Z"));
    words.insert( QString::fromUtf8( "И"), QString("I"));
    words.insert( QString::fromUtf8( "Й"), QString("J"));
    words.insert( QString::fromUtf8( "К"), QString("K"));
    words.insert( QString::fromUtf8( "Л"), QString("L"));
    words.insert( QString::fromUtf8( "М"), QString("M"));
    words.insert( QString::fromUtf8( "Н"), QString("N"));
    words.insert( QString::fromUtf8( "О"), QString("O"));
    words.insert( QString::fromUtf8( "Р"), QString("R"));
    words.insert( QString::fromUtf8( "П"), QString("P"));
    words.insert( QString::fromUtf8( "С"), QString("S"));
    words.insert( QString::fromUtf8( "Т"), QString("T"));
    words.insert( QString::fromUtf8( "У"), QString("U"));
    words.insert( QString::fromUtf8( "Ф"), QString("F"));
    words.insert( QString::fromUtf8( "Х"), QString("H"));
    words.insert( QString::fromUtf8( "Ц"), QString("C"));
    words.insert( QString::fromUtf8( "Ч"), QString("Ch"));
    words.insert( QString::fromUtf8( "Ш"), QString("Sh"));
    words.insert( QString::fromUtf8( "Щ"), QString("Sch"));
    words.insert( QString::fromUtf8( "Ъ"), QString("J"));
    words.insert( QString::fromUtf8( "Ы"), QString("I"));
    words.insert( QString::fromUtf8( "Ь"), QString("J"));
    words.insert( QString::fromUtf8( "Э"), QString("E"));
    words.insert( QString::fromUtf8( "Ю"), QString("Yu"));
    words.insert( QString::fromUtf8( "Я"), QString("Ya"));
}
