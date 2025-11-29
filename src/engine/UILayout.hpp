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
#include "RectangleElement.hpp"
#include "LineElement.hpp"
#include "ClickableGridElement.hpp"

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
        uint16_t AddRectangleElement(const sf::Vector2f &position, const sf::Vector2f &size, const engine::gui::elements::RectangleConfig &config = {});
        uint16_t AddLineElement(const sf::Vector2f &startPoint, const sf::Vector2f &endPoint, const engine::gui::elements::LineConfig &config = {});
        uint16_t AddClickableGridElement(const sf::Vector2f &position, const sf::Vector2f &cellSize, size_t sizeX, size_t sizeY);

        engine::gui::elements::UIElement *GetElementById(uint16_t id);

        inline engine::gui::elements::TextElement *GetTextElementById(uint16_t id)
        {
            return dynamic_cast<engine::gui::elements::TextElement *>(GetElementById(id));
        }
        inline engine::gui::elements::ImageElement *GetImageElementById(uint16_t id)
        {
            return dynamic_cast<engine::gui::elements::ImageElement *>(GetElementById(id));
        }
        inline engine::gui::elements::ButtonElement *GetButtonElementById(uint16_t id)
        {
            return dynamic_cast<engine::gui::elements::ButtonElement *>(GetElementById(id));
        }
        inline engine::gui::elements::RectangleElement *GetRectangleElementById(uint16_t id)
        {
            return dynamic_cast<engine::gui::elements::RectangleElement *>(GetElementById(id));
        }
        inline engine::gui::elements::LineElement *GetLineElementById(uint16_t id)
        {
            return dynamic_cast<engine::gui::elements::LineElement *>(GetElementById(id));
        }
        inline engine::gui::elements::ClickableGridElement *GetClickableGridElementById(uint16_t id)
        {
            return dynamic_cast<engine::gui::elements::ClickableGridElement *>(GetElementById(id));
        }

        uint16_t GetID() const { return m_id; }

        void ClearLayout();
        void DisableAllButtons();

        inline bool CompareID(uint16_t id) const
        {
            return m_id == id;
        }

        inline bool operator==(const UILayout &other) const
        {
            return m_id == other.m_id;
        }

    private:
        friend class GameScreen;

        void update(const GameScreenData &data);
        void drawLayout(sf::RenderWindow &window);
    };
}
