#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "CardData.h"
#include "CardRank.h"
#include "CardSuit.h"
#include "HandData.h"

std::string GetCardFileName(CardRank rank, CardSuit suit);

class CardTextureManager
{
private:
    std::map<std::string, sf::Texture> textures;
    sf::Texture backTexture;

public:
    bool LoadCardTexture(CardRank rank, CardSuit suit);
    
    sf::Texture* GetCardTexture(CardRank rank, CardSuit suit);
    
    void LoadAllCards();
};

void DrawCard(sf::RenderWindow& window, CardTextureManager& cardManager, const CardData& card, float x, float y);

float CalculateCenteredStartX(size_t cardCount, float cardWidth, float spacing, float screenWidth);

void DrawHand(sf::RenderWindow& window, CardTextureManager& cardManager, const HandData& hand, float y, float screenWidth, bool showAll = true);


