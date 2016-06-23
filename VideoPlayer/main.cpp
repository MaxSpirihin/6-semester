#include "main.h"
#include <QProcess>
#include <windows.h>


BOOL IsProcessRunning(DWORD pid)
{
    HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, pid);
    DWORD ret = WaitForSingleObject(process, 0);
    CloseHandle(process);
    return ret == WAIT_TIMEOUT;
}

//Первый запуск - отдаем управление приложению
int StartMainMode(int argc, char *argv[])
{
    //создаем секретный файлик
    std::ofstream outfile(FILE_PROCESS_NAME);
    qint64 b = QApplication::applicationPid();
    outfile << b;
    outfile.close();

    //запускаем сообственно плеер
    QApplication a(argc,argv);
    PlayerWindow *player = new PlayerWindow();
    QStringList args = Utils::arguments(argc,argv);
    if (args.length()>1)
    {
        int mode = 0;
        if (args.length()>2)
        {
            bool ok;
            int res = args[2].toInt(&ok,10);
            if (ok)
                mode = res;
        }
        player->Play(args[1],mode);
    }


    player->show();




    return a.exec();
}




//Повторный запуск - пишем в файл
int StartExtraMode(int argc, char *argv[])
{
    QStringList args = Utils::arguments(argc,argv);

    std::ofstream outfile;


    if (args.length()>1)
    {

        outfile.open(FILE_PROCESS_NAME, std::ios_base::app);

        outfile << std::endl;
        outfile << args[1].toStdString() << std::endl;
        if (args.length()>2)
            outfile << args[2].toStdString();
        else
            outfile << "-";

        outfile << std::endl;
        outfile.close();
    }

    return 0;
}
int main(int argc, char *argv[])
{
    std::ifstream file(FILE_PROCESS_NAME);

    if (!file)
    {
        file.close();
        return StartMainMode(argc,argv);
    }


    std::string str((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
    file.close();

     QString qStr=QString::fromUtf8(str.c_str());
     QStringList lines = qStr.split("\n",QString::SkipEmptyParts);

     bool ok;
     int pid = lines[0].toInt(&ok,10);

     if (!ok)
        return StartMainMode(argc,argv);

    if (IsProcessRunning(pid))
        return StartExtraMode(argc,argv);
    else
        return StartMainMode(argc,argv);
}



