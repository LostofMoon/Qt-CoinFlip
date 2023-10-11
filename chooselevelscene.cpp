#include "chooselevelscene.h"
#include <QMenuBar>
#include <QMenu>
#include <QPainter>
#include <mypushbutton.h>
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QSound>

ChooseLevelScene::ChooseLevelScene() {
    setFixedSize(320*2, 580*2);
    setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    setWindowTitle("选择关卡");

    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);

    QMenu * startMenu = bar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){this->close();});

//---------------------------------------------------------------------------------------------------------------

    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);

    MyPushButton * closeBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    closeBtn->setParent(this);
    closeBtn->move(this->width()-closeBtn->width(),this->height()-closeBtn->height());

    connect(closeBtn, &QPushButton::clicked,[=](){
        QTimer::singleShot(100, this, [=](){
            backSound->play();
            emit this->BackToMain();
        });
    });

//---------------------------------------------------------------------------------------------------------------

    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);

    for(int i = 0 ; i < 20;i++) {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(50 + (i%4)*140 , 260+ (i/4)*140);

        connect(menuBtn,&MyPushButton::clicked,[=](){
            // qDebug() << "select: " << i;
            if(pScene == NULL){//游戏场景最好不用复用，直接移除掉创建新的场景
                this->hide();
                pScene = new PlayScene(i+1); //将选择的关卡号 传入给PlayerScene
                chooseSound->play();
                pScene->setGeometry(this->geometry());
                pScene->show();

                connect(pScene,&PlayScene::chooseSceneBack,[=](){
                    this->setGeometry(pScene->geometry());
                    this->show();
                    delete pScene;
                    pScene = NULL;
                });

            }
        });

//---------------------------------------------------------------------------------------------------------------

        //按钮上显示的文字
        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());

        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //设置居中

        label->move(50 + (i%4)*140 , 260+ (i/4)*140);
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true);  //鼠标事件穿透
    }

}

//---------------------------------------------------------------------------------------------------------------

void ChooseLevelScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,width(), height(), pix);

    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*2,pix.height()*2);
    painter.drawPixmap( (this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);

}
