#include <QTimer>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

QTimer  *timer;
int count = 10;
bool is_done = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
    timer->start();
    ui->label_9->setText(QString::number(count));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    is_done = true;
    int a = 10, b = 2;

    ui->lineEdit->setDisabled(true);
    ui->lineEdit_2->setDisabled(true);
    ui->lineEdit_3->setDisabled(true);
    ui->lineEdit_4->setDisabled(true);
    ui->lineEdit_5->setDisabled(true);
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(false);

    if (ui->lineEdit->text() == "" && ui->lineEdit_2->text() == "" &&
        ui->lineEdit_3->text() == "" && ui->lineEdit_4->text() == "" &&
        ui->lineEdit_5->text() == "") {

        ui->label_6->setText("Khong co ket qua");
        ui->label_7->setText("");
        ui->label_10->setText("");
        ui->label_11->setText("");
        return;
    }

    int kq_1 = ui->lineEdit->text().toInt(),
        kq_2 = ui->lineEdit_2->text().toInt(),
        kq_3 = ui->lineEdit_3->text().toInt(),
        kq_5 = ui->lineEdit_5->text().toInt();
    float kq_4 = ui->lineEdit_4->text().toFloat();

    QString cau_dung[5];
    QString cau_sai[5];

    if (kq_1 == a + b) cau_dung[0] = "1";
    else cau_sai[0] = "1";

    if (kq_2 == a - b)cau_dung[1] = "2";
    else cau_sai[1] = "2";

    if (kq_3 == a * b) cau_dung[2] = "3";
    else cau_sai[2] = "3";

    if (kq_4 == a / b) cau_dung[3] = "4";
    else cau_sai[3] = "4";

    if (kq_5 == a % b && ui->lineEdit_5->text() != "") cau_dung[4] = "5";
    else cau_sai[4] = "5";

    QString d = "", s = "";
    int so_cau = 0;
    for (int i = 0; i < 5; i++) {
        if (cau_dung[i] != "") {
            so_cau++;
            d += (d == "" ? "" : ", ") + cau_dung[i];
        }

        if (cau_sai[i] != "")
            s += (s == "" ? "" : ", ") + cau_sai[i];
    }

    ui->label_6->setText("So cau dung: " + QString("%1").arg(so_cau));
    ui->label_10->setText("Cau dung: " + d);
    ui->label_11->setText("Cau sai: " + s);
    ui->label_7->setText("Diem: " + QString("%1").arg(so_cau * 2));
}

void MainWindow::timer_timeout()  {
    if (count >= 0 && is_done == false)
        count --;
    ui->label_9->setText(QString::number(count));

    if (count < 0 && is_done == false) {
        if (QMessageBox::information(this, "info", "Het gio"))
            this->close();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setDisabled(false);
    ui->lineEdit_2->setDisabled(false);
    ui->lineEdit_3->setDisabled(false);
    ui->lineEdit_4->setDisabled(false);
    ui->lineEdit_5->setDisabled(false);
    ui->pushButton->setDisabled(false);
    ui->pushButton_2->setDisabled(true);

    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    ui->label_6->setText("So cau dung: ");
    ui->label_10->setText("Cau dung: ");
    ui->label_11->setText("Cau sai: ");
    ui->label_7->setText("Diem: ");

    count = 10;
    ui->label_9->setText(QString::number(count));
    is_done = false;
}


