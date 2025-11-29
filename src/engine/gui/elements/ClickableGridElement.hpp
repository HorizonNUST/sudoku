#pragma once

#include "UIElement.hpp"
#include "ButtonElement.hpp"
#include "ElementConfigs.hpp"

#include <SFML/Graphics.hpp>
#include <functional>
#include <optional>
#include <string>
#include <vector>

namespace engine::gui::elements
{
    /// @brief creates cells of given width, height
    /// @brief each cell is clickable
    /// @brief loop through all to set text
    class ClickableGridElement : public UIElement
    {
    public:
        ClickableGridElement(uint16_t id, const sf::Vector2f &position, const sf::Vector2f &cellSize);

        void Update(const GameScreenData &data) override;

        void SetCallback(std::function<void(size_t, size_t, std::string &)> callback);

        inline bool IsCellDisabled(size_t x, size_t y) const { return m_cells_disabled[getUnwrappedIndex(x, y)]; }
        void SetCellDisabled(size_t x, size_t y, bool disabled);

        // set text for a specific cell
        void SetCellText(size_t x, size_t y, const std::string &text);

    private:
        size_t m_size_x = 9;
        size_t m_size_y = 9;

        // per-cell configs
        std::vector<ClickableGridElementCellConfig> m_cell_configs;

        sf::Font m_font;
        std::vector<std::optional<sf::Text>> m_cells_text;
        std::vector<sf::RectangleShape> m_cells_background;

        // vertical and horizontal lines
        std::vector<sf::VertexArray> m_lines;

        // list for all cells disabled state
        std::vector<bool> m_cells_disabled{false};

        bool m_pressedThisFrame = false;
        // callback that tells what box was clicked
        std::function<void(size_t, size_t, std::string &)> m_callback;

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

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };

}
