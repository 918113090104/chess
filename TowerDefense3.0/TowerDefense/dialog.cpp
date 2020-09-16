#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent):
    QDialog(parent),

    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog(){
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    accept();   //模式对话框的槽函数
}

void Dialog::on_pushButton_2_clicked()
{
    close();   //关闭
}
