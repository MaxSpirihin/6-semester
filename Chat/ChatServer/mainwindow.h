#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define ERROR_MESSAGE "Error"

#include <QMainWindow>
#include <QtNetwork>
#include <QTcpSocket>
#include <QObject>
#include <QByteArray>
#include <QDebug>

namespace Ui {
    class MainWindow;
}

class QTcpServer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void newuser();
    void ReadClient();
    void DisconnectClient();

private:
    Ui::MainWindow *ui;
    QTcpServer *tcpServer;
    QMap<int,QTcpSocket *> SClients;
    QMap<int,QString> Names;
    void startServer();
    void stopServer();
    void SendToAllClients(QString Message);
};

#endif // MAINWINDOW_H
