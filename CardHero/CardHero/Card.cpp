//
//  Card.cpp
//  CardHero
//
//  Created by Mijo Gracanin on 13/11/2018.
//  Copyright © 2018 MijoCoder. All rights reserved.
//

#include "Card.hpp"

namespace as {
    
    Card::Card(CardColor color, CardTrait trait, size size):
    m_color(color),
    m_trait(trait),
    m_cardShape(sf::RectangleShape(size)),
    m_cardText(sf::Text()),
    m_isRevealed(false) {
    
        m_cardShape.setFillColor(sf::Color::Cyan);
        m_cardShape.setOutlineColor(sf::Color::White);
        m_cardShape.setOutlineThickness(2);
    };
    
    void Card::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(m_cardShape, states);
        target.draw(m_cardText, states);
    }
}
