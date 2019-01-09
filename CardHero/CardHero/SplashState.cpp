#include <sstream>
#include "SplashState.h"
#include "DEFINITIONS.h"
#include "MainMenuState.h"
#include "ResourcePath.hpp"
#include <SFML/Audio.hpp>

#include <iostream>

namespace as
{
    SplashState::SplashState(GameDataRef data): _data(data)
    {

    }

    void SplashState::Init()
    {
        //this->_data->assets.LoadTexture("Splash State Background",SPLASH_SCENE_BACKGROUND_FILEPATH);     need to import a backgorund picture for splash screen
      //_background.setTexture(this->_data->assets.GetTexture("Splash State Background"));
        _introB.loadFromFile(resourcePath() + BACKGROUND_MUSIC_FILEPATH);
        _intro.setBuffer(_introB);
        _intro.play();
    }
    void SplashState::HandleInput()
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

    void SplashState::Update(float dt)
    {
        if(this->_clock.getElapsedTime().asSeconds()>SPLASH_STATE_SHOW_TIME)
        {
            _intro.stop();
            this->_data->machine.AddState(StateRef(new MainMenuState(_data)),true);
        }
    }

    void SplashState::Draw(float dt)
    {
        this->_data->window.clear();
        //this->_data->window.draw(this->_background);   after we make a splash screen we just remove //
        this->_data->window.display();
    }
}
