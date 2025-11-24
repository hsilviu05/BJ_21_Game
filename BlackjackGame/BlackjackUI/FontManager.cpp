#include "FontManager.h"

FontManager::FontManager()
{
    const char *fontPaths[] = {
        "C:/Windows/Fonts/arial.ttf",
        "C:/Windows/Fonts/calibri.ttf",
        "C:/Windows/Fonts/tahoma.ttf",
        "C:/Windows/Fonts/verdana.ttf",
        "/System/Library/Fonts/Supplemental/Arial.ttf",
        "/System/Library/Fonts/Helvetica.ttc",
        "/Library/Fonts/Arial.ttf",
        "/System/Library/Fonts/SFNS.ttf",
    };

    for (const char *path : fontPaths)
    {
        if (TryLoadFont(path))
        {
            m_fontLoaded = true;
            break;
        }
    }
}

bool FontManager::TryLoadFont(const char *path)
{
    try
    {
        m_font = sf::Font(path);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

sf::Font *FontManager::GetFont()
{
    if (m_fontLoaded)
    {
        return &m_font;
    }
    return nullptr;
}

bool FontManager::IsFontLoaded() const
{
    return m_fontLoaded;
}

