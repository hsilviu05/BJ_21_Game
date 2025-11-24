#pragma once
#include "BlackjackAPI.h"
#include "IGameController.h"
#include "GameObserver.h"
#include "UIComponents.h"
#include <memory>


class GameController
{
private:
    std::unique_ptr<IGameController> m_gameController;
    SFMLGameObserver m_observer;
    
    float m_hitBtnX = 50.0f;
    float m_hitBtnY = 730.0f;
    float m_standBtnX = 180.0f;
    float m_standBtnY = 730.0f;
    float m_newGameBtnX = 310.0f;
    float m_newGameBtnY = 730.0f;
    float m_btnWidth = 120.0f;
    float m_btnHeight = 40.0f;

public:
    GameController();
    ~GameController();
    
    void ProcessMouseClick(float mouseX, float mouseY);
    
    SFMLGameObserver* GetObserver() { return &m_observer; }
    
    float GetHitBtnX() const { return m_hitBtnX; }
    float GetHitBtnY() const { return m_hitBtnY; }
    float GetStandBtnX() const { return m_standBtnX; }
    float GetStandBtnY() const { return m_standBtnY; }
    float GetNewGameBtnX() const { return m_newGameBtnX; }
    float GetNewGameBtnY() const { return m_newGameBtnY; }
    float GetBtnWidth() const { return m_btnWidth; }
    float GetBtnHeight() const { return m_btnHeight; }
};

