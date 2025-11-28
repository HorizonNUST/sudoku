#include "ButtonElement.hpp"
#include "utils.hpp"

engine::gui::elements::ButtonElement::ButtonElement(uint16_t id, const std::string &text, const sf::Vector2f &position, std::function<void()> callback, ButtonConfig config)
    : m_callback(callback), m_config(config)
{
    setID(id);

    if (!m_font.openFromFile(CONSTANTS::FONT_PATH))
    {
        throw std::runtime_error("Font not found");
    }

    m_shape.setFillColor(config.fillColor);
    m_shape.setOutlineThickness(config.outlineThickness);
    m_shape.setOutlineColor(config.outlineColor);

    m_text = sf::Text(m_font);
    m_text->setString(text);
    m_text->setCharacterSize(config.fontSize);
    m_text->setFillColor(config.fontColor);
    m_text->setLineSpacing(config.lineHeight);

    sf::FloatRect textBounds = m_text->getLocalBounds();

    m_shape.setPosition({
        position.x + config.outlineThickness,
        position.y + config.outlineThickness //
    });
    m_shape.setSize({
        textBounds.size.x + 2.f * config.padding.x,
        textBounds.size.y + 2.f * config.padding.y //
    });

    m_text->setOrigin(textBounds.position + textBounds.size / 2.f);
    m_text->setPosition(
        m_shape.getPosition() + m_shape.getSize() / 2.f //
    );
}

inline void engine::gui::elements::ButtonElement::SetText(const std::string &newText)
{
    if (m_text)
        m_text->setString(newText);
}

void engine::gui::elements::ButtonElement::Update(const GameScreenData &data)
{
    if (m_is_disabled)
        return;

    // aliases
    const int &mousePosX = data.mousePos.x;
    const int &mousePosY = data.mousePos.y;

    const float &topSidePos = m_shape.getPosition().y;
    const float &bottomSidePos = topSidePos + m_shape.getSize().y;
    const float &leftSizePos = m_shape.getPosition().x;
    const float &rightSidePos = leftSizePos + m_shape.getSize().x;

    if ((mousePosX >= leftSizePos && mousePosX < rightSidePos) &&
        (mousePosY >= topSidePos && mousePosY < bottomSidePos))
    {
        if (data.isClicking)
        {
            // click logic
            if (!m_pressedThisFrame)
            {
                DEBUG_PRINT("CLICK");
                m_callback();
                m_text->setStyle(m_config.fontClickStyle);

                m_pressedThisFrame = true;
            }
        }
        else
        {
            // hover logic
            m_text->setStyle(m_config.fontHoverStyle);
            m_pressedThisFrame = false;
        }
    }
    else
    {
        m_text->setStyle(m_config.fontStyle);
    }
}

void engine::gui::elements::ButtonElement::SetCallback(std::function<void()> callback)
{
    m_callback = callback;
}

void engine::gui::elements::ButtonElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (IsHidden())
        return;

    target.draw(m_shape, states);

    if (m_text)
        target.draw(*m_text, states);
}
