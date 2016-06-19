#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QLabel>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <bird2.h>
#include <slingshot.h>
#include <enimy.h>
#include <wood.h>
#include <bird3.h>
#include <bird4.h>
#include <egg.h>
#include <form.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    b2Vec2 calculate(int a, int b);
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void check();
    void time();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer,timer2;
    Bird *bird;
    Bird2 *bird2;
    Enimy *enimy;
    Bird3 *bird3,*bir,*bir2;
    Bird4 *bird4;
    Egg *egg;
    Wood *wood,*wood2,*wood3;
    Form *form;
    QLabel *label2;
    int key,key1,key2,key3,key4;
    int score;
};

#endif // MAINWINDOW_H
