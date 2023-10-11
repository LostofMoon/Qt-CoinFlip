#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

MyPushButton::MyPushButton(QString norImg, QString preImg)
    :norImg_(norImg),preImg_(preImg) {

    QPixmap map;
    bool flag = map.load(norImg_);
    if(!flag){
        qDebug() << norImg_ << "加载图片失败!";
        return;
    }
    map = map.scaled(map.width()*2,map.height()*2);//图片拉伸

    SetPicture(map);
}

void MyPushButton::ClickAnimation(){

    QPropertyAnimation * animation1 = new QPropertyAnimation(this,"geometry");
    animation1->setDuration(200);
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation1->setEasingCurve(QEasingCurve::OutBounce);


    QPropertyAnimation * animation2 = new QPropertyAnimation(this,"geometry");
    animation2->setDuration(200);
    animation2->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation2->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation2->setEasingCurve(QEasingCurve::OutBounce);

    animation1->start();
    animation2->start();
}

void MyPushButton::SetPicture(QPixmap& map){
    setFixedSize(map.width(), map.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    setIcon(map);
    this->setIconSize(QSize(map.width(),map.height()));
}

void MyPushButton::mousePressEvent(QMouseEvent *ev){
    if(preImg_ == nullptr) return QPushButton::mousePressEvent(ev);

    QPixmap map;
    map.load(preImg_);
    map = map.scaled(map.width()*2,map.height()*2);//图片拉伸
    SetPicture(map);
    return QPushButton::mousePressEvent(ev);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *ev){
    if(preImg_ == nullptr) return QPushButton::mouseReleaseEvent(ev);

    QPixmap map;
    map.load(norImg_);
    map = map.scaled(map.width()*2,map.height()*2);//图片拉伸
    SetPicture(map);
    return QPushButton::mouseReleaseEvent(ev);
}
