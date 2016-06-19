#include "mycontactlistener.h"
#include "egg.h"
#include "enimy.h"
#include "bird.h"
#include "wood.h"

#include <iostream>

MyContactListener::MyContactListener()
{

}

void MyContactListener::BeginContact(b2Contact *contact)
{
    GameItem* a = static_cast<GameItem*>(contact->GetFixtureA()->GetBody()->GetUserData());
    GameItem* b = static_cast<GameItem*>(contact->GetFixtureB()->GetBody()->GetUserData());

    //check if fixture A was an egg
    if ( a->type == 5 && b->type == 6 )
    {
        static_cast<Enimy*>( b )->startContact();
        std::cout << "OK" << endl;
    }
    if ( b->type == 5 && a->type == 6 )
    {
        static_cast<Enimy*>( a )->startContact();
        std::cout << "OK" << endl;
    }
    if (a->type == 7 && b->type !=7 )
    {
        static_cast<Wood*>(a)->addscore();
    }
    if (b->type == 7 && a->type !=7 )
    {
        static_cast<Wood*>(b)->addscore();
    }



}

void MyContactListener::EndContact(b2Contact *contact)
{
    //check if fixture A was a ball
  //  void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
   // if ( bodyUserData == typeid(Egg) )
    //    static_cast<Egg*>( bodyUserData )->endContact();
    //check if fixture B was a ball
   // bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    //if ( bodyUserData )
     //   static_cast<Ball*>( bodyUserData )->endContact();
}
