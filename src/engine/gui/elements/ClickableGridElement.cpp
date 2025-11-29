#include "ClickableGridElement.hpp"

using namespace engine::gui::elements;

ClickableGridElement::ClickableGridElement(uint16_t id, const sf::Vector2f &position, const sf::Vector2f &cellSize)
    : m_position(position), m_cell_size(cellSize), m_size_x(9), m_size_y(9)
{
    setID(id);

    if (!m_font.openFromFile(CONSTANTS::FONT_PATH))
    {
        throw std::runtime_error("Font not found");
    }

    const size_t &totalCells = m_size_x * m_size_y;

    // initilizing containers
    m_cells_text.resize(totalCells);
    m_cells_background.resize(totalCells);
    m_lines.reserve(m_size_x + m_size_y - 2); // vertical + horizontal lines
    m_cells_disabled.resize(totalCells, false);

    // create grid lines
    // vertical lines
    for (size_t x = 1; x < m_size_x; x++)
    {
        sf::VertexArray line(sf::PrimitiveType::LineStrip, 2);

        // vertices position
        line[0].position = sf::Vector2f{
            m_position.x + x * m_cell_size.x,
            m_position.y //
        };
        line[1].position = sf::Vector2f{
            m_position.x + x * m_cell_size.x,
            m_position.y + m_size_y * m_cell_size.y //
        };

        // color
        line[0].color = sf::Color::White;
        line[1].color = sf::Color::White;

        m_lines.push_back(line);
    }

    // horizontal lines
    for (size_t y = 1; y < m_size_y; y++)
    {
        sf::VertexArray line(sf::PrimitiveType::LineStrip, 2);
        
        // vertices position
        line[0].position = sf::Vector2f{
            m_position.x,
            m_position.y + y * m_cell_size.y //
        };
        line[1].position = sf::Vector2f{
            m_position.x + m_size_x * m_cell_size.x,
            m_position.y + y * m_cell_size.y //
        };

        // color
        line[0].color = sf::Color::White;
        line[1].color = sf::Color::White;

        m_lines.push_back(line);
    }

    // backgrounds
    for (size_t y = 0; y < m_size_y; y++)
    {
        for (size_t x = 0; x < m_size_x; x++)
        {
            size_t index = getUnwrappedIndex(x, y);

            sf::RectangleShape rect;
            rect.setPosition({
                m_position.x + x * m_cell_size.x,
                m_position.y + y * m_cell_size.y //
            });

            rect.setSize(m_cell_size);
            rect.setFillColor(sf::Color::Transparent);

            m_cells_background[index] = rect;
        }
    }
}

void ClickableGridElement::SetCallback(std::function<void(size_t, size_t, std::string &)> callback)
{
    m_callback = std::move(callback);
}

void ClickableGridElement::SetCellDisabled(size_t x, size_t y, bool disabled)
{
    checkOutOfBounds(x, y);

    m_cells_disabled[getUnwrappedIndex(x, y)] = disabled;
}

void ClickableGridElement::SetCellText(size_t x, size_t y, const std::string &text)
{
    checkOutOfBounds(x, y);

    size_t index = getUnwrappedIndex(x, y);

    // if text not initilized initlize with empty object
    if (!m_cells_text[index].has_value())
        m_cells_text[index] = sf::Text(m_font);

    sf::Text &cellText = m_cells_text[index].value();
    cellText.setString(sf::String{text});

    // center the text
    sf::FloatRect bounds = cellText.getLocalBounds();
    cellText.setOrigin({
        bounds.position.x + bounds.size.x * 0.5f,
        bounds.position.y + bounds.size.y * 0.5f //
    });
    cellText.setPosition({
        m_position.x + (x + 0.5f) * m_cell_size.x,
        m_position.y + (y + 0.5f) * m_cell_size.y //
    });
}

void ClickableGridElement::Update(const GameScreenData &data)
{
    const int &mouseX = data.mousePos.x;
    const int &mouseY = data.mousePos.y;

    const float &gridLeft = m_position.x;
    const float &gridTop = m_position.y;
    const float &gridRight = gridLeft + m_size_x * m_cell_size.x;
    const float &gridBottom = gridTop + m_size_y * m_cell_size.y;

    // if mouse is outside grid
    if (mouseX < gridLeft || mouseX >= gridRight || mouseY < gridTop || mouseY >= gridBottom)
    {
        m_pressedThisFrame = false;
        return;
    }

    // compute cell coordinates; ignores decimals
    size_t cellX = static_cast<size_t>((mouseX - gridLeft) / m_cell_size.x);
    size_t cellY = static_cast<size_t>((mouseY - gridTop) / m_cell_size.y);

    // bounds safety; ignore out-of-bounds clicks
    if (cellX >= m_size_x || cellY >= m_size_y)
    {
        m_pressedThisFrame = false;
        return;
    }

    size_t index = getUnwrappedIndex(cellX, cellY);

    // If cell is disabled, ignore input but still allow pressed state to reset on release.
    if (m_cells_disabled[index])
    {
        if (!data.isClicking)
            m_pressedThisFrame = false;
        return;
    }

    if (data.isClicking)
    {
        if (!m_pressedThisFrame)
        {
            if (m_callback)
            {
                std::string mutable_string;

                // get current value
                if (m_cells_text[index].has_value())
                {
                    mutable_string = m_cells_text[index].value().getString().toAnsiString();
                }

                // callback
                m_callback(cellX, cellY, mutable_string);

                SetCellText(cellX, cellY, mutable_string);
            }

            m_pressedThisFrame = true;
        }
    }
    else
    {
        m_pressedThisFrame = false;
    }
}

void ClickableGridElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (IsHidden())
        return;

    const size_t totalCells = m_size_x * m_size_y;

    // draw lines
    for (const auto &line : m_lines)
    {
        target.draw(line, states);
    }

    // draw backgrounds
    for (size_t i = 0; i < totalCells; i++)
    {
        target.draw(m_cells_background[i], states);
    }

    // draw texts
    for (size_t i = 0; i < totalCells; i++)
    {
        if (m_cells_text[i].has_value())
            target.draw(m_cells_text[i].value(), states);
    }
}
