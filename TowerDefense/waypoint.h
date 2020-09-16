#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QPoint>
#include <QPainter>

//移动的路线
class WayPoint
{
public:
    //初始构造
    WayPoint(QPoint pos);
    void draw(QPainter *painter) const;//绘制
    void NextWayPoint(WayPoint *nextPoint);//下一个点

    const QPoint  w_pos; //当前点
    WayPoint*  w_nextPoint=NULL;//下一个点
};

#endif // WAYPOINT_H
