#include "wood.h"


Wood::Wood(float x, float y, float w, float h, float WOOD_DENSITY,QTimer *timer,QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    type = 7;
    score = 0;
    // Set pixmap
    g_pixmap.setPixmap(pixmap.scaled(w*g_windowsize.width()/g_worldsize.width(),h*g_windowsize.height()/g_worldsize.height()));
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSizeF(w,h);


    // Create body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;
    bodyDef.userData = this;
    bodyDef.position.Set(x,y);
    g_body = world->CreateBody(&bodyDef);
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w/2,h/2);
    b2FixtureDef fixturedef;
    fixturedef.shape = & bodyBox;
    fixturedef.density = WOOD_DENSITY;
    fixturedef.friction = WOOD_FRICTION;
    fixturedef.restitution = WOOD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    scene->addItem(&g_pixmap);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));
    scene->addItem(&g_pixmap);
}

void Wood::addscore()
{
    score = score+100;
}
