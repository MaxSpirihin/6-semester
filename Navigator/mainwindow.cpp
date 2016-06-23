#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWebKit/QWebView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWebView *view = new QWebView(this);
    view->setGeometry(0,0,1280,720);
    view->load(QUrl("https://www.google.ru/maps?source=tldsi&hl=ru"));
    view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
