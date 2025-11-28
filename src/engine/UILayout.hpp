#pragma once
#include <array>
#include <functional>
#include <cstdlib>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "UIElement.hpp"
#include "TextElement.hpp"
#include "ImageElement.hpp"
#include "ButtonElement.hpp"
#include "utils.hpp"

#include "GameScreen.hpp"
#include "GameScreenData.hpp"

namespace engine
{
    class GameScreen;

    /// @brief To generate a Layout containing `UIElements`
    class UILayout
    {
    private:
        uint8_t m_id;
        std::vector<std::unique_ptr<engine::gui::elements::UIElement>> m_elements;

        uint16_t m_last_element_id = 0;

    public:
        UILayout(uint16_t id);

        uint16_t AddTextElement(const std::string &text, const sf::Vector2f &position, const engine::gui::elements::TextConfig &config = {});
        uint16_t AddImageElement(const std::string &imagePath, const sf::Vector2f &position);
        uint16_t AddButtonElement(const std::string &text, const sf::Vector2f &position, std::function<void()> callback = CONSTANTS::NULLFUNC, const engine::gui::elements::ButtonConfig &config = {});

        void ClearLayout();
        void DisableAllButtons();

        engine::gui::elements::UIElement *GetElementById(uint16_t id);

        bool operator==(const UILayout &other) const
        {
            return m_id == other.m_id;
        }

    private:
        friend class GameScreen;

        void update(const GameScreenData &data);
        void drawLayout(sf::RenderWindow &window);
    };
}
