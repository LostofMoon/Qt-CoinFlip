#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <chooselevelscene.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT
private:
    ChooseLevelScene *chooselevelscene_ = nullptr;
    void paintEvent(QPaintEvent *);

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
