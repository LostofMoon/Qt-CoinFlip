#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
private:
    QString norImg_;
    QString preImg_;

    void SetPicture(QPixmap& x);

public:
    MyPushButton(QString norImg, QString preImg = "");

    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

    void ClickAnimation();

signals:

};

#endif // MYPUSHBUTTON_H
