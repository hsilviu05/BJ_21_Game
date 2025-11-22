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
    // Deseneaza masa (fundal verde cu pattern)
    window.clear(sf::Color(34, 139, 34)); // Verde inchis pentru masa
    
    // Adauga un border elegant pentru masa
    float borderThickness = 8.0f;
    
    // Border exterior (mai inchis)
    sf::RectangleShape outerBorder({m_windowWidth, m_windowHeight});
    outerBorder.setPosition({0.0f, 0.0f});
    outerBorder.setFillColor(sf::Color::Transparent);
    outerBorder.setOutlineColor(sf::Color(0, 100, 0, 255)); // Verde foarte inchis
    outerBorder.setOutlineThickness(borderThickness);
    window.draw(outerBorder);
    
    // Border interior (mai deschis, pentru efect de adancime)
    float innerMargin = borderThickness;
    sf::RectangleShape innerBorder({m_windowWidth - 2 * innerMargin, m_windowHeight - 2 * innerMargin});
    innerBorder.setPosition({innerMargin, innerMargin});
    innerBorder.setFillColor(sf::Color::Transparent);
    innerBorder.setOutlineColor(sf::Color(50, 150, 50, 200)); // Verde deschis
    innerBorder.setOutlineThickness(3.0f);
    window.draw(innerBorder);
    
    // Adauga un pattern subtil (linii diagonale subtile pentru textura)
    // Deseneaza linii subtile pentru a da impresia de textura a mesei
    sf::Color lineColor(20, 120, 20, 30); // Verde foarte subtil
    float lineSpacing = 40.0f;
    
    // Linii diagonale subtile
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
    // Eticheta pentru dealer (sub cartile dealerului, centrata, mai jos)
    // Cartile dealerului sunt la Y=120, cu scale 0.25 o carte are ~120px inaltime, deci se termina la ~240px
    sf::RectangleShape dealerLabel({250.0f, 35.0f});
    dealerLabel.setPosition({375.0f, 300.0f}); // Sub cartile dealerului, mai jos
    dealerLabel.setFillColor(sf::Color(0, 0, 0, 220));
    dealerLabel.setOutlineColor(sf::Color::White);
    dealerLabel.setOutlineThickness(2.0f);
    window.draw(dealerLabel);

    // Eticheta pentru jucator (sub cartile jucatorului, centrata, mai jos)
    // Cartile jucatorului sunt la Y=480, cu scale 0.25 o carte are ~120px inaltime, deci se termina la ~600px
    sf::RectangleShape playerLabel({250.0f, 35.0f});
    playerLabel.setPosition({375.0f, 660.0f}); // Sub cartile jucatorului, mai jos
    playerLabel.setFillColor(sf::Color(0, 0, 0, 220));
    playerLabel.setOutlineColor(sf::Color::White);
    playerLabel.setOutlineThickness(2.0f);
    window.draw(playerLabel);
}

void GameRenderer::DrawScores(sf::RenderWindow& window)
{
    sf::Font* fontPtr = m_fontManager->GetFont();
    if (!fontPtr) return;

    // Suma dealerului (sub cartile dealerului)
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
    // Centreaza textul pe eticheta (centrat pe 375 + 250/2 = 500)
    sf::FloatRect dealerTextBounds = dealerScore.getLocalBounds();
    float dealerTextX = 500.0f - dealerTextBounds.size.x / 2.0f - dealerTextBounds.position.x;
    dealerScore.setPosition({dealerTextX, 305.0f}); // Sub cartile dealerului, mai jos
    window.draw(dealerScore);

    // Suma jucatorului (sub cartile jucatorului)
    std::string playerScoreText = "Jucator: " + std::to_string(m_observer->playerHand.value);
    sf::Text playerScore(*fontPtr, playerScoreText);
    playerScore.setCharacterSize(24);
    playerScore.setFillColor(sf::Color::White);
    playerScore.setStyle(sf::Text::Bold);
    // Centreaza textul pe eticheta (centrat pe 375 + 250/2 = 500)
    sf::FloatRect playerTextBounds = playerScore.getLocalBounds();
    float playerTextX = 500.0f - playerTextBounds.size.x / 2.0f - playerTextBounds.position.x;
    playerScore.setPosition({playerTextX, 665.0f}); // Sub cartile jucatorului, mai jos
    window.draw(playerScore);
}

void GameRenderer::DrawResult(sf::RenderWindow& window)
{
    if (!m_observer->gameEnded) return;

    sf::Font* fontPtr = m_fontManager->GetFont();
    if (!fontPtr) return;

    // Determina textul si culoarea in functie de rezultat
    std::string resultText;
    sf::Color backgroundColor;
    sf::Color textColor;
    
    switch (m_observer->currentState)
    {
        case GameState::PlayerWins:
            resultText = "AI CASTIGAT!";
            backgroundColor = sf::Color(0, 200, 0, 230); // Verde
            textColor = sf::Color::White;
            break;
        case GameState::PlayerBlackjack:
            resultText = "BLACKJACK! AI CASTIGAT!";
            backgroundColor = sf::Color(0, 200, 0, 230); // Verde
            textColor = sf::Color::White;
            break;
        case GameState::DealerWins:
            resultText = "DEALERUL A CASTIGAT!";
            backgroundColor = sf::Color(200, 0, 0, 230); // Rosu
            textColor = sf::Color::White;
            break;
        case GameState::PlayerBust:
            resultText = "BUST! AI DEPASIT 21!";
            backgroundColor = sf::Color(200, 0, 0, 230); // Rosu
            textColor = sf::Color::White;
            break;
        case GameState::Push:
            resultText = "EGALITATE!";
            backgroundColor = sf::Color(255, 255, 0, 230); // Galben
            textColor = sf::Color::Black;
            break;
    }

    // Overlay semi-transparent pentru a face mesajul mai vizibil
    sf::RectangleShape overlay({m_windowWidth, m_windowHeight});
    overlay.setPosition({0.0f, 0.0f});
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(overlay);

    // Caseta de rezultat (centrata pe ecran)
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

    // Textul de rezultat (centrat in caseta)
    sf::Text result(*fontPtr, resultText);
    result.setCharacterSize(36);
    result.setFillColor(textColor);
    result.setStyle(sf::Text::Bold);
    
    // Centreaza textul in caseta
    sf::FloatRect resultBounds = result.getLocalBounds();
    float resultX = boxX + (boxWidth - resultBounds.size.x) / 2.0f - resultBounds.position.x;
    float resultY = boxY + (boxHeight - resultBounds.size.y) / 2.0f - resultBounds.position.y;
    result.setPosition({resultX, resultY});
    window.draw(result);
}

void GameRenderer::DrawCards(sf::RenderWindow& window)
{
    // Deseneaza cartile dealerului (centrate pe mijloc, in jumatatea de sus)
    bool showAllDealerCards = m_observer->gameEnded;
    DrawHand(window, *m_cardManager, m_observer->dealerHand, 120, m_windowWidth, showAllDealerCards);

    // Deseneaza cartile jucatorului (centrate pe mijloc, in jumatatea de jos, dar mai sus pentru a nu iesi din cadru)
    // Ajustat Y pentru a fi mai sus și a nu iesi din cadru (fereastra are 700px inaltime)
    DrawHand(window, *m_cardManager, m_observer->playerHand, 480, m_windowWidth, true);
}

void GameRenderer::DrawButtons(sf::RenderWindow& window)
{
    sf::Font* fontPtr = m_fontManager->GetFont();
    
    // Butoane mutate in stanga jos, aranjate orizontal in linie, mai jos
    float btnStartX = 50.0f;
    float btnY = 680.0f; // Mai jos
    float btnWidth = 120.0f;
    float btnHeight = 40.0f;
    float btnSpacing = 10.0f; // Spatiu intre butoane

    float hitBtnX = btnStartX;
    float standBtnX = btnStartX + btnWidth + btnSpacing;
    float newGameBtnX = btnStartX + 2 * (btnWidth + btnSpacing);

    DrawButton(window, hitBtnX, btnY, btnWidth, btnHeight, "HIT", fontPtr);
    DrawButton(window, standBtnX, btnY, btnWidth, btnHeight, "STAND", fontPtr);
    DrawButton(window, newGameBtnX, btnY, btnWidth, btnHeight, "JOC NOU", fontPtr);
}

