#include "BlackjackAPI.h"
#include "GameEngine.h"

namespace BlackjackAPI
{
    std::unique_ptr<IGameController> CreateGameController()
    {
        return std::make_unique<GameEngine>();
    }

    void DestroyGameController(IGameController* controller)
    {
        delete controller;
    }
}