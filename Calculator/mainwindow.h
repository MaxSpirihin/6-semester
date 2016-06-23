#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "main.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public IDisplay
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    virtual void ShowText(QString s);
    virtual QString GetText();
    virtual void Clear();

public slots:
    void OnNumPressed();
    void OnClearPressed();
    void OnBackPressed();
    void OnEqualsPressed();


private:
    Ui::MainWindow *ui;
    ICommandListener* Listener;
    void PrepareElements();
};

#endif // MAINWINDOW_H
