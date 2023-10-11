#include "playscene.h"
#include <QMenuBar>
#include <QMenu>
#include <QPainter>
#include <QDebug>
#include <mypushbutton.h>
#include <mycoin.h>
#include <QTimer>
#include <QLabel>
#include <QPropertyAnimation>
#include <dataconfig.h>
#include <QSound>


PlayScene::PlayScene(int x):levalIndex(x) {
    //设置窗口固定大小
    this->setFixedSize(320*2,580*2);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币");

    //创建菜单栏
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
    //创建按钮菜单项
    QAction * quitAction = startMenu->addAction("退出");
    //点击退出 退出游戏
    connect(quitAction,&QAction::triggered,[=](){this->close();});

    //返回按钮
    MyPushButton * closeBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    closeBtn->setParent(this);
    closeBtn->move(this->width()-closeBtn->width(),this->height()-closeBtn->height());

    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);

    //返回按钮功能实现
    connect(closeBtn,&MyPushButton::clicked,[=](){
        backSound->play();
        QTimer::singleShot(100, this,[=](){
            this->hide();
            //触发自定义信号，关闭自身，该信号写到 signals下做声明
            emit this->chooseSceneBack();
        });
    });

    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(40);
    label->setFont(font);
    QString str = QString("Leavel: %1").arg(this->levalIndex);
    label->setText(str);
    label->setGeometry(40, this->height() - 100, 400, 100); //设置大小和位置

//-------------------------------------------------------------------------------------------------
    dataConfig config;
    for(int i = 0 ; i < 4;i++)
        for(int j = 0 ; j < 4; j++)
            gameArray[i][j] = config.mData[this->levalIndex][i][j];

    MyCoin *coin[4][4];
    //创建金币的背景图片
    for(int i = 0 ; i < 4;i++) {
        for(int j = 0 ; j < 4; j++) {
            //绘制背景图片
            QLabel* label = new QLabel;
            label->setParent(this);

            QPixmap pix = QPixmap(":/res/BoardNode.png");
            pix = pix.scaled(pix.width()*2,pix.height()*2);
            label->setPixmap(pix);
            label->move(114 + i*100,400+j*100);
            label->setFixedSize(100, 100);

            //金币对象
            QString img;
            if(gameArray[i][j] == 1)
                img = ":/res/Coin0001.png";
            else img = ":/res/Coin0008.png";

            coin[i][j] = new MyCoin(img);
            coin[i][j]->setParent(this);
            coin[i][j]->move(59*2+i*100,204*2+j*100);

            coin[i][j]->posX = i; //记录x坐标
            coin[i][j]->posY = j; //记录y坐标
            coin[i][j]->flag =gameArray[i][j]; //记录正反标志
        }
    }

    QLabel* winLabel = new QLabel;
    winLabel->setParent(this);
    QPixmap temp;
    temp.load(":/res/LevelCompletedDialogBg.png");
    temp = temp.scaled(temp.width() * 2, temp.height() * 2);
    winLabel->setPixmap(temp);
    winLabel->move( (this->width() - temp.width())*0.5 , -temp.height());
    winLabel->setFixedSize(temp.width(), temp.height());

    for(int i = 0 ; i < 4;i++)
        for(int j = 0 ; j < 4; j++)
            connect(coin[i][j],&MyCoin::clicked,[=](){
                gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0;
                coin[i][j]->changeFlag();
                if(i > 0){
                    gameArray[i-1][j] = gameArray[i-1][j] == 0 ? 1 : 0;
                    coin[i-1][j]->changeFlag(300);
                }
                if(i < 3){
                    gameArray[i+1][j] = gameArray[i+1][j] == 0 ? 1 : 0;
                    coin[i+1][j]->changeFlag(300);
                }
                if(j > 0){
                    gameArray[i][j-1] = gameArray[i][j-1] == 0 ? 1 : 0;
                    coin[i][j-1]->changeFlag(300);
                }
                if(j < 3){
                    gameArray[i][j+1] = gameArray[i][j+1] == 0 ? 1 : 0;
                    coin[i][j+1]->changeFlag(300);
                }
                QTimer::singleShot(420, this,[=](){
                if(isWin()){
                    QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);
                    winSound->play();
                    for(int i = 0 ; i < 4;i++)
                        for(int j = 0 ; j < 4; j++)
                            coin[i][j]->isWin = true;
                   QPropertyAnimation *animation1 = new QPropertyAnimation(winLabel,"geometry");
                   animation1->setDuration(1000);
                   animation1->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                   animation1->setEndValue(QRect(winLabel->x(),winLabel->y()+228,winLabel->width(),winLabel->height()));
                   animation1->setEasingCurve(QEasingCurve::OutBounce);
                   animation1->start();
                }
                });
            });
}

void PlayScene::paintEvent(QPaintEvent *) {
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);
}

bool PlayScene::isWin() {
    for(int i = 0 ; i < 4;i++)
        for(int j = 0 ; j < 4; j++){
            //qDebug() << gameArray[i][j];
            if(gameArray[i][j] == 0)
                return false;
        }
    return true;
}
