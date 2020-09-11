#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "pieces.h"
#include <QMainWindow>
#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <QtMath>
#include <QtGlobal>
#include <QTime>
#include <QMessageBox>
#include <QPushButton>
#include <QTimer>
#include <QLCDNumber>
#include <QPalette>
#include <QString>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



    int x;  //每格边长
    int flag[32];//标识被翻中的棋子ID
    int count=0;//用于flag数组
    int before=-1;//上一次点击的棋子ID;
    int r_col=0;//被吃掉的红色的棋子放的列
    int b_col=0;//被吃掉的黑色棋子放的列
    int turn=0;//trun=1,计算机走棋
    int first=0;
    QString recv="none";
    Pieces p[32];//定义32颗棋子
    QPushButton *button;


    void paintEvent(QPaintEvent *);//所有需要绘制的都写在这个函数里


    void drawPieces(QPainter &painters, int id);//画棋子

    void mouseReleaseEvent(QMouseEvent *);
    bool getRowCol(QPoint p,int &row,int &col);
    bool movement(int before1,int row1,int col1,int now1);
    bool gameOver();
    //以下9个函数为走棋规则
    bool shuai(int before2,int row2,int col2,int now2);
    bool jiang(int before2,int row2,int col2,int now2);
    bool shi(int before2,int row2,int col2,int now2);
    bool xiang(int before2,int row2,int col2,int now2);
    bool che(int before2,int row2,int col2,int now2);
    bool ma(int before2,int row2,int col2,int now2);
    bool pao(int before2,int row2,int col2,int now2);
    bool bing(int before2,int row2,int col2,int now2);
    bool zu(int before2,int row2,int col2,int now2);

public slots:
     void slotStart();
     void Timeout();


private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QLCDNumber *time;
    int m_time=500;
};

#endif // MAINWINDOW_H
