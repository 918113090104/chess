#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadTowerPositions();
    loadWayPoints();
    loadWavesInfo();
    loadWave();

    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateMap()));
    timer->start(30);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//所有的绘制
void MainWindow::paintEvent(QPaintEvent *)
{

    QPixmap cachePix(":/image/Bg.png");  //界面载入背景图片
    QPainter cachePainter(&cachePix);

    //从towerPositionsList中遍历基地的位置,绘制基地
    foreach (const TowerPosition &towerPos,towerPositionsList ) {
        towerPos.draw(&cachePainter);
    }
    //从towersList中遍历塔的位置,绘制塔
    foreach (const Tower *tower, towersList ) {
        tower->draw(&cachePainter);
    }
    //从wayPointsList中遍历路线点,绘制路线
    foreach (const WayPoint *wayPoint, wayPointsList){
        wayPoint->draw(&cachePainter);
    }
    //从wayPointsList中遍历路线点,绘制路线
    foreach (const Enemy *enemy,  enemyList){
        enemy->draw(&cachePainter);
    }

    QPainter painters(this);
    painters.drawPixmap(0,0,cachePix);



}

//点击放塔操作
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint clickPos=event->pos();//获取点击的位置
    auto it=towerPositionsList.begin();
    while(it!=towerPositionsList.end()){
        // 钱够买塔&&点击的位置在范围之内&&该位置是否已经有塔
        if(canBuyTower()&& it->withinPos(clickPos) && !it->hasTower){
            playerGold-=TowerCost;
            it->hasTower=true;
            //画塔
            Tower *tower=new Tower(it->_pos);
            towersList.push_back(tower);
            update();
            break;
        }
        it++;
    }
}


//获得基地的位置(从.plist文件里获取),并存入towerPositionsList
void MainWindow::loadTowerPositions()
{
    QFile file(":/config/TowersPosition.plist");  //打开文件，读取失败则返回失败信息
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"TowerDefense","Cannot Open TowersPosition.plist");
        return;
    }
    PlistReader reader;
    reader.read(&file);//读取文件

    QList<QVariant> array=reader.data();//array存放文件中读取的数据
    foreach (QVariant dict, array) {  //在array中遍历搜索
        QMap<QString,QVariant> point=dict.toMap(); //QMap是一个关联容器，以“键-值”存放
        int x=point.value("x").toInt();
        int y=point.value("y").toInt();
        towerPositionsList.push_back(QPoint(x,y));
    }
    file.close();

}

//金币是否够买塔
bool MainWindow::canBuyTower()
{
    //玩家金币数量够买塔则返回true
    if(playerGold>=TowerCost){
        return true;
    }
    else{
        return false;
    }
}

//设置路线点
void MainWindow::loadWayPoints()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(690, 473));
     wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(58, 473));
     wayPointsList.push_back(wayPoint2);
    wayPoint2->NextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(58, 323));
     wayPointsList.push_back(wayPoint3);
    wayPoint3->NextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(739, 323));
     wayPointsList.push_back(wayPoint4);
    wayPoint4->NextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(425, 167));
     wayPointsList.push_back(wayPoint5);
    wayPoint5->NextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(58, 167));
     wayPointsList.push_back(wayPoint6);
     wayPoint6->NextWayPoint(wayPoint5);
}

//获得攻击波数的信息(从.plist文件里获取
void MainWindow::loadWavesInfo()
{
    QFile file(":/config/Waves.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open Waves.plist");
        return;
    }

    PlistReader reader;
    reader.read(&file);

    // 获取波数信息
     wavesInfo = reader.data();

     file.close();
}

bool MainWindow::loadWave()
{
    if ( waves >=  wavesInfo.size())
        return false;

    WayPoint *startWayPoint =  wayPointsList.back();
    QList<QVariant> curWavesInfo =  wavesInfo[ waves].toList();

    for (int i = 0; i < curWavesInfo.size(); ++i)
    {
        QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
        int spawnTime = dict.value("spawnTime").toInt();

        Enemy *enemy = new Enemy(startWayPoint, this);
        enemyList.push_back(enemy);
        QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
    }

    return true;
}

//地图的更新，敌人移动和塔的转动
void MainWindow::updateMap()
{
    foreach (Enemy *enemy, enemyList) {
        enemy->move();
    }
    update();
}
