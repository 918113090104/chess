#ifndef DIALOG_H
#define DIALOG_H
#include<QDialog>
//游戏刚开始的页面，有两个按钮，“开始游戏”和“退出”
namespace Ui {
class Dialog;
}
class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent=0);
   ~Dialog();

private slots:    //俩按钮的槽函数
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
