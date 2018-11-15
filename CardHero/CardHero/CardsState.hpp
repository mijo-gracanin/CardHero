//
//  CardsState.hpp
//  CardHero
//
//  Created by Mijo Gracanin on 04/11/2018.
//  Copyright © 2018 MijoCoder. All rights reserved.
//

#ifndef CardsState_hpp
#define CardsState_hpp

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace as
{
    class CardsState : public State {
    public:
        CardsState(GameDataRef data);
        
        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        
    private:
        GameDataRef _data;
    };
}

#endif /* CardsState_hpp */
