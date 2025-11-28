#pragma once
#include "UIElement.hpp"

#include "utils.hpp"
#include "constants.hpp"

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
    class TextElement : public UIElement
    {
    public:
        TextElement(uint16_t id, const std::string &text, const sf::Vector2f &position, const TextConfig &config = {});

        /// @brief Set the text of the Element
        /// @param newText The New Text
        void SetText(const std::string &newText);

    private:
        sf::Font m_font;
        std::optional<sf::Text> m_text;
        sf::Vector2f m_position;

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
