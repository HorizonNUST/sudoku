#pragma once

#include "ClickableGridElement.hpp"
#include "TextElement.hpp"
#include "ButtonElement.hpp"

#include <SFML/Graphics.hpp>

struct SudokuBoardStyles
{
    // cell styles
    static inline const engine::gui::elements::ClickableGridElementCellConfig defaultCell = {};

    static inline const engine::gui::elements::ClickableGridElementCellConfig prefilledCell = {
        .fontColor = sf::Color::Yellow,
    };

    static inline const engine::gui::elements::ClickableGridElementCellConfig highlightedCell = {
        .fillCellColor = sf::Color(150, 150, 255),
        .hoverCellFillColor = sf::Color(200, 200, 255),
        .clickCellFillColor = sf::Color(255, 255, 255),
    };

    static inline const engine::gui::elements::ClickableGridElementCellConfig invalidCell = {
        .fontColor = sf::Color::Red,
    };

    // font styles
    static inline const engine::gui::elements::TextConfig cellFont = {
        .fontColor = sf::Color::White,
        .fontSize = 24,
        .fontStyle = sf::Text::Style::Bold,
        .lineHeight = 1.0f,
    };

    static inline const engine::gui::elements::TextConfig invalidFont = {
        .fontColor = sf::Color::Red,
        .fontSize = 24,
        .fontStyle = sf::Text::Style::Bold,
        .lineHeight = 1.0f,
    };

    static inline const engine::gui::elements::TextConfig prefilledFont = {
        .fontColor = sf::Color::Yellow,
        .fontSize = 24,
        .fontStyle = sf::Text::Style::Bold,
        .lineHeight = 1.0f,
    };

    // button styles
    static inline const engine::gui::elements::ButtonConfig defaultToggleButtonConfig = {};
    static inline const engine::gui::elements::ButtonConfig selectedToggleButtonConfig = {
        .fontColor = sf::Color::Green,
    };
};
