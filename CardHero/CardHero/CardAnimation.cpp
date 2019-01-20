//
//  CardAnimation.cpp
//  CardHero
//
//  Created by Mijo Gracanin on 23/11/2018.
//  Copyright © 2018 MijoCoder. All rights reserved.
//

#include "CardAnimation.hpp"
#include <cmath>

namespace as
{
    
    CardAnimation::CardAnimation(Card * const card, sf::Vector2f destinationPoint, float speed):
    m_card(card),
    m_startPoint(card->getPosition()),
    m_destinationPoint(destinationPoint),
    m_speed(speed),
    m_isCompleted(false),
    m_animationType(TRANSITION) {

        float x = m_destinationPoint.x - m_startPoint.x;
        float y = m_destinationPoint.y - m_startPoint.y;
        
        float magnitude = sqrt(x*x + y*y);
        
        if (magnitude == 0) {
            m_directionVector = sf::Vector2f(0, 0);
        }
        float normalised_x = x / magnitude;
        float normalised_y = y / magnitude;
        
        m_directionVector = sf::Vector2f(normalised_x, normalised_y);
    }
    
    CardAnimation::CardAnimation(Card * const card, float flipDuration):
    m_card(card),
    m_flipDuration(flipDuration),
    m_isCompleted(false),
    m_animationType(FLIP) {
        
    }
    
    void CardAnimation::update(float dt) {
        float offset = m_speed * dt;
        float offsetX = m_directionVector.x * offset;
        float offsetY = m_directionVector.y * offset;
        
        sf::Vector2f position = m_card->getPosition();
        
        if (abs(m_destinationPoint.x - position.x) <= abs(offsetX) &&
            abs(m_destinationPoint.y - position.y) <= abs(offsetY)) {
            m_card->setPosition(m_destinationPoint.x, m_destinationPoint.y);
            m_isCompleted = true;
        } else {
            m_card->setPosition(position.x + offsetX, position.y + offsetY);
        }
    }
    
    bool CardAnimation::getIsCompleted() const {
        return m_isCompleted;
    }
}
