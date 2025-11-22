#pragma once
#include <SFML/Graphics.hpp>
#include "GameObserver.h"
#include "FontManager.h"
#include "CardRenderer.h"

// Clasa care coordonează toate componentele de rendering
// Gestionează desenarea mesei, cărților, butoanelor, textului și rezultatelor
class GameRenderer
{
private:
    SFMLGameObserver* m_observer;
    FontManager* m_fontManager;
    CardTextureManager* m_cardManager;
    float m_windowWidth;
    float m_windowHeight;

    // Metode private pentru desenarea diferitelor componente
    void DrawTable(sf::RenderWindow& window);
    void DrawScoreLabels(sf::RenderWindow& window);
    void DrawScores(sf::RenderWindow& window);
    void DrawResult(sf::RenderWindow& window);
    void DrawCards(sf::RenderWindow& window);
    void DrawButtons(sf::RenderWindow& window);

public:
    GameRenderer(SFMLGameObserver* observer, FontManager* fontManager, CardTextureManager* cardManager, float windowWidth, float windowHeight);
    
    // Metoda principală care desenează tot UI-ul
    void Render(sf::RenderWindow& window);
};

