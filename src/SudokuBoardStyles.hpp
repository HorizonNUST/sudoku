#pragma once

#include "ClickableGridElement.hpp"
#include "TextElement.hpp"
#include "ButtonElement.hpp"

#include <SFML/Graphics.hpp>

struct SudokuBoardStyles
{
    // cell styles
    static inline const engine::gui::elements::ClickableGridElementCellConfig defaultCell = {
        .fontColor = sf::Color(89, 100, 117),
    };

    static inline const engine::gui::elements::ClickableGridElementCellConfig prefilledCell = {
        .fontColor = sf::Color::White,
        .fillCellColor = sf::Color(50, 50, 50),
    };

    static inline const engine::gui::elements::ClickableGridElementCellConfig highlightedCell = {
        .fontColor = sf::Color(0, 166, 118),
        .fillCellColor = sf::Color(50, 50, 50),
    };

    static inline const engine::gui::elements::ClickableGridElementCellConfig invalidCell = {
        .fontColor = sf::Color::Red,
        .fillCellColor = sf::Color(60, 40, 40),
    };

    // button styles
    static inline const engine::gui::elements::ButtonConfig defaultToggleButtonConfig = {};
    static inline const engine::gui::elements::ButtonConfig selectedToggleButtonConfig = {
        .fontColor = sf::Color(89, 100, 117),
    };

    // text styles (TODO)
};
