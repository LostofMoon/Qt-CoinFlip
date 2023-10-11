#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include <playscene.h>


class ChooseLevelScene : public QMainWindow {
    Q_OBJECT
private:
    void paintEvent(QPaintEvent *);

    PlayScene *pScene = nullptr;

public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

signals:
    void BackToMain();
};

#endif // CHOOSELEVELSCENE_H
