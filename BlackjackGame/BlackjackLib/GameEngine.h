#pragma once
#include "Hand.h"
#include "Deck.h"
#include "IGameObserver.h"
#include "IGameController.h"
#include "GameState.h"
#include <vector>

class GameEngine : public IGameController
{
    private:
    Hand m_playerHand;
    Hand m_dealerHand;
    Deck m_deck;
    std::vector<IGameObserver*> m_observers;
    GameState m_gameState;
    
    public:
    GameEngine();

    void StartNewGame() override;
    void PlayerHit() override;
    void PlayerStand() override;

    void RegisterObserver(IGameObserver* observer) override;
    void UnregisterObserver(IGameObserver* observer) override;
    
    private:
    void NotifyGameStarted();
    void NotifyPlayerHandChanged();
    void NotifyDealerHandChanged();
    void NotifyGameEnded(GameState state);
    void NotifyPlayerTurnBegan();

    void DealerTurn();


};