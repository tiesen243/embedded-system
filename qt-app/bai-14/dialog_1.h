#ifndef DIALOG_1_H
#define DIALOG_1_H

#include <QDialog>

namespace Ui {
class Dialog_1;
}

class Dialog_1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_1(QWidget *parent = nullptr);
    ~Dialog_1();

private slots:
    void on_pushButton_clicked();
    void timer_timeout();

private:
    Ui::Dialog_1 *ui;
};

#endif // DIALOG_1_H
