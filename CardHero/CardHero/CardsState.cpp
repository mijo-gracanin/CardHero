//
//  CardsState.cpp
//  CardHero
//
//  Created by Mijo Gracanin on 04/11/2018.
//  Copyright © 2018 MijoCoder. All rights reserved.
//

#include "CardsState.hpp"
#include "SplashState.h"
#include "DEFINITIONS.h"
#include <SFML/Audio.hpp>

namespace as
{
    CardsState::CardsState(GameDataRef data): _data(data)
    {
        
    }
    
    void CardsState::Init()
    {
        
    }
    
    void CardsState::HandleInput()
    {
        sf::Event event;
        while(this->_data->window.pollEvent(event))
        {
            if(sf::Event::Closed==event.type)
            {
                this->_data->window.close();
            }
        }
    }
    
    void CardsState::Update(float dt)
    {
        
    }
    
    void CardsState::Draw(float dt)
    {
        this->_data->window.clear();
        //this->_data->window.draw(this->_background);   after we make a splash screen we just remove //
        this->_data->window.display();
    }
}
