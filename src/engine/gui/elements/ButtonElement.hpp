#pragma once
#include <functional>

#include "utils.hpp"
#include "constants.hpp"

#include "UIElement.hpp"
#include "GameScreenData.hpp"
#include "ElementConfigs.hpp"

namespace engine::gui::elements
{
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

        inline bool IsDisabled() const { return m_is_disabled; }
        /// @brief Disable the button
        inline void SetDisabled(bool disabled)
        {
            m_is_disabled = disabled;

            if (m_is_disabled && m_text)
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

        bool m_is_disabled = false;

        bool m_pressedThisFrame = false;
        std::function<void()> m_callback;

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
