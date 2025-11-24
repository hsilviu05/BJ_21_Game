#include "GameController.h"

GameController::GameController()
{
    m_gameController = BlackjackAPI::CreateGameController();
    
    m_gameController->RegisterObserver(&m_observer);
    
    m_gameController->StartNewGame();
}

GameController::~GameController()
{
}

void GameController::ProcessMouseClick(float mouseX, float mouseY)
{
    if (IsButtonClicked(mouseX, mouseY, m_hitBtnX, m_hitBtnY, m_btnWidth, m_btnHeight))
    {
        if (m_observer.playerTurn && !m_observer.gameEnded)
        {
            m_gameController->PlayerHit();
        }
    }
    else if (IsButtonClicked(mouseX, mouseY, m_standBtnX, m_standBtnY, m_btnWidth, m_btnHeight))
    {
        if (m_observer.playerTurn && !m_observer.gameEnded)
        {
            m_gameController->PlayerStand();
        }
    }
    else if (IsButtonClicked(mouseX, mouseY, m_newGameBtnX, m_newGameBtnY, m_btnWidth, m_btnHeight))
    {
        m_gameController->StartNewGame();
    }
}


