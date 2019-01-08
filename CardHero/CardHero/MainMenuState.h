#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"


namespace as
{
    class MainMenuState :public State
   {
       public:
       MainMenuState(GameDataRef data);

       void Init();

       void HandleInput();
       void Update(float dt);
       void Draw(float dt);

   private:
    GameDataRef _data;

    sf::Sprite menuBackground;
    sf::Music menuMusic;
    sf::Sprite button1,button2;



   };
}

