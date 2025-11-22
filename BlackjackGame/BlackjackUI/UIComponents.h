#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// Functie pentru verificarea daca un click este in interiorul unui buton
bool IsButtonClicked(float mouseX, float mouseY, float btnX, float btnY, float btnWidth, float btnHeight);

// Functie pentru desenarea unui buton cu text
void DrawButton(sf::RenderWindow& window, float x, float y, float width, float height, const std::string& text, sf::Font* font);

