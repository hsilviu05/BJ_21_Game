#pragma once
#include <SFML/Graphics.hpp>

class FontManager
{
private:
    sf::Font m_font;
    bool m_fontLoaded = false;

    bool TryLoadFont(const char* path);

public:
    FontManager();
    
    sf::Font* GetFont();
    
    bool IsFontLoaded() const;
};


