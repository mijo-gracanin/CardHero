#include "Collision.h"

namespace as
{
    Collision::Collision()
    {

    }
    //this is a basic Collision System.It depends of Sprite scale that involves sprites intersection
    bool Collision::CheckSpriteCollision(sf::Sprite s1,sf::Sprite s2)
    {
        sf::Rect<float> rect1=s1.getGlobalBounds();
        sf::Rect<float> rect2=s2.getGlobalBounds();


        if(rect1.intersects(rect2))
        {
            return true;
        }
        else
        {
            return false;
        }

    }
}
