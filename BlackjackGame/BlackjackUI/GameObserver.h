#pragma once
#include "IGameObserver.h"
#include "HandData.h"
#include "GameState.h"

class SFMLGameObserver : public IGameObserver
{
public:
    HandData playerHand;
    HandData dealerHand;
    GameState currentState;
    bool gameEnded = false;
    bool playerTurn = false;

    virtual void OnGameStarted(const HandData& playerHand, const HandData& dealerHand) override;
    virtual void OnPlayerHandChanged(const HandData& playerHand) override;
    virtual void OnDealerHandChanged(const HandData& dealerHand) override;
    virtual void OnGameEnded(GameState state, const HandData& finalPlayerData, const HandData& finalDealerData) override;
    virtual void OnPlayerTurnBegan() override;
};


