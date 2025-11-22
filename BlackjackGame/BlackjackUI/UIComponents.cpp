#include "UIComponents.h"

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

