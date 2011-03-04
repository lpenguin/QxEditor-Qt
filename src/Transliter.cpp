#include "Transliter.h"

TransliterInstance::TransliterInstance()
{
    words.insert("а", "a");
    words.insert("б", "b");
    words.insert("в", "v");
    words.insert("г", "g");
    words.insert("д", "d");
    words.insert("е", "e");
    words.insert("ё", "yo");
    words.insert("ж", "zh");
    words.insert("з", "z");
    words.insert("и", "i");
    words.insert("й", "j");
    words.insert("к", "k");
    words.insert("л", "l");
    words.insert("м", "m");
    words.insert("н", "n");
    words.insert("о", "o");
    words.insert("п", "p");
    words.insert("р", "r");
    words.insert("с", "s");
    words.insert("т", "t");
    words.insert("у", "u");
    words.insert("ф", "f");
    words.insert("х", "h");
    words.insert("ц", "c");
    words.insert("ч", "ch");
    words.insert("ш", "sh");
    words.insert("щ", "sch");
    words.insert("ъ", "j");
    words.insert("ы", "i");
    words.insert("ь", "j");
    words.insert("э", "e");
    words.insert("ю", "yu");
    words.insert("я", "ya");
    words.insert("А", "A");
    words.insert("Б", "B");
    words.insert("В", "V");
    words.insert("Г", "G");
    words.insert("Д", "D");
    words.insert("Е", "E");
    words.insert("Ё", "Yo");
    words.insert("Ж", "Zh");
    words.insert("З", "Z");
    words.insert("И", "I");
    words.insert("Й", "J");
    words.insert("К", "K");
    words.insert("Л", "L");
    words.insert("М", "M");
    words.insert("Н", "N");
    words.insert("О", "O");
    words.insert("П", "P");
    words.insert("Р", "R");
    words.insert("С", "S");
    words.insert("Т", "T");
    words.insert("У", "U");
    words.insert("Ф", "F");
    words.insert("Х", "H");
    words.insert("Ц", "C");
    words.insert("Ч", "Ch");
    words.insert("Ш", "Sh");
    words.insert("Щ", "Sch");
    words.insert("Ъ", "J");
    words.insert("Ы", "I");
    words.insert("Ь", "J");
    words.insert("Э", "E");
    words.insert("Ю", "Yu");
    words.insert("Я", "Ya");
}

QString Transliter::Translate(QString source)
{
    QMapIterator<QString, QString> i(transliterInstance.words);

    while (i.hasNext()) {
        i.next();
        source = source.replace( i.key(), i.value());
    }
    return source;

}
