//
//  CardsState.cpp
//  CardHero
//
//  Created by Mijo Gracanin on 04/11/2018.
//  Copyright © 2018 MijoCoder. All rights reserved.
//

#include "DEFINITIONS.h"
#include "CardsState.hpp"
#include <iostream>


namespace as
{
#define INDEX_NOT_FOUND -1
    
    CardsState::CardsState(GameDataRef data):
    m_data(data),
    m_isPlayerTurn(true)
    {
        m_playerHand.fill(nullptr);
        m_aiHand.fill(nullptr);
    }
    
    void CardsState::Init()
    {
        m_currentState = DEAL_CARDS;
        setupCardSize();
        generateDeck();
        shuffleDeck();
        updateDeckPosition();
    }
    
    void CardsState::HandleInput()
    {
        sf::Event event;
        while(this->m_data->window.pollEvent(event))
        {
            if(sf::Event::Closed==event.type)
            {
                this->m_data->window.close();
            }
        }
    }
    
    void CardsState::Update(float dt)
    {
        if (m_currentState == DEAL_CARDS) {
            if (m_animations.empty()) {
                
                auto &hand = m_isPlayerTurn ? m_playerHand : m_aiHand;
                
                if (getCardCount(hand) == CARD_HAND_COUNT) {
                    m_currentState = DRAW_CARDS;
                    return;
                }
                
                Card *card = m_cardDeck.back();
                m_cardDeck.pop_back();
                
                int freeCardSlotIndex = getFreeCardSlotIndex(hand);
                hand[freeCardSlotIndex] = card;
                sf::Vector2f destination = getPositionOfHandCardAtIndex(freeCardSlotIndex);
                m_animations.emplace_back(card, destination);
            } else {
                for (auto &animation: m_animations) {
                    animation.update(dt);
                }
                purgeCompletedAnimations();
                
                if (m_animations.size() == 0) {
                    m_isPlayerTurn = !m_isPlayerTurn;
                }
            }
        } else if (m_currentState == DRAW_CARDS) {
            // TODO
        }
    }
    
    void CardsState::Draw(float dt)
    {
        this->m_data->window.clear();
        
        drawCards();
        
        this->m_data->window.display();
    }
    
    #pragma mark - Private methods
    
    void CardsState::setupCardSize() {
        sf::Vector2u windowSize = m_data->window.getSize();
        uint cardWidth = windowSize.x / 10;
        uint cardHeight = cardWidth * 2;
        m_cardSize = sf::Vector2f(cardWidth, cardHeight);
    }
    
    void CardsState::generateDeck() {
        std::array<CardColor, 5> colors = { CardColor::ALL, CardColor::BLUE, CardColor::GREEN, CardColor::RED, CardColor::YELLOW };
        int cardCountPerColor = CARD_DECK_COUNT / colors.size();
        
        for (auto &color: colors) {
            for (int j=0; j < cardCountPerColor; ++j) {
                CardTrait trait;
                m_cards.emplace_back(color, trait, m_cardSize);
            }
        }
    }
    
    void CardsState::shuffleDeck() {
        // TODO
        for (auto &card: m_cards) {
            m_cardDeck.push_back(&card);
        }
    }
    
    void CardsState::updateDeckPosition() {
        sf::Vector2u windowSize = m_data->window.getSize();
        int leftMargin = windowSize.x / 20;
        int verticalOffset = 3;
        int verticalMiddle = windowSize.y / 2;
        int cardMiddle = m_cardSize.y / 2;
        int bottomMargin = verticalMiddle - cardMiddle + (m_cardDeck.size() / 2 * verticalOffset);
        for (int i=0; i<m_cardDeck.size(); ++i) {
            m_cardDeck[i]->setPosition(leftMargin, bottomMargin - (i * verticalOffset));
        }
    }
    
    void CardsState::drawCards() const {
        for (auto *card: m_cardDeck) {
            this->m_data->window.draw(*card);
        }
        
        for (int i=0; i<CARD_HAND_COUNT; ++i) {
            if (m_playerHand[i] != nullptr) {
                Card *card = m_playerHand[i];
                this->m_data->window.draw(*card);
            }
            
            if (m_aiHand[i] != nullptr) {
                Card *card = m_aiHand[i];
                this->m_data->window.draw(*card);
            }
        }
    }
    
    int CardsState::getCardCount(std::array<Card *, CARD_HAND_COUNT> &hand) const {
        int count = 0;
        
        for (int i=0; i<hand.size(); ++i) {
            if (hand[i] != nullptr) {
                ++count;
            }
        }
        
        return count;
    }
    
    int CardsState::getFreeCardSlotIndex(std::array<Card *, CARD_HAND_COUNT> &hand) const {
        int index = INDEX_NOT_FOUND;
        
        for (int i=CARD_HAND_COUNT-1; i>=0; --i) {
            if (hand[i] == nullptr) {
                return i;
            }
        }
        
        return index;
    }
    
    sf::Vector2f CardsState::getPositionOfHandCardAtIndex(int index) const {
        sf::Vector2u windowSize = m_data->window.getSize();
        float paddingBetweenCards = m_cardSize.x / 10;
        float screenMiddle = windowSize.x / 2;
        float cardMiddle = m_cardSize.x / 2;
        float widthOfCardsInHand = CARD_HAND_COUNT * m_cardSize.x;
        float paddingBetweenCardsInHand = (CARD_HAND_COUNT - 1) * paddingBetweenCards;
        float handWidth = widthOfCardsInHand + paddingBetweenCardsInHand;
        float firstCard_x = screenMiddle - cardMiddle - (handWidth / 2);
        float x = firstCard_x + (index * (m_cardSize.x + paddingBetweenCards));
        
        float y;
        if (m_isPlayerTurn) {
            y = windowSize.y - m_cardSize.y - paddingBetweenCards;
        } else {
            y = paddingBetweenCards;
        }
        
        return sf::Vector2f(x, y);
    }
    
    void CardsState::purgeCompletedAnimations() {
        int i = 0;
        
        while (i < m_animations.size()) {
            auto &animation = m_animations[i];
            
            if (animation.getIsCompleted()) {
                m_animations.erase(m_animations.begin() + i);
            } else {
                ++i;
            }
        }
    }

}
