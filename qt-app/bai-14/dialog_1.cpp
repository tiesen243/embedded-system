#include "dialog_1.h"
#include "ui_dialog_1.h"

#include <QTimer>
#include <QMessageBox>

QTimer *timer;
int count = 10;
bool is_done = false;

Dialog_1::Dialog_1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog_1)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
    timer->start();
    ui->label->setText(QString::number(count) + "s");
}

Dialog_1::~Dialog_1()
{
    delete ui;
}

void Dialog_1::on_pushButton_clicked()
{
    is_done = true;

    int kq_1 = ui->lineEdit->text().toInt(),
        kq_2 = ui->lineEdit_3->text().toInt(),
        kq_3 = ui->lineEdit_2->text().toInt(),
        kq_5 = ui->lineEdit_4->text().toInt();
    float kq_4 = ui->lineEdit_5->text().toFloat();

    QString cau_dung[5], cau_sai[5];

    if (kq_1 == 2) cau_dung[0] = "1";
    else cau_sai[0] = "1";

    if (kq_2 == 2) cau_dung[1] = "2";
    else cau_sai[1] = "2";

    if (kq_3 == 10) cau_dung[2] = "3";
    else cau_sai[2] = "3";

    if (kq_4 == 1) cau_dung[3] = "4";
    else cau_sai[3] = "4";

    if (kq_5 == 0 && ui->lineEdit_4->text() != "") cau_dung[4] = "5";
    else cau_sai[4] = "5";

    int so_cau_dung = 0;
    QString dung = "", sai = "";
    for (int i = 0; i < 4; i++) {
        if (cau_dung[i] != "") {
            so_cau_dung ++;
            dung += (dung == "" ? "" : ", ") + cau_dung[i];
        }

        if (cau_sai[i] != "") sai += (sai == "" ? "" : ", ") + cau_sai[i];
    }

    QMessageBox::information(this, "info", QString::number(so_cau_dung) + " | " + dung + " | " + sai);
}

void Dialog_1::timer_timeout() {
    if (!is_done) {
        count--;
        ui->label->setText(QString::number(count) + "s");
    }

    if (count <= 0) {
        if (QMessageBox::information(this, "info", "Het gio lam bai")) this->close();
    }
}
