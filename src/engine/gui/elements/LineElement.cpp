#include "LineElement.hpp"

engine::gui::elements::LineElement::LineElement(uint16_t id, const sf::Vector2f &startPoint, const sf::Vector2f &endPoint, const LineConfig &config)
{
    setID(id);

    sf::Vector2f direction = endPoint - startPoint;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length == 0.f)
        return;

    sf::Vector2f normal = {-direction.y / length, direction.x / length};
    sf::Vector2f offset = normal * (config.thickness * 0.5f);

    m_line.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_line.resize(6); // 6 vertices

    // first triangle vertices
    m_line[0].position = startPoint + offset; // top right vertex
    m_line[1].position = startPoint - offset; // top left vertex
    m_line[2].position = endPoint - offset;   // bottom left vertex

    // second triangle vertices
    m_line[3].position = startPoint + offset; // top right vertex
    m_line[4].position = endPoint - offset;   // bottom left vertex
    m_line[5].position = endPoint + offset;   // bottom right vertexs

    // settings color for all vertices
    m_line[0].color = config.color;
    m_line[1].color = config.color;
    m_line[2].color = config.color;
    m_line[3].color = config.color;
    m_line[4].color = config.color;
    m_line[5].color = config.color;
}

void engine::gui::elements::LineElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (IsHidden())
        return;
    target.draw(m_line, states);
}
