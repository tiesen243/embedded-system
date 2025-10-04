#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_released()
{
    QString a, b, c;

    if (ui->checkBox->isChecked())
        a = "nhac ";
    if (ui->checkBox_2->isChecked())
        b = "phim ";
    if (ui->checkBox_3->isChecked())
        c = "game";

    if (a == "" && b == "" && c == "") ui->label->setText("Not thing");
    else ui->label->setText(a +b +c);
}
