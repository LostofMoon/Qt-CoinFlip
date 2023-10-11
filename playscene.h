#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>

class PlayScene : public QMainWindow
{
    Q_OBJECT

private:
    int levalIndex;
    void paintEvent(QPaintEvent *ev);
    int gameArray[4][4];

public:
    PlayScene(int x);
    bool isWin();

signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
