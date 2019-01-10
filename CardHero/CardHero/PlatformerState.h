#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"


namespace as
{
    class PlatformerState :public State
   {
       public:
       PlatformerState(GameDataRef data);

       void Init();

       void HandleInput();
       void Update(float dt);
       void Draw(float dt);

   private:
    GameDataRef _data;





   };
}

