#include "stemmer.h"

static QRegExp PERFECTIVEGROUND = QRegExp(QString::fromUtf8("((ив|ивши|ившись|ыв|ывши|ывшись)|([ая](в|вши|вшись)))$"));
static QRegExp PERFECTIVEGROUND_CUT = QRegExp(QString::fromUtf8("((ив|ивши|ившись|ыв|ывши|ывшись)|(в|вши|вшись))$"));
static QRegExp REFLEXIVE = QRegExp(QString::fromUtf8("(с[яь])$"));
static QRegExp ADJECTIVE = QRegExp(QString::fromUtf8("(ее|ие|ые|ое|ими|ыми|ей|ий|ый|ой|ем|им|ым|ом|его|ого|ему|ому|их|ых|ую|юю|ая|яя|ою|ею)$"));
static QRegExp VERB = QRegExp(QString::fromUtf8("((ила|ыла|ена|ейте|уйте|ите|или|ыли|ей|уй|ил|ыл|им|ым|ен|ило|ыло|ено|ят|ует|уют|ит|ыт|ены|ить|ыть|ишь|ую|ю)|(([ая])(ла|на|ете|йте|ли|й|л|ем|н|ло|но|ет|ют|ны|ть|ешь|нно)))$"));
static QRegExp VERB_CUT = QRegExp(QString::fromUtf8("((ила|ыла|ена|ейте|уйте|ите|или|ыли|ей|уй|ил|ыл|им|ым|ен|ило|ыло|ено|ят|ует|уют|ит|ыт|ены|ить|ыть|ишь|ую|ю)|(ла|на|ете|йте|ли|й|л|ем|н|ло|но|ет|ют|ны|ть|ешь|нно))$"));
static QRegExp NOUN = QRegExp(QString::fromUtf8("(а|ев|ов|ие|ье|е|иями|ями|ами|еи|ии|и|ией|ей|ой|ий|й|иям|ям|ием|ем|ам|ом|о|у|ах|иях|ях|ы|ь|ию|ью|ю|ия|ья|я)$"));
static QRegExp RVRE = QRegExp(QString::fromUtf8("[аеиоуыэюя]"));
static QRegExp DER = QRegExp(QString::fromUtf8("ость?$"));
static QRegExp SUPERLATIVE = QRegExp(QString::fromUtf8("(ейше|ейш)$"));
static QRegExp I = QRegExp(QString::fromUtf8("и$"));
static QRegExp P = QRegExp(QString::fromUtf8("ь$"));
static QRegExp NN = QRegExp(QString::fromUtf8("нн$"));
static QRegExp N = QRegExp(QString::fromUtf8("н$"));
static QRegExp ALPHABET = QRegExp(QString::fromUtf8("[^абвгдеёжзийклмнопрстуфхцчшщьыъэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯ]"));

bool CutEnding(QString *s, QRegExp pattern)
{
    bool a = pattern.indexIn(*s) != -1;
    if (a)
    {
        //концовка нашлась - режем ее
        *s = s->replace(pattern, "");
    }
    return a;
}


bool CutEndingWithCheck(QString *s, QRegExp PatternCheck,QRegExp PatternCut)
{
    bool a = PatternCheck.indexIn(*s) != -1;
    if (a)
    {
        //концовка нашлась - режем ее
        *s = s->replace(PatternCut, "");
    }
    return a;
}


bool GetPreAndRV(QString source,QString* Pre, QString* RV)
{
    //находим первую гласную
    int position = RVRE.indexIn(source);

    if (position == -1)
    {
        *Pre = source;
        *RV = QString("");
        return false;
    }
    else
    {
        *Pre = source.mid(0, position+1);
        *RV = source.mid(position + 1, source.length() - position);
        return true;
    }

}




QString Stemmer::CutWord(QString word)
{
    //начальные приготовления
    word = word.toLower();

    word = word.replace(QRegExp(QString::fromUtf8("ё")), QString::fromUtf8("е"));

    //поиск RV и того, что перед ним
    QString *Pre = new QString();
    QString *RV = new QString();
    bool haveVowel = GetPreAndRV(word, Pre, RV);



    if (haveVowel) {
        //шаг 1
        if (!CutEndingWithCheck(RV, PERFECTIVEGROUND, PERFECTIVEGROUND_CUT))
        {
            //не обрезалось, пробуем удалить REFLEXIVE
            bool a = CutEnding(RV, REFLEXIVE);
            if (!CutEnding(RV, ADJECTIVE) || a)
            {
                if (!CutEndingWithCheck(RV, VERB, VERB_CUT))
                {
                    CutEnding(RV, NOUN);
                }
            }
        }

        //шаг 2
        CutEnding(RV, I);

        //шаг 3
        CutEnding(RV, P);
        CutEnding(RV, SUPERLATIVE);
        CutEndingWithCheck(RV, NN, N);

        word = *Pre + *RV;
    }

    return word;
}

QString Stemmer::ClearString(QString s)
{
    return s.replace(ALPHABET," ");
}
