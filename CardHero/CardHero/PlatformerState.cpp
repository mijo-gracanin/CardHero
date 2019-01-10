#include <sstream>
#include "MainMenuState.h"
#include "PlatformerState.h"
#include "DEFINITIONS.h"
#include <SFML/Audio.hpp>
#include <iostream>



namespace as
{
    PlatformerState::PlatformerState(GameDataRef data): _data(data)
    {

    }
    void PlatformerState::Init()
    {


    }


    void PlatformerState::HandleInput()
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
    void PlatformerState::Update(float dt)
    {

    }
    void PlatformerState::Draw(float dt)
    {
        this->_data->window.clear();

        this->_data->window.display();
    }

}















