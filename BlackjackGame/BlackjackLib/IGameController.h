#pragma once
#include "IGameObserver.h"

class IGameController
{
    public:
    virtual ~IGameController() = default;

    virtual void StartNewGame() = 0;
    virtual void PlayerStand() = 0;
    virtual void PlayerHit() = 0;
    
    virtual void RegisterObserver(IGameObserver* observer) = 0;
    virtual void UnregisterObserver(IGameObserver* observer) = 0;

};