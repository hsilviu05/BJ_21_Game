#pragma once
#include <SFML/Graphics.hpp>
#include <string>

bool IsButtonClicked(float mouseX, float mouseY, float btnX, float btnY, float btnWidth, float btnHeight);

void DrawButton(sf::RenderWindow& window, float x, float y, float width, float height, const std::string& text, sf::Font* font);


