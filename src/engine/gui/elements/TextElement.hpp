#pragma once
#include "UIElement.hpp"

#include "utils.hpp"
#include "constants.hpp"

#include "ElementConfigs.hpp"

namespace engine::gui::elements
{
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
