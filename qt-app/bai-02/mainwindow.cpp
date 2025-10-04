#include <math.h>

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

void MainWindow::on_pushButton_exe_clicked()
{
   int a = ui->lineEdit_a->text().toInt();
   int b = ui->lineEdit_b->text().toInt();

   ui->lineEdit_ab->setText(QString("%1").arg(a + b));
   ui->lineEdit_a2->setText(QString("%1").arg(sqrt(a)));
}
