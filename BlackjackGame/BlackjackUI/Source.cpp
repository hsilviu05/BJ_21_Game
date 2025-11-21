<<<<<<< Updated upstream
#include "../BlackjackLib/BlackjackAPI.h"
#include "../BlackjackLib/IGameController.h"
#include "../BlackjackLib/IGameObserver.h"
#include "../BlackjackLib/CardData.h"
#include "../BlackjackLib/HandData.h"
#include "../BlackjackLib/GameState.h"
#include "../BlackjackLib/CardFormatter.h"
#include <iostream>
#include <string>
#include <memory> 

class ConsoleObserver : public IGameObserver
{
private:
    bool m_gameEnded = false;

public:
    void OnGameStarted(const HandData& playerHand, const HandData& dealerHand) override
    {
        m_gameEnded = false;  // Reset flag la început de joc

        std::cout << "\n=== NEW GAME STARTED ===\n";
        std::cout << "Your hand:\n";
        for (const auto& card : playerHand.cards)
        {
            std::cout << "  " << CardFormatter::CardToString(card) << "\n";
        }
        std::cout << "Total: " << playerHand.value << "\n\n";
        
        std::cout << "Dealer's visible card:\n";
        if (!dealerHand.cards.empty())
        {
            std::cout << "  " << CardFormatter::CardToString(dealerHand.cards[0]) << "\n";
        }
        std::cout << "\n";
    }

    void OnPlayerHandChanged(const HandData& hand) override
    {
        std::cout << "\nYour hand:\n";
        for (const auto& card : hand.cards)
        {
            std::cout << "  " << CardFormatter::CardToString(card) << "\n";
        }
        std::cout << "Total: " << hand.value << "\n";
    }

    void OnDealerHandChanged(const HandData& hand) override
    {
        std::cout << "\nDealer's hand:\n";
        for (const auto& card : hand.cards)
        {
            std::cout << "  " << CardFormatter::CardToString(card) << "\n";
        }
        std::cout << "Total: " << hand.value << "\n";
    }

    void OnGameEnded(GameState state, const HandData& playerHand, const HandData& dealerHand) override
    {
        m_gameEnded = true;  // Setează flag când jocul se termină

        std::cout << "\n=== GAME OVER ===\n";
        
        std::cout << "\nYour final hand:\n";
        for (const auto& card : playerHand.cards)
        {
            std::cout << "  " << CardFormatter::CardToString(card) << "\n";
        }
        std::cout << "Total: " << playerHand.value << "\n";

        std::cout << "\nDealer's final hand:\n";
        for (const auto& card : dealerHand.cards)
        {
            std::cout << "  " << CardFormatter::CardToString(card) << "\n";
        }
        std::cout << "Total: " << dealerHand.value << "\n";

        std::cout << "\nResult: ";
        switch (state)
        {
            case GameState::PlayerWins:
                std::cout << "YOU WIN!\n";
                break;
            case GameState::DealerWins:
                std::cout << "DEALER WINS!\n";
                break;
            case GameState::Push:
                std::cout << "PUSH (TIE)!\n";
                break;
            case GameState::PlayerBlackjack:
                std::cout << "BLACKJACK! YOU WIN!\n";
                break;
            case GameState::PlayerBust:
                std::cout << "BUST! YOU LOSE!\n";
                break;
            default:
                break;
        }
        std::cout << "\n";
    }

    void OnPlayerTurnBegan() override
    {
        std::cout << "\n--- YOUR TURN ---\n";
    }

    // Metodă publică pentru a verifica dacă jocul s-a terminat
    bool IsGameEnded() const
    {
        return m_gameEnded;
    }
};

<<<<<<< Updated upstream
void DisplayMenu()
{
    std::cout << "\n1. Hit (draw a card)\n";
    std::cout << "2. Stand (end turn)\n";
    std::cout << "Choice: ";
}

void PlayGame(IGameController* game, ConsoleObserver& observer)  // Pasează observer ca parametru
{
    game->StartNewGame();

    bool gameInProgress = true;

    while (gameInProgress)
    {
        // Verifică dacă jocul s-a terminat (bust, blackjack, etc.)
        if (observer.IsGameEnded())
        {
            break;  // Ieși din loop
        }

        DisplayMenu();
        
        int choice;
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter 1 or 2.\n";
            continue;
        }

        switch (choice)
        {
            case 1:
                game->PlayerHit();
                break;
            case 2:
                game->PlayerStand();
                gameInProgress = false;
                break;
            default:
                std::cout << "Invalid choice! Please enter 1 or 2.\n";
                continue;
        }
    }
}

int main()
{
    std::cout << "=================================\n";
    std::cout << "   WELCOME TO BLACKJACK (21)    \n";
    std::cout << "=================================\n";

    auto game = BlackjackAPI::CreateGameController();
    ConsoleObserver observer;
    
    game->RegisterObserver(&observer);

    bool playing = true;
    while (playing)
    {
        PlayGame(game.get(), observer);  // Pasează observer

        std::cout << "\nPlay again? (y/n): ";
        char response;
        std::cin >> response;

        if (response != 'y' && response != 'Y')
        {
            playing = false;
        }
    }

    game->UnregisterObserver(&observer);
    BlackjackAPI::DestroyGameController(game.get());

    std::cout << "\nThanks for playing!\n";
    return 0;
}

