#include "mainwindow.h"
#include "ui_mainwindow.h"

int value = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    value = ui->dial->value();
    // QString("%1").arg(value)
    ui->lineEdit->setText(QString::number(value));
    ui->lineEdit_2->setText(QString::number(ui->spinBox->value()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dial_sliderMoved(int position)
{
    value = position;
    ui->lineEdit->setText(QString::number(value));
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->lineEdit_2->setText(QString::number(arg1));
}


void MainWindow::on_pushButton_clicked()
{
    value += ui->spinBox->value();
    if (value > 2000) value = 2000;

    ui->lcdNumber->display(QString::number(value));
}


void MainWindow::on_pushButton_2_clicked()
{
    value -= ui->spinBox->value();
    if (value < 100) value = 100;

    ui->lcdNumber->display(QString::number(value));
}

