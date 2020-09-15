#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "plistreader.h"
#include "towerposition.h"
#include "tower.h"
#include "waypoint.h"
#include <QMainWindow>
#include <QXmlStreamReader>
#include <QPainter>
#include <QFile>
#include <QMessageBox>
#include <QMouseEvent>
//#include <QtGlobal>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

    void loadTowerPositions();//获取基地的位置,将基地位置存入towerPositionsList列表
    bool canBuyTower();

    void loadWayPoints();//获取路线点的位置，存入wayPointsList列表


private:
    Ui::MainWindow *ui;
    QList<TowerPosition> towerPositionsList; //数组列表，存储塔的位置
    QList<Tower *>	  towersList; //数组列表，塔
    QList<WayPoint *> wayPointsList  ;//数组列表，路线点

    const int TowerCost=300; //一个塔需要的金币数
    int playerGold=1000;//玩家的金币数，初始为1000

};

#endif // MAINWINDOW_H
