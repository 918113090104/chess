#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H
#include <QPoint>
#include <QPainter>
#include <QPixmap>
#include <QSize>

class TowerPosition
{
public:
    //初始构造
    TowerPosition(QPoint pos,const QPixmap &sprite= QPixmap(":/image/open.png"));
    void draw(QPainter *painter) const ;   //绘制塔所在的基地

    bool withinPos(QPoint &pos);

    bool hasTower=false;//标记该基地是否有塔，初始为false



    QPixmap _sprite;
    QPoint  _pos;  //基地的位置（x,y）左上角坐标
    static const QSize fixedSize; //基地大小




};

#endif // TOWERPOSITION_H
