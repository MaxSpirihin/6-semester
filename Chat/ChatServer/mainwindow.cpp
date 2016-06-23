#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    startServer();
}

MainWindow::~MainWindow()
{
    delete ui;
    stopServer();
}

//Запуск сервера
void MainWindow::startServer()
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newuser()));
    if (!tcpServer->listen(QHostAddress::Any, 33333)){
        ui->textinfo->append(tcpServer->errorString());
    }
}


void MainWindow::stopServer()
{
        foreach(int i,SClients.keys()){
            QTextStream os(SClients[i]);
            os.setAutoDetectUnicode(true);
            os << QDateTime::currentDateTime().toString() << "\n";
            SClients[i]->close();
            SClients.remove(i);
        }
        tcpServer->close();
}


void MainWindow::newuser()
{
    QTcpSocket* clientSocket=tcpServer->nextPendingConnection();
    connect(clientSocket,SIGNAL(readyRead()),this, SLOT(ReadClient()));

}

void MainWindow::ReadClient()
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");  //Указываем кодировку явным обрзом
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    int id=clientSocket->socketDescriptor();
    QString message = codec->toUnicode(clientSocket->readAll());


    if (SClients.contains(id))
    {
        //этот клиент подключен, посылаем его сообщение
        SendToAllClients(message);
    }
    else
    //Клиент не подключен, передано имя
    {
        message = message.trimmed();
        if (Names.values().contains(message))
        {
            //такой пользователь уже есть
            clientSocket->write(ERROR_MESSAGE);
        }
        else
        {
            //пользователь новый, можно подключать
            SendToAllClients(QString::fromUtf8("Пользователь ") +
                             message + QString::fromUtf8(" присоединился к чату."));

            //подключаем его
            SClients[id]=clientSocket;
            Names[id]=message;
            connect(SClients[id], SIGNAL(disconnected()),
                                this, SLOT(DisconnectClient()));

            //отправляем ему историю переписки
            clientSocket->write(ui->textinfo->toPlainText().toUtf8().data());
        }
    }
}


void MainWindow::SendToAllClients(QString Message)
{
    //пишем себе
    ui->textinfo->append(Message+"\n------------------------------");

    //отправляем всем клиентам
    foreach( QTcpSocket *client, SClients.values())
    {
       client->write(Message.toUtf8().data());
    }
}


void MainWindow::DisconnectClient()
{
    int offId = -1;
    foreach (int id, SClients.keys()) {
        if (SClients[id]->socketDescriptor() == -1)
        {
            offId = id;
            break;
        }
    }

    QString nameDisc = Names[offId];

    //убираем из слушателей
    SClients.remove(offId);
    Names.remove(offId);

    SendToAllClients(QString::fromUtf8("Пользователь ") +
                     nameDisc + QString::fromUtf8(" отключился от чата."));
}
