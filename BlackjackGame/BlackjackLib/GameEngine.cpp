#include "GameEngine.h"

GameEngine::GameEngine()
{
    m_deck.Shuffle();
}

void GameEngine::StartNewGame()
{
    m_deck.Shuffle(); 
    m_playerHand.Clear();
    m_dealerHand.Clear();

    m_playerHand.AddCard(m_deck.DrawCard());
    m_dealerHand.AddCard(m_deck.DrawCard());
    m_playerHand.AddCard(m_deck.DrawCard());
    m_dealerHand.AddCard(m_deck.DrawCard());

    
    HandData playerFullHand = m_playerHand.ToData();

    HandData dealerVisibleHand;
    Card visibleCard = m_dealerHand.GetCard(0);
    
    dealerVisibleHand.cards.push_back(visibleCard.ToData());
    dealerVisibleHand.value = visibleCard.GetValue(); 

    for (IGameObserver* obs : m_observers)
    {
        obs->OnGameStarted(playerFullHand, dealerVisibleHand);
    }

    if (playerFullHand.value == 21)
    {
        NotifyDealerHandChanged();
        
        if (m_dealerHand.GetValue() == 21)
        {
            NotifyGameEnded(GameState::Push);
        }
        else
        {
            NotifyGameEnded(GameState::PlayerBlackjack); 
        }
    }
    else
    {
        NotifyPlayerTurnBegan();
    }
}

void GameEngine::PlayerHit()
{
    m_playerHand.AddCard(m_deck.DrawCard());
    NotifyPlayerHandChanged();
    if (m_playerHand.GetValue() == 21)
    {
        DealerTurn();
    }
    if(m_playerHand.GetValue() > 21)
    {
        m_gameState = GameState::PlayerBust;
        NotifyGameEnded(m_gameState);
    }
}

void GameEngine::PlayerStand()
{
    DealerTurn();
}

void GameEngine::DealerTurn()
{
    while (m_dealerHand.GetValue() < 17)
    {
        m_dealerHand.AddCard(m_deck.DrawCard());
        NotifyDealerHandChanged();
    }

    int playerValue = m_playerHand.GetValue();
    int dealerValue = m_dealerHand.GetValue();

    if (dealerValue > 21)
    {
        NotifyGameEnded(GameState::PlayerWins);
    }
    else if (playerValue > dealerValue)
    {
        NotifyGameEnded(GameState::PlayerWins);
    }
    else if (playerValue < dealerValue)
    {
        NotifyGameEnded(GameState::DealerWins);
    }
    else
    {
        NotifyGameEnded(GameState::Push);
    }
}

void GameEngine::RegisterObserver(IGameObserver* observer)
{
    m_observers.push_back(observer);
}

void GameEngine::UnregisterObserver(IGameObserver* observer)
{
    m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
}

void GameEngine::NotifyGameStarted()
{
    for (IGameObserver* obs : m_observers)
    {
        obs->OnGameStarted(m_playerHand.ToData(), m_dealerHand.ToData());
    }
}

void GameEngine::NotifyPlayerHandChanged()
{
    for (IGameObserver* obs : m_observers)
    {
        obs->OnPlayerHandChanged(m_playerHand.ToData());
    }
}

void GameEngine::NotifyDealerHandChanged()
{
    for (IGameObserver* obs : m_observers)
    {
        obs->OnDealerHandChanged(m_dealerHand.ToData());
    }
}

void GameEngine::NotifyGameEnded(GameState state)
{
    m_gameState = state;
    for (IGameObserver* obs : m_observers)
    {
        obs->OnGameEnded(m_gameState, m_playerHand.ToData(), m_dealerHand.ToData());
    }
}

void GameEngine::NotifyPlayerTurnBegan()
{
    for (IGameObserver* obs : m_observers)
    {
        obs->OnPlayerTurnBegan();
    }
}