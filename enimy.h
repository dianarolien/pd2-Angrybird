#ifndef ENIMY_H
#define ENIMY_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QMouseEvent>

#define BIRD_DENSITY 5.0f
#define BIRD_FRICTION 0.2f
#define BIRD_RESTITUTION 0.5f

class Enimy : public GameItem
{
public:
    Enimy(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    int score;
    int key;
    void startContact();
    void startContact2();
};

#endif // ENIMY_H
