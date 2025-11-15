#pragma once
#include "HandData.h"
#include "GameState.h"

class IGameObserver
{
public:
    virtual ~IGameObserver() = default;

    virtual void OnGameStarted(const HandData& playerHand, const HandData& dealerHand) = 0;
    virtual void OnPlayerHandChanged(const HandData& playerHand) = 0;
    virtual void OnDealerHandChanged(const HandData& dealerHand) = 0;
    virtual void OnGameEnded(GameState state, const HandData& finalPlayerData, const HandData& finalDealerData) = 0;
    virtual void OnPlayerTurnBegan() = 0;
};
