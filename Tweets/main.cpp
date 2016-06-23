#include <QCoreApplication>
#include <tweetreader.h>
#include <stemmer.h>
#include <QMap>
#include <QString>
#include <iostream>
#define USE_EXTERNAL false

using namespace std;

inline string int_to_str(int n, int len)
{
    string result(len--, ' ');
    for (int val=(n<0)?-n:n; len>=0&&val!=0; --len,val/=10)
       result[len]='0'+val%10;
    if (len>=0&&n<0) result[0]='-';
    return result;
}

int main(int argc, char *argv[])
{

TweetReader *tr;

if (!USE_EXTERNAL)
{
    cout << "Dictionary is generating by training sample." << endl;
    cout << "Please wait..." << endl;
    tr = new TweetReader("C:/Users/Max/Documents/qt/Tweets/tonalnost/train_real.xml",false);
    tr->ClearNeutral();
    tr->GenerateDictionary();
    tr->DictionaryToFile("C:/Users/Max/Documents/qt/Tweets/tonalnost/dictionary.txt");
}
else
{
    cout << "External dictionary is using." << endl;
    cout << "Please wait..." << endl;
    tr = new TweetReader("C:/Users/Max/Documents/qt/Tweets/tonalnost/words.txt",true);
}
    ExpertResult r = tr->ComputeFile("C:/Users/Max/Documents/qt/Tweets/tonalnost/banks_test_etalon.xml",
                                     "C:/Users/Max/Documents/qt/Tweets/tonalnost/log.txt",true);

    cout << "Vertical - system, horizontal - expert." << endl;
    cout << "      1      0      -1" << endl;
    cout << "1   " << int_to_str(r.PlusPlus,5) << "  " << int_to_str(r.NeutralPlus,5) << "  " << int_to_str(r.MinusPlus,5) << endl;
    cout << "0   " << int_to_str(r.PlusNeutral,5) << "  " << int_to_str(r.NeutralNeutral,5) << "  " << int_to_str(r.MinusNeutral,5) << endl;
    cout << "-1  " << int_to_str(r.PlusMinus,5) << "  " << int_to_str(r.NeutralMinus,5) << "  " << int_to_str(r.MinusMinus,5) << endl;

   /*
    cout << "++  " << r.PlusPlus << "  +" << endl;
    cout << "+0  " << r.PlusNeutral<< "  -" << endl;
    cout << "+-  " << r.PlusMinus<< "  -" << endl;
    cout << "0+  " << r.NeutralPlus<< "  -" << endl;
    cout << "00  " << r.NeutralNeutral<< "  +" << endl;
    cout << "0-  " << r.NeutralMinus<< "  -" << endl;
    cout << "-+  " << r.MinusPlus<< "  -" << endl;
    cout << "-0  " << r.MinusNeutral<< "  -" << endl;
    cout << "--  " << r.MinusMinus<< "  +" << endl;

    cout << "Correct - " << r.TrueValue << endl;
    cout << "InCorrect - " << r.FalseValue << endl;
    cout << "Percent - " + QString::number(r.TrueValue*1.0/(r.FalseValue + r.TrueValue)).toStdString() << endl;
    */
    system("pause");
}
