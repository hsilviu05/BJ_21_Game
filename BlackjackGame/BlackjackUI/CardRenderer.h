#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "CardData.h"
#include "CardRank.h"
#include "CardSuit.h"
#include "HandData.h"

// Functie pentru a obtine numele fisierului PNG pentru o carte
std::string GetCardFileName(CardRank rank, CardSuit suit);

// Clasa pentru incarcarea si gestionarea texturilor cartilor
class CardTextureManager
{
private:
    std::map<std::string, sf::Texture> textures;
    sf::Texture backTexture;

public:
    // Încarcă textura pentru o carte specifică
    bool LoadCardTexture(CardRank rank, CardSuit suit);
    
    // Returnează textura pentru o carte sau nullptr dacă nu există
    sf::Texture* GetCardTexture(CardRank rank, CardSuit suit);
    
    // Încarcă toate cărțile disponibile
    void LoadAllCards();
};

// Functie pentru desenarea unei carti
void DrawCard(sf::RenderWindow& window, CardTextureManager& cardManager, const CardData& card, float x, float y);

// Functie pentru calcularea pozitiei de start centrata
float CalculateCenteredStartX(size_t cardCount, float cardWidth, float spacing, float screenWidth);

// Functie pentru desenarea unei maini
void DrawHand(sf::RenderWindow& window, CardTextureManager& cardManager, const HandData& hand, float y, float screenWidth, bool showAll = true);

