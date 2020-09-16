#include "enemy.h"

Enemy::Enemy(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite)
    :QObject(0),_game(game),_sprite(sprite),
      _nowpos(startWayPoint->w_pos),_nextpoint(startWayPoint->w_nextPoint)
{

}

Enemy::~Enemy()
{

}

void Enemy::draw(QPainter *painter) const
{
    if(!_active)
        return;

    painter->save();
    //绘制敌人
    painter->translate(_nowpos);//以路线点为中心
    painter->rotate(_rotation);// 偏转
    painter->drawPixmap(-_fixedSize.width()/2,-_fixedSize.height()/2,_sprite);

    painter->restore();
}

void Enemy::move()
{

    if(!_active)
        return;
    // 敌人抵达了一个航点
    if(judge(_nowpos,_nextpoint->w_pos)){

        // 还有下一个航点
        if (_nextpoint->w_nextPoint)
        {

            _nowpos = _nextpoint->w_pos;
            _nextpoint =_nextpoint->w_nextPoint;
        }
        else
        {
            // 表示进入基地
//            _game->getHpDamage();
//            _game->removedEnemy(this);
            return;
        }
    }
    // 在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = _nextpoint->w_pos;

    // 向量标准化
    QVector2D normalized(targetPoint - _nowpos);  //向量，从现在的点指向下一个路线点
    normalized.normalize();   //normalized取值只有(1,0),(-1,0),(0,-1),(0,1)四种
    _nowpos = _nowpos + normalized.toPoint() *_speed;

    // 确定敌人选择方向
    // 默认图片向左,需要修正180度转右
    _rotation = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) + 180;

}

bool Enemy::judge(QPoint point1, QPoint point2)
{
    int dx=point1.x()-point2.x();
    int dy=point1.y()-point2.y();
    int distance=qSqrt(dx*dx+dy*dy);
    if(distance<2)
        return true;
    return false;

}

void Enemy::doActivate()
{
    _active=true;
}
