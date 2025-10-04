#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_1.h"

QString USER_NAME = "AAA", PASSWORD = "BBB";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString userName = ui->lineEdit->text(),
        password = ui->lineEdit_2->text();

    if (userName == "" || password == "") { QMessageBox::warning(this, "UNAUTHORIZED", "User name va password khong duoc de trong"); return; }
    else if (userName != USER_NAME) { QMessageBox::warning(this, "UNAUTHORIZED", "User khong ton tai"); return; }
    else if (password != PASSWORD) { QMessageBox::warning(this, "UNAUTHORIZED", "Sai password"); return; }

    Dialog_1 d;
    d.setModal(true);
    this->hide();
    d.exec();
}

