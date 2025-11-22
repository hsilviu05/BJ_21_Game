#include "GameController.h"

GameController::GameController()
{
    // Înregistrează observer-ul la game engine
    m_game.RegisterObserver(&m_observer);
    
    // Porneste primul joc
    m_game.StartNewGame();
}

void GameController::ProcessMouseClick(float mouseX, float mouseY)
{
    // Verifica click pe butonul HIT
    if (IsButtonClicked(mouseX, mouseY, m_hitBtnX, m_hitBtnY, m_btnWidth, m_btnHeight))
    {
        if (m_observer.playerTurn && !m_observer.gameEnded)
        {
            m_game.PlayerHit();
        }
    }
    // Verifica click pe butonul STAND
    else if (IsButtonClicked(mouseX, mouseY, m_standBtnX, m_standBtnY, m_btnWidth, m_btnHeight))
    {
        if (m_observer.playerTurn && !m_observer.gameEnded)
        {
            m_game.PlayerStand();
        }
    }
    // Verifica click pe butonul JOC NOU
    else if (IsButtonClicked(mouseX, mouseY, m_newGameBtnX, m_newGameBtnY, m_btnWidth, m_btnHeight))
    {
        m_game.StartNewGame();
    }
}

