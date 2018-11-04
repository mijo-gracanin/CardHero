#include <sstream>
#include "SplashState.h"
#include "DEFINITIONS.h"
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
     // sf::SoundBuffer buffer;
     // buffer.loadFromFile(BACKGROUND_MUSIC_FILEPATH);
     // _Sound.setBuffer(buffer);
     // _Sound.play();
     sf::Music bkmusic;
     bkmusic.openFromFile("nice_music.ogg");
     bkmusic.play();
     bkmusic.setVolume(50);
     std::cout<<"SPlash";

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
            //std::cout<<"Go to Main Menu"<<std::endl;
        }
    }

    void SplashState::Draw(float dt)
    {
        this->_data->window.clear();
        //this->_data->window.draw(this->_background);   after we make a splash screen we just remove //
        this->_data->window.display();
    }
}
