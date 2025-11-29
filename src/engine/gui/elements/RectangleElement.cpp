#include "RectangleElement.hpp"

engine::gui::elements::RectangleElement::RectangleElement(uint16_t id, const sf::Vector2f &position, const sf::Vector2f &size, const RectangleConfig &config)
{
    m_shape.setPosition(position);
    m_shape.setSize(size);
    m_shape.setFillColor(config.fillColor);
    m_shape.setOutlineThickness(config.outlineThickness);
    m_shape.setOutlineColor(config.outlineColor);
}

void engine::gui::elements::RectangleElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_shape, states);
}
