#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <QStringList>

#define EXEPATH "C:\\Users\\Max\\Documents\\qt\\build-PdfToTxt-Real-Debug\\debug\\poppler\\"
#define TEXTPATH "C:\\Users\\Max\\Desktop\\1\\1\\"



bool IsOne(QString first, QString second)
{
    return false;
}


int main(int argc, char *argv[])
{
    //создаем файлик
    QString file = "C:\\Users\\Max\\Desktop\\1\\6.pdf";
    QString textFile = "C:\\Users\\Max\\Desktop\\1\\temp.txt";
    system((EXEPATH + QString("pdftotext.exe ") + file + " " + textFile).toStdString().c_str());

    //считываем файлик
    std::ifstream t("C:\\Users\\Max\\Desktop\\1\\temp.txt");
    std::string str((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());
    QString qStr=QString::fromUtf8(str.c_str());


    //создаем массив абзацов
    QStringList _list = qStr.split("\n\n");

    //пишем все в файлики
    QStringList list;

    for (int i=0;i<_list.length();i++)
    {
         if (_list[i].length()>80)
             list.append(_list[i]);
    }


    int num = 1;
    for (int i=0;i<list.length();i++)
    {
        if (list[i].length()<80)
            continue;

        bool canMerge = i<list.length()-1 && (list[i+1].length()>80);
        if (canMerge)
        {
            QRegExp rg( "[.?!]$");
            if (rg.indexIn(list[i])==-1)
            {
                QRegExp dash("[-]$");
                list[i].replace(dash,"");
                list[i+1]=list[i]+list[i+1];
                continue;
            }
        }

        std::ofstream outfile((QString(TEXTPATH) + QString::number(num) + QString(".txt")).toStdString().c_str());
        outfile << list[i].toUtf8().constData();
        outfile.close();
        num++;
    }

    std::cout << "Its done";

    return 0;
}
