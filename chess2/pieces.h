#ifndef PIECES_H
#define PIECES_H

#include <QString>
class Pieces
{
public:
    Pieces();
    ~Pieces();

    int row;//行
    int col;//列
    int id;//标识每颗棋子
    bool color;//颜色（红色为ture,黑色为false）
    bool status;//棋子的状态，被吃掉为false
    bool show;//棋子是否被翻开
    /*  红：  帅，仕，相，车，马，炮，兵
        黑：  将，士，象，车，马，炮，卒
   */
    enum TYPE{SHUAI, JIANG, SHI, XIANG, CHE, MA, PAO, BING,ZU};
    TYPE type;//棋子的类型

    void init(int id);

    QString getstring();

};

#endif // PIECES_H
