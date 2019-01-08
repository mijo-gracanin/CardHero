#include <sstream>
#include "CardsState.hpp"
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
    this->_data->assets.LoadTexture("Button1 Texture",BUTTON1_TEXTURE_FILEPATH);
    this->_data->assets.LoadTexture("Button2 Texture",BUTTON2_TEXTURE_FILEPATH);
    button1.setTexture(this->_data->assets.GetTexture("Button1 Texture"));
    button2.setTexture(this->_data->assets.GetTexture("Button2 Texture"));
    button1.setPosition(this->_data->window.getSize().x/2,(this->_data->window.getSize().y/2)-100);
    button1.setOrigin(button1.getGlobalBounds().width/2,button1.getGlobalBounds().height/2);
    button2.setPosition(this->_data->window.getSize().x/2,(this->_data->window.getSize().y/2)+100);
    button2.setOrigin(button2.getGlobalBounds().width/2,button2.getGlobalBounds().height/2);
    menuMusic.openFromFile(BACKGROUND_MENU_MUSIC_FILEPATH);
    menuMusic.setVolume(15.0f);
    menuMusic.play();
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

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&(button1.getGlobalBounds().contains(sf::Mouse::getPosition(this->_data->window).x,sf::Mouse::getPosition(this->_data->window).y)))
        this->_data->machine.AddState(StateRef(new CardsState(_data)),true),menuMusic.stop();



        }

    }
    void MainMenuState::Update(float dt)
    {

    }
    void MainMenuState::Draw(float dt)
    {
        this->_data->window.clear();
        this->_data->window.draw(button1);
        this->_data->window.draw(button2);
        this->_data->window.display();
    }

}















