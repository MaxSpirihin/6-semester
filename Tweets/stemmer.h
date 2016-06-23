#ifndef STEMMER_H
#define STEMMER_H
#include <QString>
#include <QRegExp>

class Stemmer
{
public:
    static QString CutWord(QString word);
    static QString ClearString(QString s);
};

#endif // STEMMER_H
