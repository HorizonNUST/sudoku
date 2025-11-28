#include "UILayout.hpp"

engine::UILayout::UILayout(uint16_t id) : m_id(id)
{
}

uint16_t engine::UILayout::AddTextElement(const std::string &text, const sf::Vector2f &position, const engine::gui::elements::TextConfig &config)
{
    m_last_element_id++;
    m_elements.emplace_back(std::make_unique<engine::gui::elements::TextElement>(m_last_element_id, text, position, config));
    return m_last_element_id;
}

uint16_t engine::UILayout::AddImageElement(const std::string &imagePath, const sf::Vector2f &position)
{
    m_last_element_id++;
    m_elements.emplace_back(std::make_unique<engine::gui::elements::ImageElement>(m_last_element_id, imagePath, position));
    return m_last_element_id;
}

uint16_t engine::UILayout::AddButtonElement(const std::string &text, const sf::Vector2f &position, std::function<void()> callback, const engine::gui::elements::ButtonConfig& config)
{
    m_last_element_id++;
    m_elements.emplace_back(std::make_unique<engine::gui::elements::ButtonElement>(m_last_element_id, text, position, std::move(callback), config));
    return m_last_element_id;
}

void engine::UILayout::ClearLayout()
{
    m_elements.clear();
    m_last_element_id = 0;
}

void engine::UILayout::DisableAllButtons()
{
    for (const auto &element : m_elements)
    {
        auto buttonElement = dynamic_cast<engine::gui::elements::ButtonElement *>(element.get());
        if (buttonElement)
        {
            buttonElement->SetDisabled(true);
        }
    }
}

engine::gui::elements::UIElement *engine::UILayout::GetElementById(uint16_t id)
{
    for (const std::unique_ptr<engine::gui::elements::UIElement> &element : m_elements)
    {
        if (element->GetID() == id)
        {
            return element.get();
        }
    }

    return nullptr;
}

void engine::UILayout::update(const GameScreenData &data)
{
    for (const auto &element : m_elements)
    {
        element->Update(data);
    }
}

void engine::UILayout::drawLayout(sf::RenderWindow &window)
{
    for (auto &element : m_elements)
    {
        window.draw(*element);
    }
}