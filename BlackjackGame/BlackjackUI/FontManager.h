#pragma once
#include <SFML/Graphics.hpp>

// Clasa pentru gestionarea fonturilor
// Încearcă să încarce fonturi din mai multe locații comune Windows
class FontManager
{
private:
    sf::Font m_font;
    bool m_fontLoaded = false;

    // Încearcă să încarce fontul dintr-un path
    bool TryLoadFont(const char* path);

public:
    FontManager();
    
    // Returnează fontul sau nullptr dacă nu este încărcat
    sf::Font* GetFont();
    
    // Verifică dacă fontul este disponibil
    bool IsFontLoaded() const;
};

