//
//  TransitionCardAnimation.hpp
//  CardHero
//
//  Created by Mijo Gracanin on 23/11/2018.
//  Copyright © 2018 MijoCoder. All rights reserved.
//

#ifndef TransitionAnimation_hpp
#define TransitionAnimation_hpp

#include "CardAnimation.h"
#include "Card.hpp"

namespace as
{
    class TransitionCardAnimation: public CardAnimation {
        
    public:
        TransitionCardAnimation(Card * const card, sf::Vector2f destinationPoint, float speed = 800);
        virtual void update(float dt) override;
        virtual bool getIsCompleted() const override;
        
    private:
        Card *m_card;
        sf::Vector2f m_startPoint;
        sf::Vector2f m_destinationPoint;
        sf::Vector2f m_directionVector;
        float m_speed;
        float m_flipDuration;
        bool m_isCompleted;
        void updateTransition(float dt);
        void updateFlip(float dt);
    };
}

#endif /* TransitionCardAnimation_hpp */
