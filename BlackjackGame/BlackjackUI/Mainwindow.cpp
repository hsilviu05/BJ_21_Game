//#include <SFML/Graphics.hpp>
//
//int main()
//{
//    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Blackjack SFML");
//
//    while (window.isOpen())
//    {
//        while (const std::optional event = window.pollEvent())
//        {
//            if (event->is<sf::Event::Closed>())
//            {
//                window.close();
//            }
//            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
//            {
//                if (keyPressed->code == sf::Keyboard::Key::Escape)
//                    window.close();
//            }
//        }
//
//        window.clear(sf::Color::Green);
//
//
//        window.display();
//    }
//    return 0;
//}