#include <QMessageBox>

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

        QMessageBox msgBox;

        msgBox.setText(tr("Hay chon phep tinh?"));
        QAbstractButton *btnPlus = msgBox.addButton(tr("a + b"), QMessageBox::ActionRole);
        QAbstractButton *btnMinus = msgBox.addButton(tr("a - b"), QMessageBox::ActionRole);
        QAbstractButton *btnMul = msgBox.addButton(tr("a * b"), QMessageBox::ActionRole);
        QAbstractButton *btnDiv = msgBox.addButton(tr("a / b"), QMessageBox::ActionRole);

        msgBox.exec();

        if (msgBox.clickedButton() == btnPlus) {
            ui->label_2->setText(QString("%1").arg(a + b));
        } else if (msgBox.clickedButton() == btnMinus) {
            ui->label_2->setText(QString("%1").arg(a - b));
        }else if (msgBox.clickedButton() == btnMul) {
            ui->label_2->setText(QString("%1").arg(a * b));
        }else if (msgBox.clickedButton() == btnDiv) {
            ui->label_2->setText(QString("%1").arg(a / b));
        }
}
