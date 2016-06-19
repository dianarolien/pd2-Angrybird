#ifndef BIRD4_H
#define BIRD4_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QMouseEvent>

#define BIRD4_DENSITY 10.0f
#define BIRD4_FRICTION 0.2f
#define BIRD4_RESTITUTION 0.5f

class Bird4 : public GameItem
{
public:
    Bird4(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
};


#endif // BIRD4_H
