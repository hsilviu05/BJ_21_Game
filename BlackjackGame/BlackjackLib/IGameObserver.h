#pragma once
#include "HandData.h"

class IGameObserver
{
public:
    IGameObserver();
    ~IGameObserver();

    virtual void OnGameStarted(const HandData& playerHand, const HandData& dealerHand);
    virtual void OnPlayerHandChanged(const HandData& playerHand);
    virtual void OnDealerHandChanged(const HandData& dealerHand);
    virtual void OnGameEnded(GameState state, const HandData& finalPlayerData, const HandData& finalDealerData);
    virtual void OnPlayerTurnBegan();
};
