#include "waypoint.h"

WayPoint::WayPoint(QPoint pos)
    : _pos(pos)
{

}

//设置下一个点
void WayPoint::NextWayPoint(WayPoint *nextPoint)
{
    _nextPoint=nextPoint;
}

//绘制当前点，和下一个点的线
void WayPoint::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::cyan);
    //标记路线点，同心圆
    painter->drawEllipse(_pos,3,3);
    painter->drawEllipse(_pos,9,9);
    if(_nextPoint){
        painter->drawLine(_pos,_nextPoint->_pos);
    }
    painter->restore();
}


