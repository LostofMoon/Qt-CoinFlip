#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
private:
    QTimer *timer1 = new QTimer(this);
    QTimer *timer2 = new QTimer(this);
    int min = 1; //最小图片
    int max = 8; //最大图片
    bool isAnimation  = false;
    void mousePressEvent(QMouseEvent *e);

public:
    MyCoin(QString coinImg);
    int posX; //x坐标
    int posY; //y坐标
    bool flag; //正反标志
    void changeFlag(int x = 0);
    bool isWin  = false;
};

#endif // MYCOIN_H
