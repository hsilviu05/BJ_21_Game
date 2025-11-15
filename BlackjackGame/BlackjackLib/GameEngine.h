#pragma once
#include "Hand.h"
#include "Deck.h"
#include "IGameObserver.h"
#include "GameState.h"
#include <vector>

class GameEngine
{
    private:
    Hand m_playerHand;
    Hand m_dealerHand;
    Deck m_deck;
    std::vector<IGameObserver*> m_observers;
    GameState m_gameState;
    
    public:
    void StartGame();
    void PlayerHit();
    void PlayerStand();
    void RegisteredObserver(IGameObserver* observer);
    void UnregisterObserver(IGameObserver* observer);
    
    private:
    void NotifyGameStarted();
    void NotifyPlayerHandChanged();
    void NotifyDealerHandChanged();
    void NotifyGameEnded(GameState state);
    void DealerTurn();


};