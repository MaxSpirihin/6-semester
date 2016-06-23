#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define ERROR_MESSAGE "Error"

#include <QMainWindow>
#include <QString>
#include <QTcpSocket>
#include <QListWidgetItem>
#include <QTextCodec>
#include <QTextStream>
#include <QDateTime>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnSend_clicked();
    void on_btnName_clicked();
    void onServerReadName();
    void onServerReadMessage();


private:
    Ui::MainWindow *ui;
    QString userName;
    QTcpSocket* m_pTcpSocket;
    void PrepareField();
    void SendMessage(QString message);
    void RecieveMessage(QString message);
};

#endif // MAINWINDOW_H
