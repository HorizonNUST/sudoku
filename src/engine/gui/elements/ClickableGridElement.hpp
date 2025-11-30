#pragma once

#include "UIElement.hpp"
#include "ButtonElement.hpp"
#include "ElementConfigs.hpp"

#include <SFML/Graphics.hpp>
#include <functional>
#include <optional>
#include <string>
#include <vector>
#include <stdexcept>
#include <filesystem>

namespace engine::gui::elements
{
    /// @brief creates cells of given width, height
    /// @brief each cell is clickable
    /// @brief loop through all to set text
    class ClickableGridElement : public UIElement
    {
    public:
        ClickableGridElement(uint16_t id, const sf::Vector2f &position, const sf::Vector2f &cellSize, size_t sizeX, size_t sizeY);

        void Update(const GameScreenData &data) override;

        void SetCellClickCallback(std::function<void(size_t, size_t, std::string &)> callback);

        // cell disabled
        inline bool IsCellDisabled(size_t x, size_t y) const
        {
            checkOutOfBounds(x, y);
            return m_cells[getUnwrappedIndex(x, y)].disabled;
        }
        void SetCellDisabled(size_t x, size_t y, bool disabled);

        // cell text
        inline std::string GetCellText(size_t x, size_t y) const
        {
            checkOutOfBounds(x, y);
            size_t index = getUnwrappedIndex(x, y);
            if (m_cells[index].text.has_value())
            {
                return m_cells[index].text->getString();
            }
            else
            {
                return "";
            }
        }
        void SetCellText(size_t x, size_t y, const std::string &text);

        // cell config
        inline ClickableGridElementCellConfig GetCellConfig(size_t x, size_t y) const
        {
            checkOutOfBounds(x, y);
            return m_cells[getUnwrappedIndex(x, y)].config;
        }
        void SetCellConfig(size_t x, size_t y, const ClickableGridElementCellConfig &config);

        // lines
        inline size_t GetNumHorizontalLines() const { return m_size_y - 1; }
        inline size_t GetNumVerticalLines() const { return m_size_x - 1; }
        inline ClickableGridElementLineConfig GetHorizontalLineConfig(size_t index) const
        {
            if (index >= m_size_y - 1)
                throw std::runtime_error("Horizontal line index out of bounds: " + std::to_string(index));

            return m_horizontal_lines[index].config;
        }
        void SetHorizontalLineConfig(size_t index, const ClickableGridElementLineConfig &config);
        inline ClickableGridElementLineConfig GetVerticalLineConfig(size_t index) const
        {
            if (index >= m_size_x - 1)
                throw std::runtime_error("Vertical line index out of bounds: " + std::to_string(index));

            return m_vertical_lines[index].config;
        }
        void SetVerticalLineConfig(size_t index, const ClickableGridElementLineConfig &config);

        // update callback
        void AddUpdateCallback(std::function<void(const GameScreenData &)> callback)
        {
            m_update_callbacks.push_back(std::move(callback));
        }

    public:
        // GETTERS
        inline size_t GetSizeX() const { return m_size_x; }
        inline size_t GetSizeY() const { return m_size_y; }

    private:
        size_t m_size_x = 9;
        size_t m_size_y = 9;

        sf::Font m_font;

        struct Cell
        {
            ClickableGridElementCellConfig config;
            std::optional<sf::Text> text;
            sf::RectangleShape background;
            bool disabled;
        };

        struct Line
        {
            ClickableGridElementLineConfig config;
            sf::VertexArray vertices;
        };

        std::vector<Line> m_vertical_lines;
        std::vector<Line> m_horizontal_lines;
        std::vector<Cell> m_cells;

        bool m_pressedThisFrame = false;
        // callback that tells what box was clicked, and gives a mutable string representation of the cell's text
        std::function<void(size_t, size_t, std::string &)> m_cell_click_callback;
        // update callbacks
        std::vector<std::function<void(const GameScreenData &)>> m_update_callbacks;

        // position of top-left corner of the grid
        sf::Vector2f m_position;
        sf::Vector2f m_cell_size;

        inline size_t getUnwrappedIndex(size_t x, size_t y) const
        {
            return y * m_size_x + x;
        }

        inline void checkOutOfBounds(size_t x, size_t y) const
        {
            if (x < 0 || y < 0 || x >= m_size_x || y >= m_size_y)
                throw std::runtime_error("Index Out Of Bounds: [" + std::to_string(x) + ", " + std::to_string(y) + "]");
        }

        static sf::VertexArray makeThickLine(const sf::Vector2f a, const sf::Vector2f b, const float thickness, const sf::Color color);

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };

}
