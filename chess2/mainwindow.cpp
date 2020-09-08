#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
   //初识化棋盘上棋子的随机排列
   for(int i=0;i<32;i++){
      p[i].init(i);   //初始棋子的id，color，type,status
      int m=qrand()%4;
      int n=qrand()%8;
      int j;
      for( j=0;j<i;j++){    //判断是否与前面的棋子位置一样
          if(p[j].row==m&&p[j].col==n){
              break;
          }
      }
      if(j==i){  //棋子与前面棋子不一样，则进行初始赋值row,col
          p[i].row=m;
          p[i].col=n;
      }
      else{
          i--;
          continue;
      }
   }
   //初始flag[32]
   for(int i=0;i<32;i++){
       flag[i]=-1;
   }

}
MainWindow::~MainWindow()
{
    delete ui;

}

//画棋盘
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painters(this);
    this->x=70;//每格的边长
    //画10条横线
     for(int i=0;i<10;i++){
        painters.drawLine(QPoint(60,60+i*x),QPoint(8*x+60,60+i*x)); //设第一个起始位置为（60,60）
     }
    //画竖线
    for(int i=0;i<9;i++){
        if(i==0||i==8)
            painters.drawLine(QPoint(60+i*x,60),QPoint(60+i*x,60+9*x)); //棋盘的第一条线和最后一条竖线是直接一条
        else{
            //第五行中间无竖线
            painters.drawLine(QPoint(60+i*x,60),QPoint(60+i*x,60+x*4));//1到4格竖线
            painters.drawLine(QPoint(60+i*x,60+5*x),QPoint(60+i*x,60+9*x));//5到9竖线
        }
    }
    //九宫格
    painters.drawLine(QPoint(60+x*3,60),QPoint(60+x*5,60+x*2));
    painters.drawLine(QPoint(60+x*5,60),QPoint(60+x*3,60+x*2));
    painters.drawLine(QPoint(60+x*3,60+x*7),QPoint(60+x*5,60+x*9));
    painters.drawLine(QPoint(60+x*5,60+x*7),QPoint(60+x*3,60+x*9));

    //画32颗棋子
    for(int i=0;i<32;i++){
       drawPieces(painters,i);       //画棋子的函数
    }



}


//画棋子
void MainWindow::drawPieces(QPainter& painters, int id)
{

    //设置棋子的背景颜色，要是棋子未选中，则设置为棕色，选中了的棋子为黄色
    if(id==before){
        painters.setBrush(QBrush(QColor(241,247,153)));
    }
    else{
        painters.setBrush(QBrush(QColor(238,205,162)));
    }
    painters.setPen(Qt::black);//黑笔画圆圈
    painters.drawEllipse(QPoint(95+x*p[id].col,95+x*p[id].row),x/2,x/2);//画圆
    painters.setFont(QFont("隶书",30,50,false));//设置棋子的字体大小粗细
    if(p[id].color)
        painters.setPen(Qt::red);//红方就设字体为红色
    QRect rect=QRect(p[id].col*x+60,p[id].row*x+60,x,x);
    for(int j=0;j<32;j++){
       if(id==flag[j]){
          painters.drawText(rect,p[id].getstring(),QTextOption(Qt::AlignCenter));//写字
        }
    }
}

//走棋
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
      QPoint ps=event->pos();
    //将点ps转化为行列；
       int row0,col0;//本次鼠标点击的位置
       bool t=getRowCol(ps,row0,col0);
       if(t==false)
           return;
       //找到当前点击的位置对应的棋子ID
       int now=-1;
       int i;
       //翻棋
       for( i=0;i<32;i++){
          if(p[i].row==row0 && p[i].col==col0 && p[i].status&&!p[i].show){
             break;
          }
       }
       if(i<32){
           if(before!=-1){ //如果上一次点击的是翻过的棋子，则这次不能点击未翻过的
               before=-1;
               update();
           }
           else{
               flag[count++]=i;
               p[i].show=true;
               update();
           }
       }
       //不翻棋，移动棋子
       if(i==32){
           for( i=0;i<32;i++){
              if(p[i].row==row0 && p[i].col==col0 && p[i].status&&p[i].show){
                now=i;
                break;
              }
           }
           if(before==-1){
               if(now!=-1){
                   before=now;
                   update();
               }
           }
           else{
               if(movement(before,row0,col0,now)){
                   p[before].row=row0;
                   p[before].col=col0;
                   if(now!=-1){
                       p[now].status=false;
                       if(p[now].color){
                           if(r_col==8){
                               p[now].row=6;
                               p[now].col=6;
                           }
                           else {
                               p[now].row=5;
                               p[now].col=r_col++;
                           }

                       }
                       else {
                           if(b_col==8){
                               p[now].row=8;
                               p[now].col=(b_col++)%8;
                           }
                           else {
                               p[now].row=7;
                               p[now].col=b_col++;
                          }
                       }

                  }
                  before=-1;
                  update();
               }
           }
       }//endif(!dose)


}
bool MainWindow::getRowCol(QPoint ps, int &row, int &col)
{
    float r=(ps.ry()-60)/70.0;
    float c=(ps.rx()-60)/70.0;
    int i=qFloor(r);
    int j=qFloor(c);
    float dx=r-i-0.5;
    float dy=c-j-0.5;
    float dist=qSqrt(dx*dx+dy*dy);
    if(dist<0.5){
        row=i;
        col=j;
        return true;
    }
    return false;

}

bool MainWindow::movement(int before1, int row1, int col1, int now1)
{
    //只能在上面移动
    if(row1>3){
        before=-1;
        update();
        return false;
    }
    //只能吃对方的棋子
    if(p[before1].color==p[now1].color){
        if(p[before1].id!=p[now1].id){
            before=now1;
        }
        else {
            before=-1;

        }
        update();
        return false;
    }
    /* 走棋规则：
       帅（将）：帅和将可以吃除兵和卒以外的任何棋子。
       仕（士）：仕（士）可以吃除帅和将以外的任何棋子。
       相（象）：相（象）可以吃除仕，士，帅和将以外的任何棋子。
       车：可以吃除相，象，仕，士，帅和将以外的任何棋子。
       马：可以吃炮，兵或卒。
       炮：可以吃除马外的任何棋子，但是中间必须隔一个子。
       兵（卒）：只能吃对方的帅（将）。
       除炮在吃子时可以按竖线或横线走动多格，其他子每次走动只能按竖线或横线走动一格。
     */
    switch (p[before1].type) {
    case Pieces::SHUAI:
           return shuai(before1,row1,col1,now1);
            break;
        case Pieces::JIANG:
           return jiang(before1,row1,col1,now1);
            break;
        case Pieces::SHI:
            return shi(before1,row1,col1,now1);
            break;
        case Pieces::XIANG:
            return xiang(before1,row1,col1,now1);
            break;
        case Pieces::CHE:
            return che(before1,row1,col1,now1);
            break;
        case Pieces::MA:
            return ma(before1,row1,col1,now1);
            break;
        case Pieces::PAO:
            return pao(before1,row1,col1,now1);
            break;
        case Pieces::BING:
            return bing(before1,row1,col1,now1);
            break;
        case Pieces::ZU:
            return zu(before1,row1,col1,now1);
            break;

    }
    return true;//前面都没问题，则返回true
}

bool MainWindow::shuai(int before2, int row2, int col2, int now2)
{
    //只能走一格
    if(abs(p[before2].row-row2)>1||abs(p[before2].col-col2)>1){
        before=-1;
        update();
        return false;
    }
    //只能横着或竖着走
    if( abs(p[before2].row-row2) == abs(p[before2].col-col2) ){
        before=-1;
        update();
        return false;
    }
    //帅：帅可以吃对方除卒以外的任何棋子。
    if(p[now2].type==Pieces::ZU){
        before=-1;
        update();
        return false;
    }
    return true;
}

bool MainWindow::jiang(int before2, int row2, int col2, int now2)
{
    //只能走一格
    if(abs(p[before2].row-row2)>1||abs(p[before2].col-col2)>1){
        before=-1;
        update();
        return false;
    }
    //只能横着或竖着走
    if( abs(p[before2].row-row2) == abs(p[before2].col-col2) ){
        before=-1;
        update();
        return false;
    }
    //now是空位置的话可以这里直接返回了
    if(now2==-1){
        return true;
    }
    //将：将可以吃对方除兵以外的任何棋子。
    if(p[now2].type==Pieces::BING){
        before=-1;
        update();
        return false;
    }
    return true;
}

bool MainWindow::shi(int before2, int row2, int col2, int now2)
{  //只能走一格
    if(abs(p[before2].row-row2)>1||abs(p[before2].col-col2)>1){
        before=-1;
        update();
        return false;
    }
    //只能横着或竖着走
    if( abs(p[before2].row-row2) == abs(p[before2].col-col2) ){
        before=-1;
        update();
        return false;
    }
    //now是空位置的话可以这里直接返回了
    if(now2==-1){
        return true;
    }
    //仕（士）：仕（士）可以吃除帅和将以外的任何棋子。
    if(p[now2].type==Pieces::JIANG || p[now2].type==Pieces::SHUAI){
        before=-1;
        update();
        return false;
    }
    return true;
}

bool MainWindow::xiang(int before2, int row2, int col2, int now2)
{  //只能走一格
    if(abs(p[before2].row-row2)>1||abs(p[before2].col-col2)>1){
        before=-1;
        update();
        return false;
    }
    //只能横着或竖着走
    if( abs(p[before2].row-row2) == abs(p[before2].col-col2) ){
        before=-1;
        update();
        return false;
    }
    //now是空位置的话可以这里直接返回了
    if(now2==-1){
        return true;
    }
    //相（象）：相（象）可以吃除仕，士，帅和将以外的任何棋子。
    if(p[now2].type==Pieces::JIANG || p[now2].type==Pieces::SHUAI || p[now2].type==Pieces::SHI){
        before=-1;
        update();
        return false;
    }

    return true;
}

bool MainWindow::che(int before2, int row2, int col2, int now2)
{
      //只能走一格
     if(abs(p[before2].row-row2)>1||abs(p[before2].col-col2)>1){
           before=-1;
           update();
           return false;
      }
      //只能横着或竖着走
     if( abs(p[before2].row-row2) == abs(p[before2].col-col2) ){
           before=-1;
           update();
           return false;
     }
     //now是空位置的话可以这里直接返回了
     if(now2==-1){
         return true;
     }
     //车：可以吃除相，象，仕，士，帅和将以外的任何棋子。
     if(p[now2].type==Pieces::JIANG || p[now2].type==Pieces::SHUAI || p[now2].type==Pieces::SHI || p[now2].type==Pieces::XIANG){
         before=-1;
         update();
         return false;
     }

    return true;
}

bool MainWindow::ma(int before2, int row2, int col2, int now2)
{
    //只能走一格
   if(abs(p[before2].row-row2)>1||abs(p[before2].col-col2)>1){
         before=-1;
         update();
         return false;
    }
    //只能横着或竖着走
   if( abs(p[before2].row-row2) == abs(p[before2].col-col2) ){
         before=-1;
         update();
         return false;
   }
   //now是空位置的话可以这里直接返回了
   if(now2==-1){
       return true;
   }
   //马：可以吃炮，兵或卒。
   if( p[now2].type==Pieces::MA ||p[now2].type==Pieces::PAO || p[now2].type==Pieces::BING || p[now2].type==Pieces::ZU){
        return true;
   }
   else {
       before=-1;
       update();
       return false;
   }
    return true;
}

bool MainWindow::pao(int before2, int row2, int col2, int now2)
{
    //炮在吃子时可以按竖线或横线走动多格
    if( p[before2].row-row2 && p[before2].col-col2){ //if dx和dy都不为0,则说明没按竖线和横线走
        before=-1;
        update();
        return false;
    }
    //当now点击的是空位置，则在这里提前返回ture,因为后炮走棋要判断是否隔一个子，会影响空位置结果
    if(now2==-1){
        return true;
    }
    //炮：可以吃除马外的任何棋子，
    if(p[now2].type==Pieces::MA){
        before=-1;
        update();
        return false;
    }
    //但是中间必须隔一个子
    if( (abs(p[before2].row-row2)*10+abs(p[before2].col-col2))==20 ||  (abs(p[before2].row-row2)*10+abs(p[before2].col-col2))==2){
        return true;
    }
    else {
       before=-1;
       update();
       return false;
    }
    return true;
}

bool MainWindow::bing(int before2, int row2, int col2, int now2)
{
    //只能走一格
   if(abs(p[before2].row-row2)>1||abs(p[before2].col-col2)>1){
         before=-1;
         update();
         return false;
    }
    //只能横着或竖着走
   if( abs(p[before2].row-row2) == abs(p[before2].col-col2) ){
         before=-1;
         update();
         return false;
   }
   //now是空位置的话可以这里直接返回了
   if(now2==-1){
       return true;
   }
   // 兵：只能吃对方的将。
   if(p[now2].type!=Pieces::JIANG){
       before=-1;
       update();
       return false;
   }
    return true;
}

bool MainWindow::zu(int before2, int row2, int col2, int now2)
{
    //只能走一格
   if(abs(p[before2].row-row2)>1||abs(p[before2].col-col2)>1){
         before=-1;
         update();
         return false;
    }
    //只能横着或竖着走
   if( abs(p[before2].row-row2) == abs(p[before2].col-col2) ){
         before=-1;
         update();
         return false;
   }
   //now是空位置的话可以这里直接返回了
   if(now2==-1){
       return true;
   }
   // 卒：只能吃对方的帅。
   if(p[now2].type!=Pieces::SHUAI){
           before=-1;
           update();
           return false;
   }
    return true;
}








