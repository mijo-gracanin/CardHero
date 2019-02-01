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
        m_cardShape.setFillColor(sf::Color(205, 205, 205));
        m_cardShape.setOutlineColor(sf::Color::White);
        m_cardShape.setOutlineThickness(2);
        m_cardShape.setOrigin(size.x / 2, size.y / 2);
        m_cardText.setOrigin(m_cardShape.getOrigin().x, m_cardShape.getOrigin().y);
        
        if (m_color == ALL) {
            setupGradient();
        }
    };
    
    void Card::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(m_cardShape, states);
        
        if (!m_isRevealed) {
            return;
        }
        
        target.draw(m_cardText, states);
        
        if (m_color == ALL) {
            target.draw(m_gradient, states);
        }
    }
    
    void Card::setPosition(float x, float y) {
        m_cardShape.setPosition(x, y);
        m_cardText.setPosition(x, y);
        
        if (m_color == ALL) {
            updateGradientPosition();
        }
    }
    
    void Card::move(float x, float y) {
        sf::Vector2f position = m_cardShape.getPosition();
        setPosition(position.x + x, position.y + y);
    }
    
    sf::Vector2f Card::getPosition() const {
        return m_cardShape.getPosition();
    }
    
    sf::Color Card::getSFColorForCardColor(CardColor color) {
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
    
    CardColor Card::getColor() const {
        return m_color;
    }
    
    bool Card::canPlayAgainst(Card *card) const {
        
        return m_color == card->getColor() || m_color == ALL;
    }
    
    void Card::setupGradient() {
        
        sf::Color colors [] = {sf::Color::Blue, sf::Color::Green,sf::Color::Red, sf::Color::Yellow};
        int pointCount = m_cardShape.getPointCount();
        m_gradient = sf::VertexArray(sf::TrianglesFan, pointCount + 2);
        
        sf::Vertex &centralVertex = m_gradient[0];
        centralVertex.color = sf::Color(205, 205, 205);
        
        for (int i=0; i < m_cardShape.getPointCount(); ++i) {
            sf::Vertex &vertex = m_gradient[i + 1];
            vertex.color = colors[i / 4];
        }
        
        sf::Vertex &closingVertex = m_gradient[m_gradient.getVertexCount() - 1];
        closingVertex.color = colors[0];
    }
    
    void Card::updateGradientPosition() {
        sf::Vertex &centralVertex = m_gradient[0];
        sf::Vector2f center = getPosition();
        centralVertex.position = center;
        
        int pointCount = m_cardShape.getPointCount();
        
        for (int i=0; i<pointCount; ++i) {
            m_gradient[i + 1].position = center - m_cardShape.getPoint(i) + m_cardShape.getOrigin();
        }
        
        sf::Vertex &closingVertex = m_gradient[m_gradient.getVertexCount() - 1];
        closingVertex.position = center - m_cardShape.getPoint(0) + m_cardShape.getOrigin();
    }
    
    bool Card::getIsRevealed() {
        return m_isRevealed;
    }
    
    void Card::setIsRevealed(bool isReveald) {
        m_isRevealed = isReveald;
        
        if (isReveald) {
            m_cardShape.setFillColor(getSFColorForCardColor(m_color));
        } else {
            m_cardShape.setFillColor(sf::Color(205, 205, 205));
        }
    }
    
    void Card::setHorizontalScale(float scale) {
        m_cardShape.setScale(scale, 1);
    }
}
