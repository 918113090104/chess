 #ifndef TOWER_H
#define TOWER_H
#include <QObject>
#include <QPixmap>
#include <QSize>
#include <QObject>
#include <QPainter>


class Tower : QObject
{
    Q_OBJECT    //用到槽函数的类必须有Q_OBJECT
public:
    Tower(QPoint pos,const QPixmap &sprite=QPixmap(":/image/t.png"));
    void draw(QPainter *painter) const;
    ~Tower();


private:
    QPoint _pos;  //点击的位置对应基地的左上角左边
    QPixmap _sprite;//塔的图片
    QSize _fixedSize=QSize(70,70);//塔的大小
};

#endif // TOWER_H
