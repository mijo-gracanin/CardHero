//
//  Card.hpp
//  CardHero
//
//  Created by Mijo Gracanin on 13/11/2018.
//  Copyright © 2018 MijoCoder. All rights reserved.
//

#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

namespace as
{
    enum TraitType {
        HP, MELEE_DAMAGE, MOVEMENT_SPEED, ATACK_SPEED
    };
    
    struct CardTrait {
        TraitType type;
        float value;
    };
    
    class Card : public sf::Drawable {
    
    public:
        Card(CardTrait trait);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    private:
        CardTrait m_trait;
        sf::RectangleShape m_cardShape;
        sf::Text m_cardText;
    };
}

#endif /* Card_hpp */
