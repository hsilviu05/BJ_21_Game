#pragma once
#include "GameEngine.h"

class IGameController : public GameEngine
{
    public:
    virtual void StartNewGame();
    virtual void PlayerStand();
    virtual void PlayerHit();
    virtual void DealerTurn();
    virtual void RegisterObserver(IGameObserver* observer);
    virtual void UnregisterObserver(IGameObserver* observer);

};