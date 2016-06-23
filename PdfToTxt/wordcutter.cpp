#include <iostream>
#include "WordCutter.h"
#include <QRegExp>
#include <QString>

static QRegExp PERFECTIVEGROUND = QRegExp("((ив|ивши|ившись|ыв|ывши|ывшись)|([ая](в|вши|вшись)))$");
static QRegExp PERFECTIVEGROUND_CUT = QRegExp("((ив|ивши|ившись|ыв|ывши|ывшись)|(в|вши|вшись))$");
static QRegExp REFLEXIVE = QRegExp("(с[яь])$");
static QRegExp ADJECTIVE = QRegExp("(ее|ие|ые|ое|ими|ыми|ей|ий|ый|ой|ем|им|ым|ом|его|ого|ему|ому|их|ых|ую|юю|ая|яя|ою|ею)$");
static QRegExp VERB = QRegExp("((ила|ыла|ена|ейте|уйте|ите|или|ыли|ей|уй|ил|ыл|им|ым|ен|ило|ыло|ено|ят|ует|уют|ит|ыт|ены|ить|ыть|ишь|ую|ю)|(([ая])(ла|на|ете|йте|ли|й|л|ем|н|ло|но|ет|ют|ны|ть|ешь|нно)))$");
static QRegExp VERB_CUT = QRegExp("((ила|ыла|ена|ейте|уйте|ите|или|ыли|ей|уй|ил|ыл|им|ым|ен|ило|ыло|ено|ят|ует|уют|ит|ыт|ены|ить|ыть|ишь|ую|ю)|(ла|на|ете|йте|ли|й|л|ем|н|ло|но|ет|ют|ны|ть|ешь|нно))$");
static QRegExp NOUN = QRegExp("(а|ев|ов|ие|ье|е|иями|ями|ами|еи|ии|и|ией|ей|ой|ий|й|иям|ям|ием|ем|ам|ом|о|у|ах|иях|ях|ы|ь|ию|ью|ю|ия|ья|я)$");
static QRegExp RVRE = QRegExp("[аеиоуыэюя]");
static QRegExp DER = QRegExp("ость?$");
static QRegExp SUPERLATIVE = QRegExp("(ейше|ейш)$");
static QRegExp I = QRegExp("и$");
static QRegExp P = QRegExp("ь$");
static QRegExp NN = QRegExp("нн$");
static QRegExp N = QRegExp("н$");


string LowerCase(string s)
{
    int dif = 'а' - 'А';
    for (int i = 0; i<s.length(); i++)
    {
        if ((s[i] >= 'А') && (s[i] <= 'Я'))
            s[i] += dif;
    }
    return s;
}


bool CutEnding(string *s, QRegExp pattern)
{
    int a = pattern.indexIn(QString(*s->c_str()));
    if (a >= 0)
    {
        //концовка нашлась - режем ее
        *s = QString(*s->c_str()).replace(pattern,"").toStdString();
   }
    return a;
}


bool CutEndingWithCheck(string *s, QRegExp PatternCheck, QRegExp PatternCut)
{
    int a = PatternCheck.indexIn(QString(*s->c_str()));
    if (a >= 0)
    {
        //концовка нашлась - режем ее
        *s = QString(*s->c_str()).replace(PatternCut,"").toStdString();
    }
    return a;
}


bool GetPreAndRV(string source,string* Pre, string* RV)
{
    //находим первую гласную
    int position = RVRE.indexIn(QString(source.c_str()));
    bool haveVowel = position != -1;

    if (!haveVowel)
    {
        *Pre = source;
        *RV = string("");
        return false;
    }
    else
    {
        *Pre = source.substr(0, position+1);
        *RV = source.substr(position + 1, source.length() - position);
        return true;
    }

}


string WordCutter::CutWord(string word)
{
    //начальные приготовления
    word = LowerCase(word);

    word = QString(word.c_str()).replace(QRegExp("ё"), "е").toStdString();

    //поиск RV и того, что перед ним
    string *Pre = new string();
    string *RV = new string();
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

    //std::cout << word << endl;
    return word;
}



