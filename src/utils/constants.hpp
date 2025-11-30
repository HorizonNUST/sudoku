#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <string_view>

namespace CONSTANTS
{
    /// @brief For Empty Functions etc.
    constexpr static inline void (*NULLFUNC)() = []() {};
    constexpr static inline sf::Vector2f ZERO_VECTOR2F = {0.f, 0.f};
    constexpr static inline std::string_view FONT_PATH = "assets/fonts/dogica/TTF/dogica.ttf";
    constexpr static inline std::string_view SOUND_BUTTON_PATH = "assets/Sound/button.mp3";
    constexpr static inline sf::Color BACKGROUND_COLOR = sf::Color(0, 0, 0);
}
