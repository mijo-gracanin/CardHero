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
    static const int CARD_DECK_COUNT = 20;
    
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
        std::vector<Card> m_playerWonCards;
        std::vector<Card> m_aiWonCards;
        std::array<Card *, 4> m_playerHand;
        std::array<Card *, 4> m_aiHand;
        sf::Vector2f m_cardSize;
        
        void generateDeck();
        void shuffleDeck();
        void updateDeckPosition();
    };
}

#endif /* CardsState_hpp */
