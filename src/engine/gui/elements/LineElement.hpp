#pragma once
#include <functional>

#include "utils.hpp"
#include "constants.hpp"

#include "UIElement.hpp"
#include "GameScreenData.hpp"
#include "ElementConfigs.hpp"

namespace engine::gui::elements
{
    class LineElement : public UIElement
    {
    public:
        LineElement(uint16_t id, const sf::Vector2f &startPoint, const sf::Vector2f &endPoint, const LineConfig &config);

    private:
        sf::VertexArray m_line;

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
