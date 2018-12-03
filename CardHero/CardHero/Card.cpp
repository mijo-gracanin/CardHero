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
    m_cardShape(sf::RoundedRectangleShape()),
    m_cardText(sf::Text()),
    m_isRevealed(false) {
    
        m_cardShape.setSize(size);
        float radius = size.x / 8;
        m_cardShape.setCornersRadius(radius);
        m_cardShape.setCornerPointCount(4);
        m_cardShape.setFillColor(getColorForCardColor(m_color));
        m_cardShape.setOutlineColor(sf::Color::White);
        m_cardShape.setOutlineThickness(2);
        m_cardShape.setOrigin(size.x / 2, size.y / 2);
        
        m_cardText.setOrigin(m_cardShape.getOrigin().x, m_cardShape.getOrigin().y);
    };
    
    void Card::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(m_cardShape, states);
        target.draw(m_cardText, states);
    }
    
    void Card::setPosition(float x, float y) {
        m_cardShape.setPosition(x, y);
        m_cardText.setPosition(x, y);
    }
    
    void Card::move(float x, float y) {
        sf::Vector2f position = m_cardShape.getPosition();
        setPosition(position.x + x, position.y + y);
    }
    
    sf::Vector2f Card::getPosition() const {
        return m_cardShape.getPosition();
    }
    
    sf::Color Card::getColorForCardColor(CardColor color) {
        switch (color) {
            case ALL:
                return sf::Color::Magenta;
            case BLUE:
                return sf::Color::Blue;
            case GREEN:
                return sf::Color::Green;
            case RED:
                return sf::Color::Red;
            case YELLOW:
                return sf::Color::Yellow;
        }
    }
}
