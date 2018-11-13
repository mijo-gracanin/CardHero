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

namespace as
{
    enum CardTrait {
        HP, MALE_DAMAGE, MOVEMENT_SPEED, ATACK_SPEED
    };
    
    class Card {
        CardTrait _trait;
        
    public:
        Card(CardTrait trait);
    };
}

#endif /* Card_hpp */
