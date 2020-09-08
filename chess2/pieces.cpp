#include "pieces.h"

Pieces::Pieces()
{

}

Pieces::~Pieces()
{

}

void Pieces::init(int id)
{
    this->id=id;
    status=true;
    show=false;
    switch (this->id) {
    case 0:
        color=true;//红色
        type=SHUAI;
        break;
    case 1:
        color=true;
        type=SHI;
        break;
    case 2:
        color=true;
        type=SHI;
        break;
    case 3:
        color=true;
        type=XIANG;
        break;
    case 4:
        color=true;
        type=XIANG;
        break;
    case 5:
        color=true;
        type=CHE;
        break;
    case 6:
        color=true;
        type=CHE;
        break;
    case 7:
        color=true;
        type=MA;
        break;
    case 8:
        color=true;
        type=MA;
        break;
    case 9:
        color=true;
        type=PAO;
        break;
    case 10:
        color=true;
        type=PAO;
        break;
    case 11:
        color=true;
        type=BING;
        break;
    case 12:
        color=true;
        type=BING;
        break;
    case 13:
        color=true;
        type=BING;
        break;
    case 14:
        color=true;
        type=BING;
      break;
    case 15:
        color=true;
        type=BING;
        break;
    case 16:
        color=false;//黑色
        type=JIANG;
        break;
    case 17:
        color=false;//黑色
        type=SHI;
        break;
    case 18:
        color=false;//黑色
        type=SHI;
        break;
    case 19:
        color=false;//黑色
        type=XIANG;
        break;
    case 20:
        color=false;//黑色
        type=XIANG;
        break;
    case 21:
        color=false;//黑色
        type=CHE;
        break;
    case 22:
        color=false;//黑色
        type=CHE;
        break;
    case 23:
        color=false;
        type=MA;
        break;
    case 24:
        color=false;
        type=MA;
        break;
    case 25:
        color=false;
        type=PAO;
        break;
    case 26:
        color=false;
        type=PAO;
        break;
    case 27:
        color=false;
        type=ZU;
        break;
    case 28:
        color=false;
        type=ZU;
       break;
    case 29:
        color=false;
        type=ZU;
        break;
    case 30:
        color=false;
        type=ZU;
        break;
    case 31:
        color=false;
        type=ZU;
        break;
    }


}

QString Pieces::getstring()
{
    switch (this->type) {
    case JIANG:
        return "将";
    case SHUAI:
        return "帅";
    case SHI:
        if(this->color){
            return "仕";
        }
        else {
            return "士";
        }
    case XIANG:
        if(this->color){
            return "相";
        }
        else{
            return "象";
        }
    case CHE:
        return "车";
    case MA:
        return "马";
    case PAO:
        return "炮";
    case BING:
        return "兵";
    case ZU:
        return "卒";

    }
    return "false";
}



