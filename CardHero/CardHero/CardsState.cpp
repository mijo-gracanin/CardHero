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
#include <random>


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
    
    void CardsState::HandleInput() {
        
        sf::Event event;
        while(this->m_data->window.pollEvent(event)) {
            
            if (event.type == sf::Event::Closed) {
                this->m_data->window.close();
            } else if (event.type == sf::Event::MouseButtonPressed &&
                       event.mouseButton.button == sf::Mouse::Button::Right) {
                skipTurnIfPossible();
            } else {
                handleDragGestureForEvent(event);
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
            dealCard();
        }
        else if (m_currentState == PLAY_CARDS) {
            if (!m_isPlayerTurn) {
                playAITurn();
            }
            else if (!m_playAreaCards.empty() && m_playAreaCards.size() % 2 == 0) {
                if (shouldTakePlayAreaCards()) {
                movePlayAreaCardsToWonPile();
                m_currentState = DEAL_CARDS;
                } else if (!doesHandContainColor(m_playAreaCards.front()->getColor())) {
                    skipTurnIfPossible();
                }
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
        
        for (auto &card: m_cards) {
            m_cardDeck.push_back(&card);
        }
        
        std::random_device rd;
        std::mt19937 mersenne(rd());
        std::shuffle(m_cardDeck.begin(), m_cardDeck.end(), mersenne);
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
    
    void CardsState::dealCard() {
        if (m_cardDeck.empty() && getFreeCardSlotIndex(m_playerHand) == INDEX_NOT_FOUND) {
            m_currentState = GAME_OVER;
            return;
        }
        
        while(true) {
            auto &hand = m_isPlayerTurn ? m_playerHand : m_aiHand;
            
            if (getCardCount(hand) == CARD_HAND_COUNT || m_cardDeck.empty()) {
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
    }
    
    void CardsState::drawCards() const {
        for (auto *card: m_cardDeck) {
            m_data->window.draw(*card);
        }
        
        for (auto *card: m_playerWonCards) {
            m_data->window.draw(*card);
        }
        
        for (auto *card: m_aiWonCards) {
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
        float firstCard_x = screenMiddle - (handWidth / 2) + (m_cardSize.x / 2);
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
        
        m_playAreaCards.push_back(card);
        
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
    
    bool CardsState::doesHandContainColor(CardColor color) const {
        auto &hand = m_isPlayerTurn ? m_playerHand : m_aiHand;
        
        for (auto *card: hand) {
            if (card == nullptr) {
                continue;
            }
            
            if (card->getColor() == color || card->getColor() == ALL) {
                return true;
            }
        }
        
        return false;
    }
    
    void CardsState::movePlayAreaCardsToWonPile() {
        auto &winingPile = m_isPlayerTurn ? m_playerWonCards : m_aiWonCards;
        
        for (auto *card: m_playAreaCards) {
            winingPile.push_back(card);
            sf::Vector2f position = getPositionForCardOnWiningPile();
            m_animations.emplace_back(card, position);
        }
        
        m_playAreaCards.clear();
    }
    
    sf::Vector2f CardsState::getPositionForCardOnWiningPile() const {
        auto &winingPile = m_isPlayerTurn ? m_playerWonCards : m_aiWonCards;
        sf::Vector2u windowSize = m_data->window.getSize();
        float paddingBetweenCards = m_cardSize.x / 10;
        int x = windowSize.x - paddingBetweenCards - (m_cardSize.x / 2);
        int verticalOffset = 3;
        int y;
        
        if (m_isPlayerTurn) {
            y = windowSize.y - (m_cardSize.y / 2) - paddingBetweenCards - (winingPile.size() * verticalOffset);
        } else {
            int maxStackHeight = verticalOffset * m_cards.size() + m_cardSize.y;
            y = (maxStackHeight / 2) + paddingBetweenCards - (winingPile.size() * verticalOffset);
        }
        
        return sf::Vector2f(x, y);
    }
    
    void CardsState::playAITurn() {
        if (m_playAreaCards.empty()) {
            
            for (auto *card: m_aiHand) {
                if (card == nullptr) {
                    continue;
                }
                
                moveCardFromHandToPlayArea(card);
                m_animations.emplace_back(card, getRandomPositionInPlayArea());
                m_isPlayerTurn = true;
                break;
            }
        } else if (m_playAreaCards.size() % 2 != 0) {
            
            Card *bottomCard = m_playAreaCards.front();
            Card *cardToPlay = nullptr;
            
            for (auto *card: m_aiHand) {
                if (card == nullptr) {
                    continue;
                }
                
                cardToPlay = card;
                
                if (card->canPlayAgainst(bottomCard)) {
                    break;
                }
            }
            
            moveCardFromHandToPlayArea(cardToPlay);
            m_animations.emplace_back(cardToPlay, getRandomPositionInPlayArea());
            m_isPlayerTurn = true;
        } else {
            if (shouldTakePlayAreaCards()) {
                movePlayAreaCardsToWonPile();
                m_currentState = DEAL_CARDS;
                return;
            }
            
            Card *bottomCard = m_playAreaCards.front();
            Card *cardToPlay = nullptr;
            
            for (auto *card: m_aiHand) {
                if (card == nullptr) {
                    continue;
                }
                
                if (card->canPlayAgainst(bottomCard)) {
                    cardToPlay = card;
                    break;
                }
            }
            
            if (cardToPlay == nullptr) {
                m_isPlayerTurn = true;
                movePlayAreaCardsToWonPile();
                m_currentState = DEAL_CARDS;
            } else {
                moveCardFromHandToPlayArea(cardToPlay);
                m_animations.emplace_back(cardToPlay, getRandomPositionInPlayArea());
                m_isPlayerTurn = true;
            }
        }
    }
    
    sf::Vector2f CardsState::getRandomPositionInPlayArea() const {
        float x = m_playArea.left + (rand() % m_playArea.width);
        float y = m_playArea.top + (rand() % m_playArea.height);
        return sf::Vector2f(x, y);
    }
    
    void CardsState::handleDragGestureForEvent(sf::Event event) {
        
        if (!m_animations.empty() || !m_isPlayerTurn || m_currentState != PLAY_CARDS) {
            return;
        }
        
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Button::Left) {
            
            m_selectedCard = getSelectedCard();
            m_mousePosition = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
            
        } else if (event.type == sf::Event::MouseButtonReleased &&
                   event.mouseButton.button == sf::Mouse::Button::Left &&
                   m_selectedCard != nullptr) {
            
            sf::Vector2f postition = m_selectedCard->getPosition();
            if (m_playArea.contains(postition.x, postition.y)) {
                playSelectedCard();
            } else {
                alignMisplacedCards();
            }
            m_selectedCard = nullptr;
            
        } else if (event.type == sf::Event::MouseMoved &&
                   m_selectedCard != nullptr) {
            
            sf::Vector2i mousePosition = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
            int x = mousePosition.x - m_mousePosition.x;
            int y = mousePosition.y - m_mousePosition.y;
            m_selectedCard->move(x, y);
            m_mousePosition = mousePosition;
        }
    }
    
    void CardsState::playSelectedCard() {
        if (m_playAreaCards.empty()) {
            moveCardFromHandToPlayArea(m_selectedCard);
            m_isPlayerTurn = false;
        } else if (m_playAreaCards.size() % 2 != 0) {
            
            Card *topCard = m_playAreaCards.back();
            moveCardFromHandToPlayArea(m_selectedCard);
            m_isPlayerTurn = false;
        } else {
            Card *bottomCard = m_playAreaCards.front();
            
            if (m_selectedCard->canPlayAgainst(bottomCard)) {
                moveCardFromHandToPlayArea(m_selectedCard);
                m_isPlayerTurn = false;
            } else {
                alignMisplacedCards();
            }
        }
    }
    
    bool CardsState::shouldTakePlayAreaCards() const {
        Card *topCard = m_playAreaCards.back();
        Card *bottomCard = m_playAreaCards.front();
        
        return !topCard->canPlayAgainst(bottomCard);
    }
    
    void CardsState::skipTurnIfPossible() {
        if (!m_isPlayerTurn || m_playAreaCards.empty() || m_playAreaCards.size() % 2 != 0) {
            return;
        }
        
        m_isPlayerTurn = false;
        movePlayAreaCardsToWonPile();
        m_currentState = DEAL_CARDS;
    }
}
