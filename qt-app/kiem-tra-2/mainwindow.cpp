#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"

QTimer *timer;
bool is_all_on = false, is_toggle = false;
int position = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    is_all_on = true;
    ui->lineEdit->setText("Sang");
    ui->lineEdit_2->setText("Sang");
    ui->lineEdit_3->setText("Sang");
    ui->lineEdit_4->setText("Sang");
}


void MainWindow::on_pushButton_2_clicked()
{
    is_all_on = false;
    ui->lineEdit->setText("Tat");
    ui->lineEdit_2->setText("Tat");
    ui->lineEdit_3->setText("Tat");
    ui->lineEdit_4->setText("Tat");
}


void MainWindow::on_pushButton_3_clicked()
{
    is_toggle = true;
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);

    ui->label_5->setText(
        is_all_on ?
            "Trang thai: tat dan tu duoi len" :
            "Trang thai: sang dan tu duoi len"
    );
}


void MainWindow::timer_timeout()  {
    if (!is_toggle) return;

    switch (position) {
    case 0:
        ui->lineEdit_4->setText(is_all_on ? "Tat" : "Sang");
        position++;
        break;
    case 1:
        ui->lineEdit_3->setText(is_all_on ? "Tat" : "Sang");
        position++;
        break;
    case 2:
        ui->lineEdit_2->setText(is_all_on ? "Tat" : "Sang");
        position++;
        break;
    case 3:
        ui->lineEdit->setText(is_all_on ? "Tat" : "Sang");
        position++;
        break;
    default:
        position = 0;
        is_toggle = false;
        is_all_on = !is_all_on;
        ui->pushButton->setDisabled(false);
        ui->pushButton_2->setDisabled(false);
        ui->pushButton_3->setDisabled(false);
        break;
    }
}
