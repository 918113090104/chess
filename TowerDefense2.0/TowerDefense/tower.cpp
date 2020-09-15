#include "tower.h"

Tower::Tower(QPoint pos, const QPixmap &sprite)
    :_pos(pos),_sprite(sprite)

{

}

void Tower::draw(QPainter *painter) const
{
    painter->drawPixmap(_pos,_sprite);
}

Tower::~Tower()
{

}
