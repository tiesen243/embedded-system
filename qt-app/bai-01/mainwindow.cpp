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

void MainWindow::on_btn_exe_clicked()
{
        QString str_lop = ui->lineEdit_lop->text();
        QString str_ten = ui->lineEdit_ten->text();

        ui->label_result->setText("Chao ban " + str_lop + ", lop " + str_ten + ". Chuc ban hoc tot");
}
