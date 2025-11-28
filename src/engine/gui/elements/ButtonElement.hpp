#pragma once
#include <functional>

#include "utils.hpp"
#include "constants.hpp"

#include "UIElement.hpp"
#include "GameScreenData.hpp"

namespace engine::gui::elements
{
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

    class ButtonElement : public UIElement
    {
    public:
        ButtonElement(uint16_t id, const std::string &text, const sf::Vector2f &position, std::function<void()> callback = CONSTANTS::NULLFUNC, ButtonConfig config = {});

        /// @brief Set the Text Inside Button
        /// @param newText The New Text String
        inline void SetText(const std::string &newText);

        void Update(const GameScreenData &data) override;

        /// @brief Add callback for when button is clicked
        /// @param callback the callback of type `std::function<void()>` i.e a lambda that takes nothing as parameters
        void SetCallback(std::function<void()> callback);

        inline bool IsDisabled() const { return m_isDisabled; }
        /// @brief Disable the button
        inline void SetDisabled(bool disabled)
        {
            m_isDisabled = disabled;

            if (m_isDisabled && m_text)
            {
                m_text->setFillColor(m_config.fontDisabledColor);
                m_text->setStyle(m_config.fontDisabledStyle);
            }
            else if (m_text)
            {
                m_text->setFillColor(m_config.fontColor);
                m_text->setStyle(m_config.fontStyle);
            }
        }

    private:
        ButtonConfig m_config;

        sf::Font m_font;
        std::optional<sf::Text> m_text;
        sf::RectangleShape m_shape;

        bool m_isDisabled = false;

        bool m_pressedThisFrame = false;
        std::function<void()> m_callback;

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
