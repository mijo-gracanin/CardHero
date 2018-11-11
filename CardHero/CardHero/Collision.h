#pragma once

#include <SFML/Graphics.hpp>


namespace as
{

    class Collision
    {
    public:
        Collision();

        bool CheckSpriteCollision(sf::Sprite s1,sf::Sprite s2);


    };

}
