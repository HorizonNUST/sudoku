#include "LineElement.hpp"

engine::gui::elements::LineElement::LineElement(
    uint16_t id,
    const sf::Vector2f &startPoint,
    const sf::Vector2f &endPoint,
    const LineConfig &config)
{
    setID(id);

    sf::Vector2f direction = endPoint - startPoint;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length == 0.f)
        return;

    sf::Vector2f normal = { -direction.y / length, direction.x / length };
    sf::Vector2f offset = normal * (config.thickness * 0.5f);

    // m_line.setPrimitiveType(sf::Quads);
    // m_line.resize(4);

    // // quad vertices
    // m_line[0].position = startPoint + offset;
    // m_line[1].position = startPoint - offset;
    // m_line[2].position = endPoint - offset;
    // m_line[3].position = endPoint + offset;

    // m_line[0].color = config.color;
    // m_line[1].color = config.color;
    // m_line[2].color = config.color;
    // m_line[3].color = config.color;

    // using triangle
    m_line.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_line.resize(6);

    // first triangle
    m_line[0].position = startPoint + offset;
    m_line[1].position = startPoint - offset;
    m_line[2].position = endPoint - offset;
    // second triangle
    m_line[3].position = startPoint + offset;
    m_line[4].position = endPoint - offset;
    m_line[5].position = endPoint + offset;

    m_line[0].color = config.color;
    m_line[1].color = config.color;
    m_line[2].color = config.color;
    m_line[3].color = config.color;
    m_line[4].color = config.color;
    m_line[5].color = config.color;
}

void engine::gui::elements::LineElement::draw(
    sf::RenderTarget &target,
    sf::RenderStates states) const
{
    target.draw(m_line, states);
}
