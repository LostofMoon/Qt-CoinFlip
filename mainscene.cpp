#include "mainscene.h"
#include "mypushbutton.h"
#include <QAction>
#include <QPainter>
#include <QMenuBar>
#include <QMenu>
#include <QTimer>
#include <QDebug>
#include <QSound>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(320*2, 580*2);
    setWindowIcon(QPixmap(":/res/Coin0001.png"));
    setWindowTitle("老帮主带你翻金币");

    //创建菜单栏
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
    //创建按钮菜单项
    QAction * quitAction = startMenu->addAction("退出");
    //点击退出 退出游戏
    connect(quitAction,&QAction::triggered,[=](){this->close();});

//---------------------------------------------------------------------------------------------------------------

    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    QSound *startSound = new QSound(":/res/TapButtonSound.wav",this);

    chooselevelscene_ = new ChooseLevelScene;

    connect(startBtn, &QPushButton::clicked, [=](){
        startBtn->ClickAnimation();
        startSound->play();
        //100ms后this触发函数
        QTimer::singleShot(100, this, [=](){
            this->hide();
            chooselevelscene_->setGeometry(this->geometry());
            chooselevelscene_->show();
        });
    });

    connect(chooselevelscene_, &ChooseLevelScene::BackToMain,[=](){
        chooselevelscene_->close();
        this->setGeometry(chooselevelscene_->geometry());
        show();
    });
}

//---------------------------------------------------------------------------------------------------------------

void MainScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,width(), height(), pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);
}

MainScene::~MainScene()
{
    delete ui;
}

