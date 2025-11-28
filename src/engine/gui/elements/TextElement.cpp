#include "TextElement.hpp"

engine::gui::elements::TextElement::TextElement(uint16_t id, const std::string &text, const sf::Vector2f &position, const TextConfig &config)
    : m_position(position)
{
    setID(id);

    if (!m_font.openFromFile(CONSTANTS::FONT_PATH))
    {
        throw std::runtime_error("Font not found");
    }

    m_text = sf::Text(m_font);

    m_text->setString(text);
    m_text->setPosition(position);
    m_text->setCharacterSize(config.fontSize);
    m_text->setFillColor(config.fontColor);
    m_text->setStyle(config.fontStyle);
    m_text->setLineSpacing(config.lineHeight);
}

void engine::gui::elements::TextElement::SetText(const std::string &newText)
{
    if (m_text)
        m_text->setString(newText);
}

void engine::gui::elements::TextElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (IsHidden())
        return;

    if (m_text)
        target.draw(*m_text, states);
}
