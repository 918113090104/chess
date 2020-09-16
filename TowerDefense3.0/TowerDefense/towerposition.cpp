#include "towerposition.h"


const QSize TowerPosition::fixedSize(73.3,73.3);

TowerPosition::TowerPosition(QPoint pos, const QPixmap &sprite)
    : _pos(pos),_sprite(sprite)
{

}

void TowerPosition::draw(QPainter *painter) const
{
    painter->drawPixmap(_pos.x(),_pos.y(),_sprite);   //绘制基地
}

bool TowerPosition::withinPos(QPoint &pos)
{
    //判断鼠标点击的位置是否在基地范围之内
    bool click_x= _pos.x()<pos.x() && pos.x()< (_pos.x()+fixedSize.width());
    bool click_y= _pos.y()<pos.y() && pos.y()< (_pos.y()+fixedSize.height());
    return click_x&&click_y;
}

