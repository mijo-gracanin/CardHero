//
//  Card.cpp
//  CardHero
//
//  Created by Mijo Gracanin on 13/11/2018.
//  Copyright © 2018 MijoCoder. All rights reserved.
//

#include "Card.hpp"

namespace as {
    
    Card::Card(CardTrait trait):
    m_trait(trait) {
        
    };
    
    void Card::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(m_cardShape, states);
        target.draw(m_cardText, states);
    }
}
