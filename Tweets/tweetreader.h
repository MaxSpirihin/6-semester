#ifndef XMLREADER_H
#define XMLREADER_H
#include <QXmlStreamReader>
#include <QString>
#include <QVector>
#include <QFile>
#include <iostream>
#include <fstream>
#include <QMap>
#include <QStringList>

struct Tweet
{
    QString text;
    int tonality;
};


struct ExpertResult//результат работы, первый знак - оределние машины, второц - человека
{
    int PlusPlus;
    int PlusNeutral;
    int PlusMinus;
    int NeutralPlus;
    int NeutralNeutral;
    int NeutralMinus;
    int MinusPlus;
    int MinusNeutral;
    int MinusMinus;
    int TrueValue;
    int FalseValue;
};


class TweetReader
{
public:
    TweetReader(QString filename, bool ExternalDictionary);
    ~TweetReader();
    QVector<Tweet> *ToVector();
    void ToFile(QString filename);
    void DictionaryToFile(QString filename);
    void ToConsole();
    void ClearNeutral();
    void GenerateDictionary();
    int GetTonality(QString tweet);
    ExpertResult ComputeFile(QString filename,const char* LogFile="",const bool OnlyWrong = false);

private:
    QXmlStreamReader *xml;
    QVector<Tweet> *tweets;
    QMap<QString,double> *dictionary;
    QMap<QString,int> *counts;//это для учета кол-ва вхождений,иначе сбербанк встретиля 4500 и -500
    void AppendToDictionary(QStringList words, int tonality);//добавляет слова в словарь
    QStringList SplitSentence(QString text,int Length);//разрезать на слова или словосочетания длиной Length
    bool ExternalDictionary;
};

#endif // XMLREADER_H
