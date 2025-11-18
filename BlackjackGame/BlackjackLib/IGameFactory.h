#pragma once
#include "IGameController.h"
#include "GameEngine.h"

class IGameFactory
{
public:
    virtual ~IGameFactory() = default;
    virtual IGameController* CreateGame() = 0;
};