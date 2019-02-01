//
//  FlipCardAnimation.hpp
//  CardHero
//
//  Created by Mijo Gracanin on 20/01/2019.
//  Copyright © 2019 MijoCoder. All rights reserved.
//

#ifndef FlipCardAnimation_hpp
#define FlipCardAnimation_hpp

#include "CardAnimation.h"
#include "Card.hpp"

namespace as
{
    class FlipCardAnimation: public CardAnimation {
        
    public:
        FlipCardAnimation(Card * const card, float flipDuration = 0.3);
        virtual void update(float dt) override;
        virtual bool getIsCompleted() const override;
        
    private:
        Card *m_card;
        float m_flipDuration;
        float m_passedTime;
        float m_isInitialyRevealed;
        bool m_isCompleted;
    };
}

#endif /* FlipCardAnimation_hpp */
