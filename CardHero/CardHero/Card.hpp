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
#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.hpp"

namespace as
{
    
    enum CardColor {
        BLUE, GREEN, RED, YELLOW, ALL
    };
    
    
    enum TraitType {
        HP, MELEE_DAMAGE, MOVEMENT_SPEED, ATACK_SPEED
    };
    
    
    struct CardTrait {
        TraitType type;
        float value;
    };
    
    
    typedef sf::Vector2f size;
    
    
    class Card : public sf::Drawable {
        
    public:
        Card(CardColor color, CardTrait trait, size size);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void setPosition(float x, float y);
        void move(float x, float y);
        sf::Vector2f getPosition() const;
        CardColor getColor() const;
        bool canPlayAgainst(Card *card) const;
        bool getIsRevealed();
        void setIsRevealed(bool isReveald);
        void setHorizontalScale(float scale);
        
    private:
        CardColor m_color;
        CardTrait m_trait;
        sf::RoundedRectangleShape m_cardShape;
        sf::Text m_cardText;
        sf::VertexArray m_gradient;
        bool m_isRevealed;
        
        static sf::Color getSFColorForCardColor(CardColor color);
        void setupGradient();
        void updateGradientPosition();
    };
}

#endif /* Card_hpp */
