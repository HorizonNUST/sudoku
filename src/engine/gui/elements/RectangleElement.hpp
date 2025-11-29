#pragma once
#include <functional>

#include "utils.hpp"
#include "constants.hpp"

#include "UIElement.hpp"
#include "GameScreenData.hpp"
#include "ElementConfigs.hpp"

namespace engine::gui::elements
{
    class RectangleElement : public UIElement
    {
    public:
        RectangleElement(uint16_t id, const sf::Vector2f &position, const sf::Vector2f &size, const RectangleConfig &config = {});

    private:
        sf::RectangleShape m_shape;

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
