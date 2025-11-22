#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <filesystem>
#include "IGameObserver.h"
#include "IGameController.h"
#include "HandData.h"
#include "GameState.h"
#include "CardSuit.h"
#include "CardRank.h"
#include "BlackjackAPI.h"

std::string GetResourcesPath()
{
    namespace fs = std::filesystem;
    
    std::vector<std::string> possiblePaths = {
        "./BlackjackGame/cards",
        "../cards",
        "./cards",
        "../../BlackjackGame/cards",
        "../BlackjackGame/cards"
    };

    for (const auto& path : possiblePaths)
    {
        if (fs::exists(path) && fs::is_directory(path))
        {
            return path;
        }
    }
    
    return "./BlackjackGame/cards";
}

std::string GetCardFileName(CardRank rank, CardSuit suit)
{
    std::string rankStr;
    switch (rank)
    {
        case CardRank::Two:   rankStr = "2"; break;
        case CardRank::Three: rankStr = "3"; break;
        case CardRank::Four:  rankStr = "4"; break;
        case CardRank::Five:  rankStr = "5"; break;
        case CardRank::Six:   rankStr = "6"; break;
        case CardRank::Seven: rankStr = "7"; break;
        case CardRank::Eight: rankStr = "8"; break;
        case CardRank::Nine:  rankStr = "9"; break;
        case CardRank::Ten:   rankStr = "10"; break;
        case CardRank::Jack:  rankStr = "jack"; break;
        case CardRank::Queen: rankStr = "queen"; break;
        case CardRank::King:  rankStr = "king"; break;
        case CardRank::Ace:   rankStr = "ace"; break;
    }

    std::string suitStr;
    switch (suit)
    {
        case CardSuit::Hearts:   suitStr = "hearts"; break;
        case CardSuit::Diamonds: suitStr = "diamonds"; break;
        case CardSuit::Clubs:    suitStr = "clubs"; break;
        case CardSuit::Spades:   suitStr = "spades"; break;
    }

    return rankStr + "_of_" + suitStr + ".png";
}

class CardTextureManager
{
private:
    std::map<std::string, sf::Texture> textures;
    std::string m_resourcesPath;

public:
    CardTextureManager()
    {
        m_resourcesPath = GetResourcesPath();
    }

    bool LoadCardTexture(CardRank rank, CardSuit suit)
    {
        std::string fileName = GetCardFileName(rank, suit);
        std::string fullPath = m_resourcesPath + "/" + fileName;

        if (textures.find(fileName) == textures.end())
        {
            sf::Texture texture;
            if (texture.loadFromFile(fullPath))
            {
                textures[fileName] = std::move(texture);
                return true;
            }
            return false;
        }
        return true;
    }

    sf::Texture* GetCardTexture(CardRank rank, CardSuit suit)
    {
        std::string fileName = GetCardFileName(rank, suit);
        auto it = textures.find(fileName);
        if (it != textures.end())
        {
            return &it->second;
        }
        return nullptr;
    }

    void LoadAllCards()
    {
        for (int r = 2; r <= 14; ++r)
        {
            CardRank rank = static_cast<CardRank>(r);
            LoadCardTexture(rank, CardSuit::Hearts);
            LoadCardTexture(rank, CardSuit::Diamonds);
            LoadCardTexture(rank, CardSuit::Clubs);
            LoadCardTexture(rank, CardSuit::Spades);
        }
    }
};

class SFMLObserver : public IGameObserver
{
public:
    HandData playerHand;
    HandData dealerHand;
    GameState currentState;
    bool gameEnded = false;
    bool playerTurn = false;
    
    // Delay system
    bool waitingForDealer = false;
    sf::Clock dealerDelayClock;
    float dealerDelaySeconds = 1.5f;

    void OnGameStarted(const HandData& playerHand, const HandData& dealerHand) override
    {
        this->playerHand = playerHand;
        this->dealerHand = dealerHand;
        this->gameEnded = false;
        this->playerTurn = true;
        this->waitingForDealer = false;
    }

    void OnPlayerHandChanged(const HandData& playerHand) override
    {
        this->playerHand = playerHand;
    }

    void OnDealerHandChanged(const HandData& dealerHand) override
    {
        this->dealerHand = dealerHand;
    }

    void OnGameEnded(GameState state, const HandData& finalPlayerData, const HandData& finalDealerData) override
    {
        this->currentState = state;
        this->playerHand = finalPlayerData;
        this->dealerHand = finalDealerData;
        this->gameEnded = true;
        this->playerTurn = false;
        this->waitingForDealer = false;
    }

    void OnPlayerTurnBegan() override
    {
        this->playerTurn = true;
    }
};

void DrawCard(sf::RenderWindow& window, CardTextureManager& cardManager, const CardData& card, float x, float y)
{
    sf::Texture* texture = cardManager.GetCardTexture(card.rank, card.suit);
    if (texture)
    {
        sf::Sprite sprite(*texture);
        sprite.setPosition({x, y});
        float scale = 0.3f;
        sprite.setScale({scale, scale});
        window.draw(sprite);
    }
    else
    {
        sf::RectangleShape fallbackCard({100.0f, 140.0f});
        fallbackCard.setPosition({x, y});
        fallbackCard.setFillColor(sf::Color::White);
        fallbackCard.setOutlineColor(sf::Color::Red);
        fallbackCard.setOutlineThickness(2.0f);
        window.draw(fallbackCard);
    }
}

float CalculateCenteredStartX(size_t cardCount, float cardWidth, float spacing, float screenWidth)
{
    if (cardCount == 0) return screenWidth / 2.0f;
    float totalWidth = cardCount * cardWidth + (cardCount - 1) * spacing;
    return (screenWidth - totalWidth) / 2.0f;
}

void DrawHand(sf::RenderWindow& window, CardTextureManager& cardManager, const HandData& hand, float y, float screenWidth, bool showAll = true)
{
    float cardWidth = 100.0f;
    float spacing = 20.0f;
    size_t visibleCards = showAll ? hand.cards.size() : 1;
    float startX = CalculateCenteredStartX(visibleCards, cardWidth, spacing, screenWidth);

    for (size_t i = 0; i < hand.cards.size(); ++i)
    {
        if (showAll || i == 0)
        {
            DrawCard(window, cardManager, hand.cards[i], startX + i * (cardWidth + spacing), y);
        }
        else
        {
            sf::RectangleShape cardBack({cardWidth, 140.0f});
            cardBack.setPosition({startX + i * (cardWidth + spacing), y});
            cardBack.setFillColor(sf::Color::Blue);
            cardBack.setOutlineColor(sf::Color::Black);
            cardBack.setOutlineThickness(2.0f);
            window.draw(cardBack);
        }
    }
}

bool IsButtonClicked(float mouseX, float mouseY, float btnX, float btnY, float btnWidth, float btnHeight)
{
    return mouseX >= btnX && mouseX <= btnX + btnWidth && mouseY >= btnY && mouseY <= btnY + btnHeight;
}

void DrawButton(sf::RenderWindow& window, float x, float y, float width, float height, const std::string& text, sf::Font* font, bool enabled = true)
{
    sf::RectangleShape button({width, height});
    button.setPosition({x, y});
    button.setFillColor(enabled ? sf::Color(100, 150, 100) : sf::Color(80, 80, 80));
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(2.0f);
    window.draw(button);

    if (font)
    {
        sf::Text buttonText(*font, text);
        buttonText.setCharacterSize(18);
        buttonText.setFillColor(sf::Color::White);
        sf::FloatRect textBounds = buttonText.getLocalBounds();
        float textX = x + (width - textBounds.size.x) / 2.0f - textBounds.position.x;
        float textY = y + (height - textBounds.size.y) / 2.0f - textBounds.position.y;
        buttonText.setPosition({textX, textY});
        window.draw(buttonText);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({1000, 700}), "Blackjack SFML");

    // Load Font
    sf::Font font;
    bool fontLoaded = false;

    const char* fontPaths[] = {
        "/System/Library/Fonts/Supplemental/Arial.ttf",
        "/System/Library/Fonts/Helvetica.ttc",
        "/Library/Fonts/Arial.ttf",
        "C:/Windows/Fonts/arial.ttf",
        "C:/Windows/Fonts/calibri.ttf"
    };

    for (const char* path : fontPaths)
    {
        try
        {
            font = sf::Font(path);
            fontLoaded = true;
            break;
        }
        catch (...) { }
    }

    std::unique_ptr<IGameController> game = BlackjackAPI::CreateGameController();
    SFMLObserver observer;
    game->RegisterObserver(&observer);

    CardTextureManager cardManager;
    cardManager.LoadAllCards();

    float hitBtnX = 100.0f, hitBtnY = 600.0f;
    float standBtnX = 250.0f, standBtnY = 600.0f;
    float newGameBtnX = 400.0f, newGameBtnY = 600.0f;
    float btnWidth = 120.0f, btnHeight = 40.0f;

    game->StartNewGame();

    while (window.isOpen())
    {
        if (observer.waitingForDealer)
        {
            if (observer.dealerDelayClock.getElapsedTime().asSeconds() >= observer.dealerDelaySeconds)
            {
                observer.waitingForDealer = false;
                game->PlayerStand();
            }
        }

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mousePressed->button == sf::Mouse::Button::Left && !observer.waitingForDealer)
                {
                    float mouseX = static_cast<float>(mousePressed->position.x);
                    float mouseY = static_cast<float>(mousePressed->position.y);

                    if (IsButtonClicked(mouseX, mouseY, hitBtnX, hitBtnY, btnWidth, btnHeight))
                    {
                        if (observer.playerTurn && !observer.gameEnded)
                        {
                            game->PlayerHit();
                            
                            if (observer.playerHand.value > 21)
                            {
                                observer.waitingForDealer = true;
                                observer.dealerDelayClock.restart();
                            }
                        }
                    }
                    else if (IsButtonClicked(mouseX, mouseY, standBtnX, standBtnY, btnWidth, btnHeight))
                    {
                        if (observer.playerTurn && !observer.gameEnded)
                        {
                            observer.waitingForDealer = true;
                            observer.dealerDelayClock.restart();
                        }
                    }
                    else if (IsButtonClicked(mouseX, mouseY, newGameBtnX, newGameBtnY, btnWidth, btnHeight))
                    {
                        game->StartNewGame();
                    }
                }
            }
        }

        window.clear(sf::Color(34, 139, 34));

        if (observer.waitingForDealer && fontLoaded)
        {
            float elapsed = observer.dealerDelayClock.getElapsedTime().asSeconds();
            float remaining = observer.dealerDelaySeconds - elapsed;
            
            std::string waitText = "Dealerul trage carti in " + 
                                  std::to_string(static_cast<int>(remaining + 1)) + "...";
            
            sf::Text waitMessage(font, waitText, 30);
            waitMessage.setFillColor(sf::Color::Yellow);
            waitMessage.setPosition({250, 340});
            window.draw(waitMessage);
        }

        DrawHand(window, cardManager, observer.dealerHand, 150, 1000.0f, observer.gameEnded);

        DrawHand(window, cardManager, observer.playerHand, 550, 1000.0f, true);

        sf::Font* fontPtr = fontLoaded ? &font : nullptr;
        if (fontPtr)
        {
            std::string dealerScoreText = "Dealer: ";
            dealerScoreText += observer.gameEnded ? std::to_string(observer.dealerHand.value) : "?";
            sf::Text dealerScore(*fontPtr, dealerScoreText, 20);
            dealerScore.setFillColor(sf::Color::White);
            dealerScore.setPosition({400, 105});
            window.draw(dealerScore);

            sf::Text playerScore(*fontPtr, "Jucator: " + std::to_string(observer.playerHand.value), 20);
            playerScore.setFillColor(sf::Color::White);
            playerScore.setPosition({400, 505});
            window.draw(playerScore);

            if (observer.gameEnded)
            {
                std::string resultText;
                switch (observer.currentState)
                {
                    case GameState::PlayerWins:      resultText = "AI CASTIGAT!"; break;
                    case GameState::DealerWins:      resultText = "DEALERUL A CASTIGAT!"; break;
                    case GameState::Push:            resultText = "EGALITATE!"; break;
                    case GameState::PlayerBlackjack: resultText = "BLACKJACK!"; break;
                    case GameState::PlayerBust:      resultText = "BUST!"; break;
                }
                sf::Text result(*fontPtr, resultText, 28);
                result.setFillColor(sf::Color::Yellow);
                result.setPosition({300, 340});
                window.draw(result);
            }
        }

        bool buttonsEnabled = !observer.gameEnded && !observer.waitingForDealer;
        DrawButton(window, hitBtnX, hitBtnY, btnWidth, btnHeight, "HIT", fontPtr, buttonsEnabled);
        DrawButton(window, standBtnX, standBtnY, btnWidth, btnHeight, "STAND", fontPtr, buttonsEnabled);
        DrawButton(window, newGameBtnX, newGameBtnY, btnWidth, btnHeight, "JOC NOU", fontPtr);

        window.display();
    }

    return 0;
}