#pragma once
#include "IGameController.h"
#include <memory>

namespace BlackjackAPI
{
    std::unique_ptr<IGameController> CreateGameController();
    void DestroyGameController(IGameController* controller);
}