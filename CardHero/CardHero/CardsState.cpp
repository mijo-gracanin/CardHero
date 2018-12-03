//
//  CardsState.cpp
//  CardHero
//
//  Created by Mijo Gracanin on 04/11/2018.
//  Copyright © 2018 MijoCoder. All rights reserved.
//

#include "DEFINITIONS.h"
#include "CardsState.hpp"
#include "InputManager.h"
#include "Game.h"
#include <iostream>


namespace as
{
#define INDEX_NOT_FOUND -1
    
    CardsState::CardsState(GameDataRef data):
    m_data(data),
    m_isPlayerTurn(true),
    m_selectedCard(nullptr)
    {
        m_playerHand.fill(nullptr);
        m_aiHand.fill(nullptr);
    }
    
    void CardsState::Init()
    {
        m_currentState = DEAL_CARDS;
        setupCardSize();
        setupPlayAreaRect();
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
        if (!m_animations.empty()) {
            for (auto &animation: m_animations) {
                animation.update(dt);
            }
            purgeCompletedAnimations();
            return;
        }
        
        if (m_currentState == DEAL_CARDS) {
            
            auto &hand = m_isPlayerTurn ? m_playerHand : m_aiHand;
            
            if (getCardCount(hand) == CARD_HAND_COUNT) {
                m_currentState = PLAY_CARDS;
                return;
            }
            
            Card *card = m_cardDeck.back();
            m_cardDeck.pop_back();
            
            int freeCardSlotIndex = getFreeCardSlotIndex(hand);
            hand[freeCardSlotIndex] = card;
            sf::Vector2f destination = getPositionOfHandCardAtIndex(freeCardSlotIndex);
            m_animations.emplace_back(card, destination);
            m_isPlayerTurn = !m_isPlayerTurn;
        }
        else if (m_currentState == PLAY_CARDS) {
            if (m_isPlayerTurn) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(m_data->window); //m_data->input.GetMousePosition(m_data->window);
                Card *selectedCard = getSelectedCard();
                
                if (selectedCard != nullptr && m_selectedCard == selectedCard) {
                    int x = mousePosition.x - m_mousePosition.x;
                    int y = mousePosition.y - m_mousePosition.y;
                    m_selectedCard->move(x, y);
                } else if (selectedCard == nullptr && m_selectedCard != nullptr) {
                    sf::Vector2f postition = m_selectedCard->getPosition();
                    if (m_playArea.contains(postition.x, postition.y)) {
                        moveCardFromHandToPlayArea(m_selectedCard);
                        m_isPlayerTurn = false;
                    } else {
                        alignMisplacedCards();
                    }
                }
                
                m_selectedCard = selectedCard;
                m_mousePosition = mousePosition;
            }
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
        int cardWidth = windowSize.x / 10;
        int cardHeight = cardWidth * 2;
        m_cardSize = sf::Vector2f(cardWidth, cardHeight);
    }
    
    void CardsState::setupPlayAreaRect() {
        sf::Vector2u windowSize = m_data->window.getSize();
        int width = windowSize.x / 12;
        int height = width * 2;
        int x = (windowSize.x - width) / 2;
        int y = (windowSize.y - height) / 2;
        m_playArea = sf::IntRect(x, y, width, height);
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
        int leftMargin = m_cardSize.x / 10 + (m_cardSize.x /2);
        int verticalOffset = 3;
        int verticalMiddle = windowSize.y / 2;
        int bottomMargin = verticalMiddle + (verticalOffset * m_cardDeck.size() / 2);
        for (int i=0; i<m_cardDeck.size(); ++i) {
            m_cardDeck[i]->setPosition(leftMargin, bottomMargin - (i * verticalOffset));
        }
    }
    
    void CardsState::drawCards() const {
        for (auto *card: m_cardDeck) {
            m_data->window.draw(*card);
        }
        
        for (auto *card: m_playAreaCards) {
            m_data->window.draw(*card);
        }
        
        for (int i=0; i<CARD_HAND_COUNT; ++i) {
            if (m_playerHand[i] != nullptr) {
                Card *card = m_playerHand[i];
                m_data->window.draw(*card);
            }
            
            if (m_aiHand[i] != nullptr) {
                Card *card = m_aiHand[i];
                m_data->window.draw(*card);
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
        float widthOfCardsInHand = CARD_HAND_COUNT * m_cardSize.x;
        float paddingBetweenCardsInHand = (CARD_HAND_COUNT - 1) * paddingBetweenCards;
        float handWidth = widthOfCardsInHand + paddingBetweenCardsInHand;
        float firstCard_x = screenMiddle - (handWidth / 2);
        float x = firstCard_x + (index * (m_cardSize.x + paddingBetweenCards));
        
        float y;
        if (m_isPlayerTurn) {
            y = windowSize.y - (m_cardSize.y / 2) - paddingBetweenCards;
        } else {
            y = paddingBetweenCards + (m_cardSize.y / 2);
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
    
    Card* CardsState::getSelectedCard() const {
        
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            return nullptr;
        }
        
        if (m_selectedCard != nullptr) {
            return m_selectedCard;
        }
        
        Card* selectedCard = nullptr;
        sf::Vector2i mousePosition = sf::Mouse::getPosition(m_data->window); //m_data->input.GetMousePosition(m_data->window);
        
        for (auto *card: m_playerHand) {
            if (card == nullptr) {
                continue;
            }
            
            sf::Vector2f cardOrigin = card->getPosition(); // card middle
            int x = cardOrigin.x - (m_cardSize.x / 2);
            int y = cardOrigin.y - (m_cardSize.y / 2);
            sf::IntRect rect(x, y, m_cardSize.x, m_cardSize.y);
            
            if (rect.contains(mousePosition.x, mousePosition.y)) {
                selectedCard = card;
                break;
            }
        }
        
        return selectedCard;
    }
    
    void CardsState::moveCardFromHandToPlayArea(Card *card) {
        auto &hand = m_isPlayerTurn ? m_playerHand : m_aiHand;
        
        m_playAreaCards.push_back(m_selectedCard);
        
        for (int i=0; i<hand.size(); ++i) {
            if (hand[i] == card) {
                hand[i] = nullptr;
                break;
            }
        }
    }
    
    void CardsState::alignMisplacedCards() {
        auto &hand = m_isPlayerTurn ? m_playerHand : m_aiHand;
        
        for (int i=0; i<hand.size(); ++i) {
            Card *card = hand[i];
            
            if (card == nullptr) {
                continue;
            }
            
            auto position = getPositionOfHandCardAtIndex(i);
            if (card->getPosition() != position) {
                m_animations.emplace_back(card, position);
            }
        }
    }

}
