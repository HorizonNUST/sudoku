#pragma once
#include <SFML/Graphics.hpp>

namespace engine
{
    struct GameScreenData
    {
        sf::Vector2i mousePos;
        bool isClicking;
    };
}
