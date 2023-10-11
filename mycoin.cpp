#include "mycoin.h"
#include <QDebug>
#include <QSound>

MyCoin::MyCoin(QString coinImg){
    QPixmap pixmap;
    bool flag = pixmap.load(coinImg);
    if(!flag){
        qDebug() << coinImg << "加载图片失败!";
        return;
    }

    pixmap = pixmap.scaled(pixmap.width() * 2, pixmap.height() * 2);
    this->setFixedSize( pixmap.width(), pixmap.height() );
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));

    //监听正面翻转的信号槽
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pixmap.load(str);

        pixmap = pixmap.scaled(pixmap.width() * 2, pixmap.height() * 2);

        this->setFixedSize(pixmap.width(),pixmap.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        if(this->min > this->max) //如果大于最大值，重置最小值，并停止定时器
        {
            this->min = 1;
            this->isAnimation  = false;
            timer1->stop();
        }
    });

    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg((this->max)-- );
        pixmap.load(str);

        pixmap = pixmap.scaled(pixmap.width() * 2, pixmap.height() * 2);

        this->setFixedSize(pixmap.width(),pixmap.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        if(this->max < this->min) //如果小于最小值，重置最大值，并停止定时器
        {
            this->max = 8;
            this->isAnimation  = false;
            timer2->stop();
        }
    });


}

void MyCoin::changeFlag(int x){
    this->isAnimation  = true;
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    flipSound->play();
    QTimer::singleShot(x, this,[=](){
    if(this->flag) {
        timer1->start(30);
        this->flag = false;
    }
    else {
        timer2->start(30);
        this->flag = true;
    }
    });
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(isAnimation || isWin) return;
    else return QPushButton::mousePressEvent(e);
}
