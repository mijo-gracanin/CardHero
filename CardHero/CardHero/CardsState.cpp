//
//  CardsState.cpp
//  CardHero
//
//  Created by Mijo Gracanin on 04/11/2018.
//  Copyright © 2018 MijoCoder. All rights reserved.
//

#include "DEFINITIONS.h"
#include "CardsState.hpp"
#include "SplashState.h"
#include "Card.hpp"

namespace as
{
    CardsState::CardsState(GameDataRef data):
    m_data(data),
    m_cardDeck({})
    {
        CardTrait trait;
        Card card(CardColor::GREEN, trait, size(40, 80));
        m_cardDeck.insert(m_cardDeck.begin(), card);
    }
    
    void CardsState::Init()
    {
        
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
}
