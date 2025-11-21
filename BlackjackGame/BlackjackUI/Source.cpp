#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <memory>
#include "IGameObserver.h"
#include "IGameController.h"
#include "HandData.h"
#include "GameState.h"
#include "CardSuit.h"
#include "CardRank.h"
#include "GameEngine.h"

// Functie pentru a obtine numele fisierului PNG pentru o carte
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

// Clasa pentru incarcarea si gestionarea texturilor cartilor
class CardTextureManager
{
private:
    std::map<std::string, sf::Texture> textures;
    sf::Texture backTexture;

public:
    bool LoadCardTexture(CardRank rank, CardSuit suit)
    {
        std::string fileName = GetCardFileName(rank, suit);
        std::string path = "../cards/" + fileName;
        
        if (textures.find(fileName) == textures.end())
        {
            sf::Texture texture;
            if (texture.loadFromFile(path))
            {
                textures[fileName] = std::move(texture);
                return true;
            }
        }
        return textures.find(fileName) != textures.end();
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

// Observer pentru actualizarea UI-ului
class SFMLObserver : public IGameObserver
{
public:
    HandData playerHand;
    HandData dealerHand;
    GameState currentState;
    bool gameEnded = false;
    bool playerTurn = false;

    virtual void OnGameStarted(const HandData& playerHand, const HandData& dealerHand) override
    {
        this->playerHand = playerHand;
        this->dealerHand = dealerHand;
        this->gameEnded = false;
        this->playerTurn = true;
        this->currentState = GameState::PlayerWins; // placeholder
    }

    virtual void OnPlayerHandChanged(const HandData& playerHand) override
    {
        this->playerHand = playerHand;
    }

    virtual void OnDealerHandChanged(const HandData& dealerHand) override
    {
        this->dealerHand = dealerHand;
    }

    virtual void OnGameEnded(GameState state, const HandData& finalPlayerData, const HandData& finalDealerData) override
    {
        this->currentState = state;
        this->playerHand = finalPlayerData;
        this->dealerHand = finalDealerData;
        this->gameEnded = true;
        this->playerTurn = false;
    }

    virtual void OnPlayerTurnBegan() override
    {
        this->playerTurn = true;
    }
};

// Functie pentru desenarea unei carti
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
}

// Functie pentru calcularea pozitiei de start centrata
float CalculateCenteredStartX(size_t cardCount, float cardWidth, float spacing, float screenWidth)
{
    if (cardCount == 0) return screenWidth / 2.0f;
    
    float totalWidth = cardCount * cardWidth + (cardCount - 1) * spacing;
    return (screenWidth - totalWidth) / 2.0f;
}

// Functie pentru desenarea unei maini
void DrawHand(sf::RenderWindow& window, CardTextureManager& cardManager, const HandData& hand, float y, float screenWidth, bool showAll = true)
{
    float cardWidth = 100.0f;
    float spacing = 20.0f;
    
    // Calculeaza numarul de carti vizibile pentru centrare
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
            // Deseneaza spatele cartii pentru cartile ascunse
            sf::RectangleShape cardBack({cardWidth, 140.0f});
            cardBack.setPosition({startX + i * (cardWidth + spacing), y});
            cardBack.setFillColor(sf::Color::Blue);
            cardBack.setOutlineColor(sf::Color::Black);
            cardBack.setOutlineThickness(2.0f);
            window.draw(cardBack);
        }
    }
}

// Functie pentru desenarea unui buton
bool IsButtonClicked(float mouseX, float mouseY, float btnX, float btnY, float btnWidth, float btnHeight)
{
    return mouseX >= btnX && mouseX <= btnX + btnWidth &&
           mouseY >= btnY && mouseY <= btnY + btnHeight;
}

void DrawButton(sf::RenderWindow& window, float x, float y, float width, float height, const std::string& text, sf::Font* font)
{
    sf::RectangleShape button({width, height});
    button.setPosition({x, y});
    button.setFillColor(sf::Color(100, 150, 100));
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(2.0f);
    window.draw(button);

    // Deseneaza textul pe buton daca avem font
    if (font)
    {
        sf::Text buttonText(*font, text);
        buttonText.setCharacterSize(18);
        buttonText.setFillColor(sf::Color::White);
        
        // Centreaza textul pe buton
        sf::FloatRect textBounds = buttonText.getLocalBounds();
        float textX = x + (width - textBounds.size.x) / 2.0f - textBounds.position.x;
        float textY = y + (height - textBounds.size.y) / 2.0f - textBounds.position.y;
        buttonText.setPosition({textX, textY});
        
        window.draw(buttonText);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 700 }), "Blackjack SFML");

    // Incarca fontul (incearca mai multe locatii comune)
    sf::Font font;
    bool fontLoaded = false;
    
    // Listeaza locatiile comune pentru fonturi Windows
    const char* fontPaths[] = {
        "C:/Windows/Fonts/arial.ttf",
        "C:/Windows/Fonts/calibri.ttf",
        "C:/Windows/Fonts/tahoma.ttf",
        "C:/Windows/Fonts/verdana.ttf"
    };
    
    for (const char* path : fontPaths)
    {
        try
        {
            font = sf::Font(path);
            fontLoaded = true;
            break;
        }
        catch (...)
        {
            // Continua cu urmatorul font
        }
    }

    // Initializeaza jocul
    GameEngine game;
    SFMLObserver observer;
    game.RegisterObserver(&observer);

    // Incarca texturile cartilor
    CardTextureManager cardManager;
    cardManager.LoadAllCards();

    // Butoane
    float hitBtnX = 100.0f;
    float hitBtnY = 600.0f;
    float standBtnX = 250.0f;
    float standBtnY = 600.0f;
    float newGameBtnX = 400.0f;
    float newGameBtnY = 600.0f;
    float btnWidth = 120.0f;
    float btnHeight = 40.0f;

    // Porneste primul joc
    game.StartNewGame();

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mousePressed->button == sf::Mouse::Button::Left)
                {
                    float mouseX = static_cast<float>(mousePressed->position.x);
                    float mouseY = static_cast<float>(mousePressed->position.y);

                    // Verifica click pe butoane
                    if (IsButtonClicked(mouseX, mouseY, hitBtnX, hitBtnY, btnWidth, btnHeight))
                    {
                        if (observer.playerTurn && !observer.gameEnded)
                        {
                            game.PlayerHit();
                        }
                    }
                    else if (IsButtonClicked(mouseX, mouseY, standBtnX, standBtnY, btnWidth, btnHeight))
                    {
                        if (observer.playerTurn && !observer.gameEnded)
                        {
                            game.PlayerStand();
                        }
                    }
                    else if (IsButtonClicked(mouseX, mouseY, newGameBtnX, newGameBtnY, btnWidth, btnHeight))
                    {
                        game.StartNewGame();
                    }
                }
            }
        }

        // Deseneaza masa (fundal verde)
        window.clear(sf::Color(34, 139, 34)); // Verde inchis pentru masa

        // Deseneaza etichete pentru scoruri cu text (centrate)
        // Eticheta pentru dealer (centrata)
        sf::RectangleShape dealerLabel({200.0f, 30.0f});
        dealerLabel.setPosition({400.0f, 100.0f});
        dealerLabel.setFillColor(sf::Color(50, 50, 50, 180));
        window.draw(dealerLabel);

        // Eticheta pentru jucator (centrata)
        sf::RectangleShape playerLabel({200.0f, 30.0f});
        playerLabel.setPosition({400.0f, 500.0f});
        playerLabel.setFillColor(sf::Color(50, 50, 50, 180));
        window.draw(playerLabel);

        // Mesaj de rezultat (doar forma, fara text)
        if (observer.gameEnded)
        {
            sf::RectangleShape resultBox({400.0f, 60.0f});
            resultBox.setPosition({300.0f, 340.0f});
            resultBox.setFillColor(sf::Color(255, 255, 0, 200));
            resultBox.setOutlineColor(sf::Color::Black);
            resultBox.setOutlineThickness(3.0f);
            window.draw(resultBox);
        }

        // Deseneaza cartile dealerului (centrate pe mijloc, in jumatatea de sus)
        bool showAllDealerCards = observer.gameEnded;
        float windowWidth = 1000.0f;
        DrawHand(window, cardManager, observer.dealerHand, 150, windowWidth, showAllDealerCards);

        // Deseneaza cartile jucatorului (centrate pe mijloc, in jumatatea de jos)
        DrawHand(window, cardManager, observer.playerHand, 550, windowWidth, true);

        // Deseneaza textul pentru sume
        sf::Font* fontPtr = fontLoaded ? &font : nullptr;
        if (fontPtr)
        {
            // Suma dealerului
            std::string dealerScoreText = "Dealer: ";
            if (observer.gameEnded || observer.dealerHand.cards.size() > 1)
            {
                dealerScoreText += std::to_string(observer.dealerHand.value);
            }
            else
            {
                dealerScoreText += "?";
            }
            sf::Text dealerScore(*fontPtr, dealerScoreText);
            dealerScore.setCharacterSize(20);
            dealerScore.setFillColor(sf::Color::White);
            // Centreaza textul pe eticheta
            sf::FloatRect dealerTextBounds = dealerScore.getLocalBounds();
            float dealerTextX = 400.0f + (200.0f - dealerTextBounds.size.x) / 2.0f - dealerTextBounds.position.x;
            dealerScore.setPosition({dealerTextX, 105.0f});
            window.draw(dealerScore);

            // Suma jucatorului
            std::string playerScoreText = "Jucator: " + std::to_string(observer.playerHand.value);
            sf::Text playerScore(*fontPtr, playerScoreText);
            playerScore.setCharacterSize(20);
            playerScore.setFillColor(sf::Color::White);
            // Centreaza textul pe eticheta
            sf::FloatRect playerTextBounds = playerScore.getLocalBounds();
            float playerTextX = 400.0f + (200.0f - playerTextBounds.size.x) / 2.0f - playerTextBounds.position.x;
            playerScore.setPosition({playerTextX, 505.0f});
            window.draw(playerScore);

            // Mesaj de rezultat
            if (observer.gameEnded)
            {
                std::string resultText;
                switch (observer.currentState)
                {
                    case GameState::PlayerWins:
                        resultText = "AI CASTIGAT!";
                        break;
                    case GameState::DealerWins:
                        resultText = "DEALERUL A CASTIGAT!";
                        break;
                    case GameState::Push:
                        resultText = "EGALITATE!";
                        break;
                    case GameState::PlayerBlackjack:
                        resultText = "BLACKJACK! AI CASTIGAT!";
                        break;
                    case GameState::PlayerBust:
                        resultText = "BUST! AI DEPASIT 21!";
                        break;
                }
                sf::Text result(*fontPtr, resultText);
                result.setCharacterSize(28);
                result.setFillColor(sf::Color::Black);
                result.setStyle(sf::Text::Bold);
                
                // Centreaza textul in caseta
                sf::FloatRect resultBounds = result.getLocalBounds();
                float resultX = 300.0f + (400.0f - resultBounds.size.x) / 2.0f - resultBounds.position.x;
                float resultY = 340.0f + (60.0f - resultBounds.size.y) / 2.0f - resultBounds.position.y;
                result.setPosition({resultX, resultY});
                window.draw(result);
            }
        }

        // Deseneaza butoanele
        DrawButton(window, hitBtnX, hitBtnY, btnWidth, btnHeight, "HIT", fontPtr);
        DrawButton(window, standBtnX, standBtnY, btnWidth, btnHeight, "STAND", fontPtr);
        DrawButton(window, newGameBtnX, newGameBtnY, btnWidth, btnHeight, "JOC NOU", fontPtr);

        window.display();
    }

    return 0;
}
