#include "mainwindow.h"

//ОСНОВЫ////////////////////
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    PrepareElements();
    Listener = new Calculator(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PrepareElements()
{
    ui->display->setText("0");
    QList<QPushButton*> TextButtons;
    TextButtons.append(ui->btnNum_0);
    TextButtons.append(ui->btnNum_1);
    TextButtons.append(ui->btnNum_2);
    TextButtons.append(ui->btnNum_3);
    TextButtons.append(ui->btnNum_4);
    TextButtons.append(ui->btnNum_5);
    TextButtons.append(ui->btnNum_6);
    TextButtons.append(ui->btnNum_7);
    TextButtons.append(ui->btnNum_8);
    TextButtons.append(ui->btnNum_9);
    TextButtons.append(ui->btnNum_Plus);
    TextButtons.append(ui->btnNum_Minus);
    TextButtons.append(ui->btnNum_Multiple);
    TextButtons.append(ui->btnNum_Divide);
    TextButtons.append(ui->btnNum_left);
    TextButtons.append(ui->btnNum_right);
    TextButtons.append(ui->btnNum_Point);

    foreach (QPushButton* btn, TextButtons) {
        QObject::connect(btn, SIGNAL(clicked()), this, SLOT(OnNumPressed()));
    }

    QObject::connect(ui->btnClear, SIGNAL(clicked()), this, SLOT(OnClearPressed()));
    QObject::connect(ui->btnEquals, SIGNAL(clicked()), this, SLOT(OnEqualsPressed()));
    QObject::connect(ui->btnBack, SIGNAL(clicked()), this, SLOT(OnBackPressed()));


}

//ВЗАИМОДЕЙСТВИЕ С НААБЛЮДАТЕЛЕМ//////////////////////
void MainWindow::OnNumPressed()
{
    //ui->display->setText(ui->display->toPlainText() + ((QPushButton*)QObject::sender())->text());
     Listener->OnTextEnter(((QPushButton*)QObject::sender())->text());
}


void MainWindow::OnClearPressed()
{
    Listener->OnClear();
}

void MainWindow::OnEqualsPressed()
{
    Listener->OnEquals();
}


void MainWindow::OnBackPressed()
{
    Listener->OnBack();
}



//РЕАЛИЗАЦИЯ ДИСПЛЕЯ
void MainWindow::ShowText(QString s)
{
    ui->display->setText(s);
}


QString MainWindow::GetText()
{
    return ui->display->toPlainText();
}


void MainWindow::Clear()
{
    ui->display->clear();
}



