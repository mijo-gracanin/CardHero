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
#include <array>
#include "State.h"
#include "Game.h"
#include "Card.hpp"

namespace as
{
    enum CardGameStateTypes {
        SHOW_CARDS, DEAL_CARDS, PLAYER_TURN, AI_TURN, GAME_OVER
    };
    
    
    class CardsState : public State {
    public:
        CardsState(GameDataRef data);
        
        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        
    private:
        GameDataRef m_data;
        CardGameStateTypes m_currentState;
        std::vector<Card> m_cardDeck;
        std::array<Card *, 4> m_playerHand;
    };
}

#endif /* CardsState_hpp */
