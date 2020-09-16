#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "plistreader.h"
#include "towerposition.h"
#include "tower.h"
#include "waypoint.h"
#include "enemy.h"
#include <QMainWindow>
#include <QXmlStreamReader>
#include <QPainter>
#include <QFile>
#include <QMessageBox>
#include <QMouseEvent>
#include <QTimer>
//#include <QtGlobal>

class Enemy;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *); //所有绘制
    void mousePressEvent(QMouseEvent *); //鼠标点击放置塔


    void loadTowerPositions();//获取基地的位置,将基地位置存入towerPositionsList列表
    bool canBuyTower();

    void loadWayPoints();//获取路线点的位置，存入wayPointsList列表

    void loadWavesInfo();//获取攻击波数信息
    bool loadWave();//将获得的波数信息存入enemyList列表

private slots:
    void updateMap(); //地图更新，敌人的移动，塔的转动等

private:
    Ui::MainWindow *ui;
    QList<TowerPosition> towerPositionsList; //数组列表，存储塔的位置
    QList<Tower *>	  towersList; //数组列表，塔
    QList<WayPoint *>  wayPointsList;//数组列表，路线点
    QList<Enemy *>   enemyList; //数组列表，敌人
    QList<QVariant>  wavesInfo;//数组列表，攻击波数信息


    const int TowerCost=300; //一个塔需要的金币数
    int playerGold=1000;//玩家的金币数，初始为1000
    int waves=0;//当前攻击的波数

};

#endif // MAINWINDOW_H
