#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBox->setValue(10);
    ui->dial->setMaximum(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBox_valueChanged(const QString &arg1)
{
    ui->lineEdit->setText(arg1);
}

void MainWindow::on_dial_valueChanged(int value)
{
    ui->lcdNumber->display(value);
}
