#include "GameObserver.h"

void SFMLGameObserver::OnGameStarted(const HandData& playerHand, const HandData& dealerHand)
{
    this->playerHand = playerHand;
    this->dealerHand = dealerHand;
    this->gameEnded = false;
    this->playerTurn = true;
    this->currentState = GameState::PlayerWins; 
}

void SFMLGameObserver::OnPlayerHandChanged(const HandData& playerHand)
{
    this->playerHand = playerHand;
}

void SFMLGameObserver::OnDealerHandChanged(const HandData& dealerHand)
{
    this->dealerHand = dealerHand;
}

void SFMLGameObserver::OnGameEnded(GameState state, const HandData& finalPlayerData, const HandData& finalDealerData)
{
    this->currentState = state;
    this->playerHand = finalPlayerData;
    this->dealerHand = finalDealerData;
    this->gameEnded = true;
    this->playerTurn = false;
}

void SFMLGameObserver::OnPlayerTurnBegan()
{
    this->playerTurn = true;
}


