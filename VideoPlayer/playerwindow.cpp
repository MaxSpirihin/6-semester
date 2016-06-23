#include "playerwindow.h"
#include "ui_playerwindow.h"


using namespace Phonon;

Player *vp1, *vp2, *vp3, *vp4;
QTimer *timer;
int lastLength;


PlayerWindow::PlayerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayerWindow)
{



    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    PrepareWigets();

  //  Play(QString("C://test video//1.mp4"),4);
  //  Play(QString("C://test video//2.mp4"),2);
  //  Play(QString("C://test video//2.mp4"),3);

    lastLength =  QString::number(QApplication::applicationPid()).length();

    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer->start(100);


}

/*
void getProcList()
{
    BOOL bResult;
    PROCESSENTRY32 processInfo = {sizeof(PROCESSENTRY32)};
    HANDLE hSnapShot;
    hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    bResult = Process32First(hSnapShot, &processInfo);
    while(bResult) {
        wprintf(L"Name: %s - SysProcId: %d \n", processInfo.szExeFile,processInfo.th32ProcessID);
        bResult = Process32Next(hSnapShot, &processInfo);
    }
    CloseHandle(hSnapShot);
}
*/

//срабатывание таймера проверки
void PlayerWindow::tick()
{
    std::ifstream t(FILE_PROCESS_NAME);
    std::string str((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());
    t.close();

    if (str.length() != lastLength)
    {
        lastLength = str.length();

        QString qStr=QString::fromUtf8(str.c_str());
        QStringList lines = qStr.split("\n",QString::SkipEmptyParts);

        int mode = 0;
        bool ok;
        int res = lines[lines.length()-1].toInt(&ok,10);
        if (ok)
            mode = res;


        Play(lines[lines.length()-2],mode);
    }

   // Play(QString("C://test video//1.mp4"),1);
   // timer->stop();


}




//Запустить проигрывание
void PlayerWindow::Play(QString filename,int mode)
{
    Phonon::MediaSource source(filename);

    switch (mode) {
    case 2:
        vp2->play(source);
        break;
    case 3:
        vp3->play(source);
        break;
    case 4:
        vp4->play(source);
        break;
    default:
        vp1->play(source);
        break;
    }
}


//Стартовая подготовка
void PlayerWindow::PrepareWigets()
{
    vp1 = new Player(VideoCategory, ui->centralWidget);
    vp2 = new Player(VideoCategory, ui->centralWidget);
    vp3 = new Player(VideoCategory, ui->centralWidget);
    vp4 = new Player(VideoCategory, ui->centralWidget);

    ui->vl1->addWidget(vp1);
    ui->vl2->addWidget(vp2);
    ui->vl3->addWidget(vp3);
    ui->vl4->addWidget(vp4);

}


//Закрытие окна
void PlayerWindow::closeEvent(QCloseEvent *bar)
{
    timer->stop();
    remove(FILE_PROCESS_NAME);

    vp1->stop();
    vp2->stop();
    vp3->stop();
    vp4->stop();
}

PlayerWindow::~PlayerWindow()
{
    delete ui;
}

