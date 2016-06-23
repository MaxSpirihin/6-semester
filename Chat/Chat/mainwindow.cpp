#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    userName = QString("_");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    PrepareField();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::PrepareField()
{
    ui->mainWidget->setVisible(false);
    ui->chatText->setReadOnly(true);

    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost("MAX-MSI", 33333);
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(onServerReadName()));
}

void MainWindow::SendMessage(QString message)
{
    m_pTcpSocket->write(QString(userName + " : " + message).toUtf8().data());
}

void MainWindow::RecieveMessage(QString message)
{
    ui->chatText->append(message+"\n------------------------------");
}

void MainWindow::on_btnSend_clicked()
{
    if (ui->te_Message->toPlainText().isEmpty())
        return;
    SendMessage(ui->te_Message->toPlainText());
    ui->te_Message->clear();
}

void MainWindow::on_btnName_clicked()
{
    if (ui->te_Name->toPlainText().isEmpty())
        return;

    userName = ui->te_Name->toPlainText().trimmed();
    m_pTcpSocket->write(userName.toUtf8().data());
}

void MainWindow::onServerReadName()
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextStream os(m_pTcpSocket);
    QString message = codec->toUnicode(m_pTcpSocket->readAll());

    if (message == ERROR_MESSAGE)
    {
        //ошибка, такой пользователь уже есть
        ui->te_Name->clear();

        QMessageBox msgBox;
        msgBox.setText(QString::fromUtf8("Такой пользователь уже есть."));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        //мы подключились и нам вернули весь чатик
        disconnect(m_pTcpSocket, SIGNAL(readyRead()),this, SLOT(onServerReadName()));
        connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(onServerReadMessage()));
        ui->mainWidget->setVisible(true);
        ui->NameWidget->setVisible(false);
        ui->lblUserName->setText(QString::fromUtf8("Вы - ") + userName);
        ui->chatText->append(message);
    }
}


void MainWindow::onServerReadMessage()
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextStream os(m_pTcpSocket);
    QString message = codec->toUnicode(m_pTcpSocket->readAll());
    RecieveMessage(message);
}
