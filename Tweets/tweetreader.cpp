#include "tweetreader.h"
#include <stemmer.h>
#include <iostream>
#include <fstream>
#include <QTextCodec>
#define EDGE_PLUS 0.5
#define EDGE_MINUS 5
#define DIVIDER "_"
#define COLLOC_LENGTH 3
#define COLLOC_MULTIPLYER 3

TweetReader::TweetReader(QString filename, bool ExternalDictionary)
{
    this->ExternalDictionary = ExternalDictionary;
    if (!ExternalDictionary)
    {
    QFile* file = new QFile(filename);
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    xml = new QXmlStreamReader(file);
    tweets = new QVector<Tweet>();

    while (!xml->atEnd() && !xml->hasError())
    {
       QXmlStreamReader::TokenType token = xml->readNext();
       if (token == QXmlStreamReader::StartDocument)
           continue;
       if (token == QXmlStreamReader::StartElement)
       {
           if (xml->name() == "pma_xml_export")
               continue;
           if (xml->name() == "database")
               continue;
           if (xml->name() == "table")
           {
               Tweet tweet;
               tweet.tonality = 0;
               xml->readNext();
               while (!(xml->tokenType() == QXmlStreamReader::EndElement && xml->name() == "table"))
               {
                   if (xml->tokenType() == QXmlStreamReader::StartElement)
                   {
                       if (xml->attributes().value("name")=="text")
                       {
                           xml->readNext();
                           tweet.text = xml->text().toString();
                           continue;
                       }
                       if (xml->attributes().value("name") == "sberbank" ||
                           xml->attributes().value("name") == "vtb" ||
                           xml->attributes().value("name") == "gazprom" ||
                           xml->attributes().value("name") == "alfabank" ||
                           xml->attributes().value("name") == "bankmoskvy" ||
                           xml->attributes().value("name") == "raiffeisen" ||
                           xml->attributes().value("name") == "uralsib" ||
                           xml->attributes().value("name") == "rshb")
                        {
                            xml->readNext();
                            if (xml->text().toString() != "NULL")
                                tweet.tonality = xml->text().toString().toInt();
                            continue;
                        }
                    }
                   xml->readNext();
                }
               tweets->append(tweet);
           }
       }
    }
    }
    else
    {
        //здесь сразу загружаем словарь

        //считываем файлик
        std::ifstream t(filename.toStdString().c_str());
        std::string str((std::istreambuf_iterator<char>(t)),
                         std::istreambuf_iterator<char>());
        QTextCodec * codec;
        codec = QTextCodec::codecForName("cp1251");
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForTr(codec);
        QString qStr=QString(str.c_str());

        QStringList words = qStr.split("\n");
        dictionary = new QMap<QString, double>();
        foreach (QString word, words) {
            QStringList parts = word.split("\t");
            double value = parts[1].toDouble()*5;
            dictionary->insert(Stemmer::CutWord(parts[0]),value);
        }

    }
}

TweetReader::~TweetReader()
{
    delete tweets;
    delete xml;
}


QVector<Tweet> *TweetReader::ToVector()
{
    return tweets;
}


void TweetReader::ToFile(QString filename)
{
    std::ofstream outfile(filename.toStdString().c_str());


    foreach (Tweet tweet, *tweets) {
        outfile << tweet.text.toStdString() << std::endl << tweet.tonality << std::endl;
    }
    outfile.close();
}


void TweetReader::ToConsole()
{
    foreach (Tweet tweet, *tweets) {
        std::cout << tweet.text.toStdString() << std::endl << tweet.tonality << std::endl;
    }
}

void TweetReader::ClearNeutral()
{
    if (ExternalDictionary) return;

   QVector<Tweet> *_tweets = new QVector<Tweet>();
   foreach (Tweet tweet, *tweets) {
       if (tweet.tonality != 0)
           _tweets->append(tweet);
   }
   delete tweets;
   tweets = _tweets;
}

void TweetReader::GenerateDictionary()
{
    if (ExternalDictionary) return;

    dictionary = new QMap<QString,double>();
    counts = new QMap<QString,int>();

    foreach (Tweet tweet, *tweets) {
        for (int i=1;i<COLLOC_LENGTH+1;i++)
        {
            QStringList words = SplitSentence(tweet.text,i);

            int ton_mult = i;
           /* for (int j=0;j<i;j++)
                ton_mult*=COLLOC_MULTIPLYER;*/

            AppendToDictionary(words,tweet.tonality*ton_mult);
        }
    }

    //здесь делим на кол-во встречаний
    foreach (QString word, dictionary->keys()) {
        double w = dictionary->value(word)/counts->value(word);
        dictionary->remove(word);
        dictionary->insert(word,w);
    }
}


void TweetReader::AppendToDictionary(QStringList words, int tonality)
{
    foreach (QString word, words) {
        if (!word.isEmpty())
        {
            if (!dictionary->contains(word))
            {
                counts->insert(word,1);
                dictionary->insert(word,tonality);
            }
            else
            {
                int old = dictionary->value(word);
                dictionary->remove(word);
                dictionary->insert(word,old+tonality);
                int old_count = counts->value(word);
                counts->remove(word);
                counts->insert(word,old_count+1);
            }
        }
    }
}


QStringList TweetReader::SplitSentence(QString text, int Length)
{
    //чистим строку и разрезаем по пробелам
    text = Stemmer::ClearString(text);
    QStringList _words = text.split(" ");

    //обрезаем слова и удаляем пустые
    QStringList *words = new QStringList();
    foreach (QString word, _words) {
            QString _word = Stemmer::CutWord(word);
            if (!_word.isEmpty())
                words->append(_word);
        }

    //если нужны слова, то готово, дальше составляем словосочетания
    if (Length == 1) return *words;

    QStringList *collocations = new QStringList();
    int l = words->length()-Length;
    for (int i=0;i<l;i++)
    {
        QString collocation = "";
        for (int j=0;j<Length;j++)
        {
            if (j>0)
                collocation+=DIVIDER;
            collocation+=words->at(i+j);
        }
        collocations->append(collocation);
    }

    return *collocations;
}

void TweetReader::DictionaryToFile(QString filename)
{
    std::ofstream outfile(filename.toStdString().c_str());


    foreach (QString word, dictionary->keys()) {
        outfile << word.toUtf8().data() << std::endl << dictionary->value(word) << std::endl;
    }

    outfile.close();
}


int TweetReader::GetTonality(QString tweet)
{
    double weight = 0;


    QStringList words = SplitSentence(tweet,1);
    foreach (QString word, words) {
        if (dictionary->contains(word))
            weight += dictionary->value(word);
    }

    //weight/=words.length();

    if (weight > EDGE_PLUS)
        return 1;
    if (weight < -EDGE_MINUS)
        return -1;
    return 0;
}

//вычислить весь файл и получть результат
//можно сразу писать в файл
//можно писать только неверные
ExpertResult TweetReader::ComputeFile(QString filename,const char* LogFile,const bool OnlyWrong)
{
    //если просят, создаем файл
    QString LogF(LogFile);
    std::ofstream *outfile;
    if (!LogF.isEmpty())
        outfile = new std::ofstream (LogF.toStdString().c_str());

    TweetReader tr(filename,false);
    QVector<Tweet> *tweets = tr.ToVector();
    ExpertResult result;
    result.PlusPlus = 0;
    result.PlusNeutral = 0;
    result.PlusMinus = 0;
    result.NeutralPlus = 0;
    result.NeutralNeutral = 0;
    result.NeutralMinus = 0;
    result.MinusPlus = 0;
    result.MinusNeutral = 0;
    result.MinusMinus = 0;
    result.TrueValue = 0;
    result.FalseValue = 0;

    foreach (Tweet tweet, *tweets) {


        int RealTonality = tweet.tonality;
        int myTonality = GetTonality(tweet.text);

        if (RealTonality == 1 && myTonality == 1)
            result.PlusPlus++;
        else if (RealTonality == 0 && myTonality == 1)
            result.PlusNeutral++;
        else if (RealTonality == -1 && myTonality == 1)
            result.PlusMinus++;
        else if (RealTonality == 1 && myTonality == 0)
            result.NeutralPlus++;
        else if (RealTonality == 0 && myTonality == 0)
            result.NeutralNeutral++;
        else if (RealTonality == -1 && myTonality == 0)
            result.NeutralMinus++;
        else if (RealTonality == 1 && myTonality == -1)
            result.MinusPlus++;
        else if (RealTonality == 0 && myTonality == -1)
            result.MinusNeutral++;
        else if (RealTonality == -1 && myTonality == -1)
            result.MinusMinus++;

        if (RealTonality == myTonality)
            result.TrueValue++;
        else
            result.FalseValue++;

        if (!LogF.isEmpty())
        {
            if (RealTonality != myTonality || !OnlyWrong)
                *outfile << tweet.text.toUtf8().data() << std::endl << myTonality
                         << std::endl << RealTonality << std::endl;
        }
    }

    if (!LogF.isEmpty())
        outfile->close();

    return result;
}


