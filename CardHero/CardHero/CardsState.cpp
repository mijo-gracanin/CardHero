//
//  CardsState.cpp
//  CardHero
//
//  Created by Mijo Gracanin on 04/11/2018.
//  Copyright © 2018 MijoCoder. All rights reserved.
//

#include "DEFINITIONS.h"
#include "CardsState.hpp"


namespace as
{
    CardsState::CardsState(GameDataRef data):
    m_data(data),
    m_cardDeck({}),
    m_cardSize(sf::Vector2u(0, 0))
    {

    }
    
    void CardsState::Init()
    {
        sf::Vector2u windowSize = m_data->window.getSize();
        uint cardWidth = windowSize.x / 10;
        uint cardHeight = cardWidth * 2;
        m_cardSize = sf::Vector2f(cardWidth, cardHeight);
        
        generateDeck();
        updateDeckPosition();
    }
    
    void CardsState::HandleInput()
    {
        sf::Event event;
        while(this->m_data->window.pollEvent(event))
        {
            if(sf::Event::Closed==event.type)
            {
                this->m_data->window.close();
            }
        }
    }
    
    void CardsState::Update(float dt)
    {
        
    }
    
    void CardsState::Draw(float dt)
    {
        this->m_data->window.clear();
        
        for (int i=0; i<m_cardDeck.size(); ++i) {
            Card card = m_cardDeck[i];
            this->m_data->window.draw(card);
        }
        
        this->m_data->window.display();
    }
    
    #pragma mark - Private methods
    
    void CardsState::generateDeck() {
        std::array<CardColor, 5> colors = { CardColor::ALL, CardColor::BLUE, CardColor::GREEN, CardColor::RED, CardColor::YELLOW };
        int cardCountPerColor = CARD_DECK_COUNT / colors.size();
        
        for (int i=0; i < colors.size(); ++i) {
            CardColor color = colors[i];
            for (int j=0; j < cardCountPerColor; ++j) {
                CardTrait trait;
                Card card(color, trait, m_cardSize);
                m_cardDeck.insert(m_cardDeck.begin(), card);
            }
        }
    }
    
    void CardsState::shuffleDeck() {
        // TODO
    }
    
    void CardsState::updateDeckPosition() {
        sf::Vector2u windowSize = m_data->window.getSize();
        int leftMargin = windowSize.x / 20;
        int verticalOffset = 3;
        int verticalMiddle = windowSize.y / 2;
        int cardMiddle = m_cardSize.y / 2;
        int bottomMargin = verticalMiddle - cardMiddle + (m_cardDeck.size() / 2 * verticalOffset);
        for (int i=0; i<m_cardDeck.size(); ++i) {
            m_cardDeck[i].setPosition(leftMargin, bottomMargin - (i * verticalOffset));
        }
    }
}
