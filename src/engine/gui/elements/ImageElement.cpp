#include "ImageElement.hpp"

engine::gui::elements::ImageElement::ImageElement(uint16_t id, const std::string &imagePath, const sf::Vector2f &position)
{
    setID(id);
    
    if (!m_texture.loadFromFile(imagePath))
    {
        throw("Texture Not found at:" + imagePath);
    }

    m_sprite.emplace(m_texture);
    m_sprite->setPosition(position);
}

inline void engine::gui::elements::ImageElement::setImage(const std::string &newPath)
{
    if (!m_texture.loadFromFile(newPath))
    {
        throw("Texture Not found at:" + newPath);
    }

    m_sprite->setTexture(m_texture);
}

void engine::gui::elements::ImageElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (IsHidden())
        return;

    if (m_sprite)
        target.draw(*m_sprite, states);
}
