#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QString>
#include <database.h>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = new DataBase();

    ids = new QList<int>();
    names = new QList<QString>();
    FillSearchResult();
}


void MainWindow::FillSearchResult()
{
    ui->lwSearchResult->clear();
    for (int i =0 ; i< ids->length();i++) {
        ui->lwSearchResult->addItem(names->value(i));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lwSearchResult_clicked(const QModelIndex &index)
{
    ui->teMain->setText(db->GetCompanyInfo(ids->value(index.row())));
}

void MainWindow::on_btnSearch_clicked()
{
    if (ui->teSearch->text().length() < 4)
    {
        QMessageBox msgBox;
        msgBox.setText(QString::fromUtf8("Введите хотя бы 4 символа."));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        db->Search(ui->teSearch->text(),ids,names);
        FillSearchResult();
    }
}

