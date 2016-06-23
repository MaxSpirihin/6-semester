#ifndef WORDCUTTER_H
#define WORDCUTTER_H

#include <iostream>
#include <QRegExp>

using namespace std;

class WordCutter
{
public:
    WordCutter();
    static string CutWord(string word);
};

#endif // WORDCUTTER_H
