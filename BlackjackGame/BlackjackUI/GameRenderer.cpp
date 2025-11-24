#include "GameRenderer.h"
#include "UIComponents.h"
#include "GameState.h"

GameRenderer::GameRenderer(SFMLGameObserver* observer, FontManager* fontManager, CardTextureManager* cardManager, float windowWidth, float windowHeight)
    : m_observer(observer)
    , m_fontManager(fontManager)
    , m_cardManager(cardManager)
    , m_windowWidth(windowWidth)
    , m_windowHeight(windowHeight)
{
}

void GameRenderer::Render(sf::RenderWindow& window)
{
    DrawTable(window);
    DrawScoreLabels(window);
    DrawScores(window);
    DrawResult(window);
    DrawCards(window);
    DrawButtons(window);
}

void GameRenderer::DrawTable(sf::RenderWindow& window)
{
    window.clear(sf::Color(34, 139, 34));
    
    float borderThickness = 8.0f;
    
    sf::RectangleShape outerBorder({m_windowWidth, m_windowHeight});
    outerBorder.setPosition({0.0f, 0.0f});
    outerBorder.setFillColor(sf::Color::Transparent);
    outerBorder.setOutlineColor(sf::Color(0, 100, 0, 255));
    outerBorder.setOutlineThickness(borderThickness);
    window.draw(outerBorder);
    
    float innerMargin = borderThickness;
    sf::RectangleShape innerBorder({m_windowWidth - 2 * innerMargin, m_windowHeight - 2 * innerMargin});
    innerBorder.setPosition({innerMargin, innerMargin});
    innerBorder.setFillColor(sf::Color::Transparent);
    innerBorder.setOutlineColor(sf::Color(50, 150, 50, 200));
    innerBorder.setOutlineThickness(3.0f);
    window.draw(innerBorder);
    

    sf::Color lineColor(20, 120, 20, 30); 
    float lineSpacing = 40.0f;
    
    for (float y = 0; y < m_windowHeight; y += lineSpacing)
    {
        sf::Vertex line[2] = {
            sf::Vertex{{0.0f, y}, lineColor},
            sf::Vertex{{m_windowWidth, y + m_windowWidth * 0.3f}, lineColor}
        };
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }
}

void GameRenderer::DrawScoreLabels(sf::RenderWindow& window)
{
    
    sf::RectangleShape dealerLabel({250.0f, 35.0f});
    dealerLabel.setPosition({375.0f, 80.0f}); 
    dealerLabel.setFillColor(sf::Color(0, 0, 0, 220));
    dealerLabel.setOutlineColor(sf::Color::White);
    dealerLabel.setOutlineThickness(2.0f);
    window.draw(dealerLabel);

    
    sf::RectangleShape playerLabel({250.0f, 35.0f});
    playerLabel.setPosition({375.0f, 680.0f});
    playerLabel.setFillColor(sf::Color(0, 0, 0, 220));
    playerLabel.setOutlineColor(sf::Color::White);
    playerLabel.setOutlineThickness(2.0f);
    window.draw(playerLabel);
}

void GameRenderer::DrawScores(sf::RenderWindow& window)
{
    sf::Font* fontPtr = m_fontManager->GetFont();
    if (!fontPtr) return;

    std::string dealerScoreText = "Dealer: ";
    if (m_observer->gameEnded || m_observer->dealerHand.cards.size() > 1)
    {
        dealerScoreText += std::to_string(m_observer->dealerHand.value);
    }
    else
    {
        dealerScoreText += "?";
    }
    sf::Text dealerScore(*fontPtr, dealerScoreText);
    dealerScore.setCharacterSize(24);
    dealerScore.setFillColor(sf::Color::White);
    dealerScore.setStyle(sf::Text::Bold);
    sf::FloatRect dealerTextBounds = dealerScore.getLocalBounds();
    float dealerTextX = 500.0f - dealerTextBounds.size.x / 2.0f - dealerTextBounds.position.x;
    dealerScore.setPosition({dealerTextX, 80.0f}); 
    window.draw(dealerScore);

    std::string playerScoreText = "Jucator: " + std::to_string(m_observer->playerHand.value);
    sf::Text playerScore(*fontPtr, playerScoreText);
    playerScore.setCharacterSize(24);
    playerScore.setFillColor(sf::Color::White);
    playerScore.setStyle(sf::Text::Bold);
    sf::FloatRect playerTextBounds = playerScore.getLocalBounds();
    float playerTextX = 500.0f - playerTextBounds.size.x / 2.0f - playerTextBounds.position.x;
    playerScore.setPosition({playerTextX, 680.0f});
    window.draw(playerScore);
}

void GameRenderer::DrawResult(sf::RenderWindow& window)
{
    if (!m_observer->gameEnded) return;

    sf::Font* fontPtr = m_fontManager->GetFont();
    if (!fontPtr) return;

    std::string resultText;
    sf::Color backgroundColor;
    sf::Color textColor;
    
    switch (m_observer->currentState)
    {
        case GameState::PlayerWins:
            resultText = "AI CASTIGAT!";
            backgroundColor = sf::Color(0, 200, 0, 230);
            textColor = sf::Color::White;
            break;
        case GameState::PlayerBlackjack:
            resultText = "BLACKJACK! AI CASTIGAT!";
            backgroundColor = sf::Color(0, 200, 0, 230);
            textColor = sf::Color::White;
            break;
        case GameState::DealerWins:
            resultText = "DEALERUL A CASTIGAT!";
            backgroundColor = sf::Color(200, 0, 0, 230);
            textColor = sf::Color::White;
            break;
        case GameState::PlayerBust:
            resultText = "BUST! AI DEPASIT 21!";
            backgroundColor = sf::Color(200, 0, 0, 230);
            textColor = sf::Color::White;
            break;
        case GameState::Push:
            resultText = "EGALITATE!";
            backgroundColor = sf::Color(255, 255, 0, 230);
            textColor = sf::Color::Black;
            break;
    }

    sf::RectangleShape overlay({m_windowWidth, m_windowHeight});
    overlay.setPosition({0.0f, 0.0f});
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(overlay);

    float boxWidth = 500.0f;
    float boxHeight = 100.0f;
    float boxX = (m_windowWidth - boxWidth) / 2.0f;
    float boxY = (m_windowHeight - boxHeight) / 2.0f;
    
    sf::RectangleShape resultBox({boxWidth, boxHeight});
    resultBox.setPosition({boxX, boxY});
    resultBox.setFillColor(backgroundColor);
    resultBox.setOutlineColor(sf::Color::White);
    resultBox.setOutlineThickness(4.0f);
    window.draw(resultBox);

    sf::Text result(*fontPtr, resultText);
    result.setCharacterSize(36);
    result.setFillColor(textColor);
    result.setStyle(sf::Text::Bold);
    
    sf::FloatRect resultBounds = result.getLocalBounds();
    float resultX = boxX + (boxWidth - resultBounds.size.x) / 2.0f - resultBounds.position.x;
    float resultY = boxY + (boxHeight - resultBounds.size.y) / 2.0f - resultBounds.position.y;
    result.setPosition({resultX, resultY});
    window.draw(result);
}

void GameRenderer::DrawCards(sf::RenderWindow& window)
{
    bool showAllDealerCards = m_observer->gameEnded;
    DrawHand(window, *m_cardManager, m_observer->dealerHand, 120, m_windowWidth, showAllDealerCards);

    DrawHand(window, *m_cardManager, m_observer->playerHand, 480, m_windowWidth, true);
}

void GameRenderer::DrawButtons(sf::RenderWindow& window)
{
    sf::Font* fontPtr = m_fontManager->GetFont();
    
    float btnStartX = 50.0f;
    float btnY = 730.0f; 
    float btnWidth = 120.0f;
    float btnHeight = 40.0f;
    float btnSpacing = 10.0f;

    float hitBtnX = btnStartX;
    float standBtnX = btnStartX + btnWidth + btnSpacing;
    float newGameBtnX = btnStartX + 2 * (btnWidth + btnSpacing);

    DrawButton(window, hitBtnX, btnY, btnWidth, btnHeight, "HIT", fontPtr);
    DrawButton(window, standBtnX, btnY, btnWidth, btnHeight, "STAND", fontPtr);
    DrawButton(window, newGameBtnX, btnY, btnWidth, btnHeight, "JOC NOU", fontPtr);
}

