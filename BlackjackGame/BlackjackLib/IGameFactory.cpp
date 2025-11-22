#include "IGameFactory.h"

class GameFactory : public IGameFactory
{
public:
    IGameController* CreateGame() override;
};

IGameController* GameFactory::CreateGame()
{
    return new GameEngine();
}