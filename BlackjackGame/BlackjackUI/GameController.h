#pragma once
#include "GameEngine.h"
#include "GameObserver.h"
#include "UIComponents.h"

// Clasa care gestionează interacțiunea cu backend-ul și evenimentele
// Conectează UI-ul cu logica de joc
class GameController
{
private:
    GameEngine m_game;
    SFMLGameObserver m_observer;
    
    // Pozițiile butoanelor (pentru detectarea click-urilor) - mutate in stanga jos, in linie, mai jos
    float m_hitBtnX = 50.0f;
    float m_hitBtnY = 680.0f;
    float m_standBtnX = 180.0f; // 50 + 120 + 10
    float m_standBtnY = 680.0f;
    float m_newGameBtnX = 310.0f; // 50 + 2*(120 + 10)
    float m_newGameBtnY = 680.0f;
    float m_btnWidth = 120.0f;
    float m_btnHeight = 40.0f;

public:
    GameController();
    
    // Procesează un click de mouse
    void ProcessMouseClick(float mouseX, float mouseY);
    
    // Getter-e pentru acces la componente
    GameEngine* GetGame() { return &m_game; }
    SFMLGameObserver* GetObserver() { return &m_observer; }
    
    // Getter-e pentru pozițiile butoanelor (pentru rendering)
    float GetHitBtnX() const { return m_hitBtnX; }
    float GetHitBtnY() const { return m_hitBtnY; }
    float GetStandBtnX() const { return m_standBtnX; }
    float GetStandBtnY() const { return m_standBtnY; }
    float GetNewGameBtnX() const { return m_newGameBtnX; }
    float GetNewGameBtnY() const { return m_newGameBtnY; }
    float GetBtnWidth() const { return m_btnWidth; }
    float GetBtnHeight() const { return m_btnHeight; }
};

