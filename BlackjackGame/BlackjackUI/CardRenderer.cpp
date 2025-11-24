#include "CardRenderer.h"

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

bool CardTextureManager::LoadCardTexture(CardRank rank, CardSuit suit)
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
        else if (texture.loadFromFile("./BlackjackGame/cards/" + fileName))
        {
            textures[fileName] = std::move(texture);
            return true;
        }
    }
    return textures.find(fileName) != textures.end();
}

sf::Texture* CardTextureManager::GetCardTexture(CardRank rank, CardSuit suit)
{
    std::string fileName = GetCardFileName(rank, suit);
    auto it = textures.find(fileName);
    if (it != textures.end())
    {
        return &it->second;
    }
    return nullptr;
}

void CardTextureManager::LoadAllCards()
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

void DrawCard(sf::RenderWindow& window, CardTextureManager& cardManager, const CardData& card, float x, float y)
{
    sf::Texture* texture = cardManager.GetCardTexture(card.rank, card.suit);
    if (texture)
    {
        sf::Sprite sprite(*texture);
        sprite.setPosition({x, y});
        float scale = 0.25f;
        sprite.setScale({scale, scale});
        window.draw(sprite);
    }
}

float CalculateCenteredStartX(size_t cardCount, float cardWidth, float spacing, float screenWidth)
{
    if (cardCount == 0) return screenWidth / 2.0f;
    
    float totalWidth = cardCount * cardWidth + (cardCount - 1) * spacing;
    return (screenWidth - totalWidth) / 2.0f;
}

void DrawHand(sf::RenderWindow& window, CardTextureManager& cardManager, const HandData& hand, float y, float screenWidth, bool showAll)
{
 
    float cardWidth = 85.0f;
    float spacing = 15.0f;
    
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
         
            float cardHeight = cardWidth * 1.4f;
            sf::RectangleShape cardBack({cardWidth, cardHeight});
            cardBack.setPosition({startX + i * (cardWidth + spacing), y});
            cardBack.setFillColor(sf::Color::Blue);
            cardBack.setOutlineColor(sf::Color::Black);
            cardBack.setOutlineThickness(2.0f);
            window.draw(cardBack);
        }
    }
}

