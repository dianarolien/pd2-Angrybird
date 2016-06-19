#ifndef WOOD_H
#define WOOD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QMouseEvent>


#define WOOD_FRICTION 0.5f
#define WOOD_RESTITUTION 0.5f

class Wood: public GameItem
{
public:
    Wood(float x, float y, float w, float h,float WOOD_DENSITY, QTimer *timer,QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void addscore();
    int score;
};

#endif // WOOD_H
