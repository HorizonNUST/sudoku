#pragma once
#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "GameScreenData.hpp"

namespace engine::gui::elements
{
    class UIElement : public sf::Drawable
    {
    public:
        UIElement() = default;
        virtual ~UIElement() = default; // always good practice in base classes

        /// @brief Used to pass in screen data to elements
        virtual void Update(const GameScreenData &data) {};

        inline void SetHidden(bool hidden) { m_hidden = hidden; }
        inline bool IsHidden() const { return m_hidden; }

        inline uint16_t GetID() const { return m_id; }

    private:
        uint16_t m_id;
        bool m_hidden = false;

    protected:
        inline void setID(uint16_t id) { m_id = id; }

        /// @brief Draw method to implement for `sf::Drawable`
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
    };
}
