#ifndef ENEMY_H
#define ENEMY_H

#include "waypoint.h"
#include "mainwindow.h"


#include <QObject>
#include <QPoint>
#include <QPainter>
#include <QSize>
#include <QPixmap>
#include <QDebug>
#include <QColor>
#include <QVector2D>
#include <QtMath>

class MainWindow;

class Enemy :public QObject
{
    Q_OBJECT
public:
    Enemy(WayPoint *startWayPoint,MainWindow *game, const QPixmap &sprite=QPixmap(":/image/enemy.png"));
    ~Enemy();


    void draw(QPainter *painter) const;
    void move();
    bool judge(QPoint point1,QPoint point2); //判断敌人是否到达了下一个路线点


public slots:
    void doActivate();


private:
    bool _active=false;//敌人状态，是否产生
    QPoint  _nowpos; //当前路线点的坐标
    WayPoint *  _nextpoint; //移动的下一个路线点的坐标
    MainWindow *  _game;
    const QPixmap  _sprite; //敌人图片
    const QSize  _fixedSize=QSize(86,86); //图片大小
    qreal _rotation=0.0;  //图片偏转的度数
    qreal _speed=1.0; //敌人移动的速度

};

#endif // ENEMY_H
