#include "waypoint.h"

WayPoint::WayPoint(QPoint pos)
    : w_pos(pos)
{

}

//设置下一个点
void WayPoint::NextWayPoint(WayPoint *nextPoint)
{
    w_nextPoint=nextPoint;
}

//绘制当前点，和下一个点的线
void WayPoint::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::cyan);
    //标记路线点，同心圆
    painter->drawEllipse(w_pos,3,3);
    painter->drawEllipse(w_pos,9,9);
    if(w_nextPoint){
        painter->drawLine(w_pos,w_nextPoint->w_pos);
    }
    painter->restore();
}


