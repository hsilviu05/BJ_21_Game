#include <iostream>
#include <string>

#include "IGameController.h"
#include "IGameObserver.h"
#include "HandData.h"
#include "GameState.h"

#include "GameEngine.h"
class ConsoleObserver : public IGameObserver
{
public:
    virtual ~ConsoleObserver() = default;

    virtual void OnGameStarted(const HandData& playerHand, const HandData& dealerHand) override
    {
        std::cout << "--- JOC NOU INCEPUT ---\n";
        std::cout << "Player are: " << playerHand.value << "\n";
        std::cout << "Dealer are: " << dealerHand.value << "\n";
    }

    virtual void OnPlayerHandChanged(const HandData& playerHand) override
    {
        std::cout << "Player a tras. Noul scor: " << playerHand.value << "\n";
    }

    virtual void OnDealerHandChanged(const HandData& dealerHand) override
    {
        std::cout << "Dealer a tras. Noul scor: " << dealerHand.value << "\n";
    }

    virtual void OnPlayerTurnBegan() override
    {
        std::cout << "\nAcum e randul tau (Player). Ce faci? (h = hit, s = stand)\n";
    }

    virtual void OnGameEnded(GameState state, const HandData& finalPlayerData, const HandData& finalDealerData) override
    {
        std::cout << "\n--- JOC TERMINAT --- \n";
        std::cout << "Scor final Player: " << finalPlayerData.value << "\n";
        std::cout << "Scor final Dealer: " << finalDealerData.value << "\n";

        switch (state)
        {
        case GameState::PlayerWins:
            std::cout << "REZULTAT: AI CASTIGAT!\n";
            break;
        case GameState::DealerWins:
            std::cout << "REZULTAT: DEALERUL A CASTIGAT!\n";
            break;
        case GameState::Push:
            std::cout << "REZULTAT: EGALITATE (PUSH)!\n";
            break;
        case GameState::PlayerBlackjack:
            std::cout << "REZULTAT: BLACKJACK! AI CASTIGAT!\n";
            break;
        case GameState::PlayerBust:
            std::cout << "REZULTAT: AI DEPASIT 21 (BUST)! DEALERUL CASTIGA.\n";
            break;
        }
    }
};

int main()
{
    GameEngine game;

    ConsoleObserver observer;

    game.RegisterObserver(&observer);

    game.StartNewGame();

    std::string input;
    while (true)
    {
        std::cin >> input;
        if (input == "h" || input == "hit")
        {
            std::cout << "=> Player a cerut HIT\n";
            game.PlayerHit();
        }
        else if (input == "s" || input == "stand")
        {
            std::cout << "=> Player a cerut STAND\n";
            game.PlayerStand();
        }
    }

    return 0;
}