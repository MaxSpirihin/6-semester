#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <database.h>
#include <QMap>
#include <QList>

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
    void on_lwSearchResult_clicked(const QModelIndex &index);

    void on_btnSearch_clicked();
private:
    Ui::MainWindow *ui;
    DataBase *db;
    QList<int> *ids;
    QList<QString> *names;
    void FillSearchResult();
};

#endif // MAINWINDOW_H
