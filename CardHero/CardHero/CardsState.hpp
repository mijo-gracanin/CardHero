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
#include "CardAnimation.h"

namespace as
{
    static const int CARD_DECK_COUNT = 20;
    static const int CARD_HAND_COUNT = 4;
    
    
    enum CardGameStateTypes {
        DEAL_CARDS, PLAY_CARDS, GAME_OVER
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
        std::vector<Card> m_cards;
        std::vector<Card *> m_cardDeck;
        std::vector<Card *> m_playerWonCards;
        std::vector<Card *> m_aiWonCards;
        std::vector<Card *> m_playAreaCards;
        std::vector<std::unique_ptr<CardAnimation>> m_animations;
        std::array<Card *, CARD_HAND_COUNT> m_playerHand;
        std::array<Card *, CARD_HAND_COUNT> m_aiHand;
        sf::Vector2f m_cardSize;
        bool m_isPlayerTurn;
        Card *m_selectedCard;
        sf::Vector2i m_mousePosition;
        sf::IntRect m_playArea;
        sf::IntRect m_snapArea;
        sf::RectangleShape m_playAreaOutline;
        
        void setupCardSize();
        void setupPlayAreaRect();
        void generateDeck();
        void shuffleDeck();
        void updateDeckPosition();
        void dealCard();
        void drawCards() const;
        int getCardCount(std::array<Card *, CARD_HAND_COUNT> &hand) const;
        int getFreeCardSlotIndex(std::array<Card *, CARD_HAND_COUNT> &hand) const;
        sf::Vector2f getPositionOfHandCardAtIndex(int index) const;
        void purgeCompletedAnimations();
        Card* getSelectedCard() const;
        void moveCardFromHandToPlayArea(Card *card);
        void alignMisplacedCards();
        bool doesHandContainColor(CardColor color) const;
        void movePlayAreaCardsToWonPile();
        sf::Vector2f getPositionForCardOnWiningPile() const;
        void playAITurn();
        void playSelectedCard();
        void handleDragGestureForEvent(sf::Event event);
        bool shouldTakePlayAreaCards() const;
        void skipTurnIfPossible();
    };
}

#endif /* CardsState_hpp */
