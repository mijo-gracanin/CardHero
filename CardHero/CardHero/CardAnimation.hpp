//
//  CardAnimation.hpp
//  CardHero
//
//  Created by Mijo Gracanin on 23/11/2018.
//  Copyright © 2018 MijoCoder. All rights reserved.
//

#ifndef CardAnimation_hpp
#define CardAnimation_hpp

#include <stdio.h>
#include "Card.hpp"

namespace as
{
    enum CardAnimationType {
        TRANSITION, FLIP
    };
    
    
    class CardAnimation {
        
    public:
        CardAnimation(Card * const card, sf::Vector2f destinationPoint, float speed = 1000);
        CardAnimation(Card * const card, float flipDuration);
        void update(float dt);
        bool getIsCompleted() const;
        
    private:
        Card *m_card;
        sf::Vector2f m_startPoint;
        sf::Vector2f m_destinationPoint;
        sf::Vector2f m_directionVector;
        float m_speed;
        float m_flipDuration;
        CardAnimationType m_animationType;
        bool m_isCompleted;
    };
}

#endif /* CardAnimation_hpp */
