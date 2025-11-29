#pragma once
#include <SFML/Graphics.hpp>

namespace engine::gui::elements
{
    /// @brief Used to set the style for the button
    struct TextConfig
    {
        sf::Color fontColor = sf::Color::White;
        unsigned int fontSize = 16;
        /// @brief input `sf::Text::Style::`
        sf::Text::Style fontStyle = sf::Text::Style::Regular;

        /// @brief Line height multiplier (1.0 = normal, 1.5 = 1.5x spacing, etc.)
        float lineHeight = 2.f;
    };

    /// @brief Used to set the style for the button
    struct ButtonConfig
    {
        /// @brief Padding around the Text
        sf::Vector2f padding = {16.f, 8.f};

        /// @brief Color of the button backgorund
        sf::Color fillColor = sf::Color::Black;
        float outlineThickness = 2.f;
        sf::Color outlineColor = sf::Color::White;

        sf::Color fontColor = sf::Color::White;
        /// @brief Color of the font when button is disabled
        sf::Color fontDisabledColor = sf::Color(100, 100, 100);

        unsigned int fontSize = 16;
        /// @brief input `sf::Text::Style::`
        sf::Text::Style fontStyle = sf::Text::Style::Regular;
        /// @brief input `sf::Text::Style::`
        sf::Text::Style fontHoverStyle = sf::Text::Style::Underlined;
        /// @brief input `sf::Text::Style::`
        sf::Text::Style fontClickStyle = sf::Text::Style::Italic;
        /// @brief input `sf::Text::Style::`
        sf::Text::Style fontDisabledStyle = sf::Text::Style::Italic;

        /// @brief Line height multiplier (1.0 = normal, 1.5 = 1.5x spacing, etc.)
        float lineHeight = 2.f;
    };

    struct LineConfig
    {
        sf::Color color = sf::Color::White;
        float thickness = 2.f;
    };

    struct RectangleConfig
    {
        sf::Color fillColor = sf::Color::Transparent;
        float outlineThickness = 2.f;
        sf::Color outlineColor = sf::Color::White;
    };

    /// @brief config for one cell in `ClickableGridElement`
    struct ClickableGridElementCellConfig
    {
        sf::Color fontColor = sf::Color::White;
        sf::Color fontDisabledColor = sf::Color(100, 100, 100);

        unsigned int fontSize = 16;
        sf::Text::Style fontStyle = sf::Text::Style::Regular;
        sf::Text::Style fontHoverStyle = sf::Text::Style::Underlined;
        sf::Text::Style fontClickStyle = sf::Text::Style::Italic;
        sf::Text::Style fontDisabledStyle = sf::Text::Style::Italic;

        sf::Color fillColor = sf::Color::Transparent;
        sf::Color outlineColor = sf::Color::White;
        float outlineThickness = 2.f;

        sf::Color hoverFillColor = sf::Color(50, 50, 50);
        sf::Color clickFillColor = sf::Color(100, 100, 100);
    };
}