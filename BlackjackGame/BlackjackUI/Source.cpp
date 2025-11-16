#include <iostream>
#include <string>
#include <vector>

#include "IGameController.h"
#include "IGameObserver.h"
#include "HandData.h"
#include "GameState.h"
#include "CardSuit.h"
#include "CardRank.h"


#include "GameEngine.h"

std::string RankToString(CardRank rank)
{
    switch (rank)
    {
        case CardRank::Two:   return "Doi";
        case CardRank::Three: return "Trei";
        case CardRank::Four:  return "Patru";
        case CardRank::Five:  return "Cinci";
        case CardRank::Six:   return "Sase";
        case CardRank::Seven: return "Sapte";
        case CardRank::Eight: return "Opt";
        case CardRank::Nine:  return "Noua";
        case CardRank::Ten:   return "Zece";
        case CardRank::Jack:  return "Valet";
        case CardRank::Queen: return "Dama";
        case CardRank::King:  return "Popa";
        case CardRank::Ace:   return "As";
        default: return "?";
    }
}

std::string SuitToString(CardSuit suit)
{
    switch (suit)
    {
        case CardSuit::Hearts:   return "Inima Rosie";
        case CardSuit::Diamonds: return "Romb";
        case CardSuit::Clubs:    return "Trefla";
        case CardSuit::Spades:   return "Inima Neagra";
        default: return "?";
    }
}

void PrintHand(const std::string& title, const HandData& hand)
{
    std::cout << title << " (Total: " << hand.value << ")\n";
    for (const CardData& card : hand.cards)
    {
        std::cout << "  - " << RankToString(card.rank) << " de " << SuitToString(card.suit) << "\n";
    }
}
class ConsoleObserver : public IGameObserver
{
public:
    virtual ~ConsoleObserver() = default;

    virtual void OnGameStarted(const HandData& playerHand, const HandData& dealerHand) override
    {
        std::cout << "--- JOC NOU INCEPUT ---\n";
        PrintHand("Mana Jucator:", playerHand);
        PrintHand("Mana Dealer (vizibil):", dealerHand);
    }

    virtual void OnPlayerHandChanged(const HandData& playerHand) override
    {
        std::cout << "\n=> Jucatorul a tras o carte.\n";
        PrintHand("Mana Jucator:", playerHand);
    }

    virtual void OnDealerHandChanged(const HandData& dealerHand) override
    {
        std::cout << "\n=> Dealerul a tras o carte.\n";
        PrintHand("Mana Dealer:", dealerHand);
    }

    virtual void OnPlayerTurnBegan() override
    {
        std::cout << "\nAcum e randul tau (Player). Ce faci? (h = hit, s = stand)\n";
    }

    virtual void OnGameEnded(GameState state, const HandData& finalPlayerData, const HandData& finalDealerData) override
    {
        std::cout << "\n--- JOC TERMINAT --- \n";
        PrintHand("Mana Finala Jucator:", finalPlayerData);
        PrintHand("Mana Finala Dealer:", finalDealerData);

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
    
    while (std::cin >> input)
    {
        if (input == "h" || input == "hit")
        {
            std::cout << "-> Comanda: HIT\n";
            game.PlayerHit();
        }
        else if (input == "s" || input == "stand")
        {
            std::cout << "-> Comanda: STAND\n";
            game.PlayerStand();
        }
        else if (input == "n" || input == "new")
        {
            std::cout << "-> Comanda: JOC NOU\n";
            game.StartNewGame();
        }
    }

    return 0;
}