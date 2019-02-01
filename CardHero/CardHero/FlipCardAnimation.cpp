//
//  FlipCardAnimation.cpp
//  CardHero
//
//  Created by Mijo Gracanin on 20/01/2019.
//  Copyright © 2019 MijoCoder. All rights reserved.
//

#include "FlipCardAnimation.hpp"
#include <algorithm>


namespace as {
    
    FlipCardAnimation::FlipCardAnimation(Card * const card, float flipDuration):
    m_card(card),
    m_flipDuration(flipDuration),
    m_isCompleted(false),
    m_isInitialyRevealed(card->getIsRevealed()),
    m_passedTime(0) {
        
    }
    
    void FlipCardAnimation::update(float dt) {
        m_passedTime += dt;
        
        float halfDuration = m_flipDuration / 2;
        
        if (m_passedTime > halfDuration) {
            if (m_isInitialyRevealed == m_card->getIsRevealed()) {
                m_card->setIsRevealed(!m_isInitialyRevealed);
            }
            
            float scale = (m_passedTime - halfDuration) / halfDuration;
            if (scale >= 1) {
                scale = 1;
                m_isCompleted = true;
            }
            m_card->setHorizontalScale(scale);
        } else {
            float scale = 1 - (m_passedTime / halfDuration);
            m_card->setHorizontalScale(scale);
        }
    }
    
    bool FlipCardAnimation::getIsCompleted() const {
        return m_isCompleted;
    }
}
