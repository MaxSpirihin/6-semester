#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QMainWindow>
#include "main.h"

namespace Ui {
class PlayerWindow;
}

class PlayerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayerWindow(QWidget *parent = 0);
    ~PlayerWindow();
    void Play(QString filename, int mode);

public slots:
    void tick();

private:
    Ui::PlayerWindow *ui;
    void PrepareWigets();
    void closeEvent(QCloseEvent *bar);
};

#endif // PLAYERWINDOW_H
