#include <SFML/Graphics.hpp>
#include "FontManager.h"
#include "CardRenderer.h"
#include "GameRenderer.h"
#include "GameController.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 800 }), "Blackjack SFML");

    FontManager fontManager;

    GameController gameController;

    CardTextureManager cardManager;
    cardManager.LoadAllCards();

    float windowWidth = 1000.0f;
    float windowHeight = 700.0f;
    GameRenderer gameRenderer(gameController.GetObserver(), &fontManager, &cardManager, windowWidth, windowHeight);

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

                    gameController.ProcessMouseClick(mouseX, mouseY);
                }
            }
        }

        gameRenderer.Render(window);

        window.display();
    }

    return 0;
}
