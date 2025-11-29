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

uint16_t engine::UILayout::AddButtonElement(const std::string &text, const sf::Vector2f &position, std::function<void()> callback, const engine::gui::elements::ButtonConfig &config)
{
    m_last_element_id++;
    m_elements.emplace_back(std::make_unique<engine::gui::elements::ButtonElement>(m_last_element_id, text, position, std::move(callback), config));
    return m_last_element_id;
}

uint16_t engine::UILayout::AddRectangleElement(const sf::Vector2f &position, const sf::Vector2f &size, const engine::gui::elements::RectangleConfig &config)
{
    m_last_element_id++;
    m_elements.emplace_back(std::make_unique<engine::gui::elements::RectangleElement>(m_last_element_id, position, size, config));
    return m_last_element_id;
}

uint16_t engine::UILayout::AddLineElement(const sf::Vector2f &startPoint, const sf::Vector2f &endPoint, const engine::gui::elements::LineConfig &config)
{
    m_last_element_id++;
    m_elements.emplace_back(std::make_unique<engine::gui::elements::LineElement>(m_last_element_id, startPoint, endPoint, config));
    return m_last_element_id;
}

uint16_t engine::UILayout::AddClickableGridElement(const sf::Vector2f &position, const sf::Vector2f &cellSize, size_t sizeX, size_t sizeY)
{
    m_last_element_id++;
    m_elements.emplace_back(std::make_unique<engine::gui::elements::ClickableGridElement>(m_last_element_id, position, cellSize, sizeX, sizeY));
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

    throw std::runtime_error("Element with ID " + std::to_string(id) + " not found in UILayout " + std::to_string(m_id));
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