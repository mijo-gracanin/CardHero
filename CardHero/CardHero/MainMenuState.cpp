#include <sstream>
#include "MainMenuState.h"
#include "DEFINITIONS.h"
#include <SFML/Audio.hpp>
#include <iostream>



namespace as
{
    MainMenuState::MainMenuState(GameDataRef data): _data(data)
    {

    }
    void MainMenuState::Init()
    {


    }


    void MainMenuState::HandleInput()
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
    void MainMenuState::Update(float dt)
    {

    }
    void MainMenuState::Draw(float dt)
    {
        this->_data->window.clear();

        this->_data->window.display();
    }

}















