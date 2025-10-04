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

void MainWindow::on_pushButton_clicked()
{
   int a = ui->lineEdit->text().toInt();
   int b = ui->lineEdit_2->text().toInt();

   ui->label_7->setText(QString("%1").arg(a + b));
   ui->label_8->setText(QString("%1").arg(a - b));
   ui->label_9->setText(QString("%1").arg(a * b));
   ui->label_10->setText(QString("%1").arg(a / b));

}
