#include "ClickableGridElement.hpp"

using namespace engine::gui::elements;

ClickableGridElement::ClickableGridElement(uint16_t id, const sf::Vector2f &position, const sf::Vector2f &cellSize, size_t sizeX, size_t sizeY)
    : m_position(position), m_cell_size(cellSize), m_size_x(sizeX), m_size_y(sizeY)
{
    setID(id);

    if (!m_font.openFromFile(CONSTANTS::FONT_PATH))
    {
        throw std::runtime_error("Font not found at: " + std::filesystem::absolute(CONSTANTS::FONT_PATH).string());
    }

    const size_t &totalCells = m_size_x * m_size_y;

    // initilizing containers
    m_cells.resize(totalCells);               // resize fills the vector with default initialized data
    m_lines.reserve(m_size_x + m_size_y - 2); // reserve only changes the size with uninitialized data

    // create grid lines
    // vertical lines; skip first and last
    for (size_t x = 1; x < m_size_x; x++)
    {
        ClickableGridElementLineConfig config;

        sf::Vector2f startPos{
            m_position.x + x * m_cell_size.x,
            m_position.y //
        };
        sf::Vector2f endPos{
            m_position.x + x * m_cell_size.x,
            m_position.y + m_size_y * m_cell_size.y //
        };

        sf::VertexArray line = makeThickLine(startPos, endPos, config.thickness, config.color);
        m_lines.push_back(Line{config, line});
    }

    // horizontal lines; skip first and last
    for (size_t y = 1; y < m_size_y; y++)
    {
        ClickableGridElementLineConfig config;

        sf::Vector2f startPos{
            m_position.x,
            m_position.y + y * m_cell_size.y //
        };
        sf::Vector2f endPos{
            m_position.x + m_size_x * m_cell_size.x,
            m_position.y + y * m_cell_size.y //
        };

        sf::VertexArray line = makeThickLine(startPos, endPos, config.thickness, config.color);
        m_lines.push_back(Line{config, line});
    }

    // backgrounds
    for (size_t y = 0; y < m_size_y; y++)
    {
        for (size_t x = 0; x < m_size_x; x++)
        {
            size_t index = getUnwrappedIndex(x, y);

            ClickableGridElementCellConfig config;
            sf::RectangleShape background;

            background.setPosition({
                m_position.x + x * m_cell_size.x,
                m_position.y + y * m_cell_size.y //
            });

            background.setSize(m_cell_size);
            background.setFillColor(config.fillCellColor);

            m_cells[index].background = background;
            m_cells[index].config = config;

            // text
            sf::Text cellText(m_font);
            cellText.setCharacterSize(config.fontSize);
            cellText.setFillColor(config.fontColor);
            cellText.setStyle(config.fontStyle);
            m_cells[index].text = cellText;
        }
    }
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
        // reset style
        const size_t totalCells = m_size_x * m_size_y;
        for (size_t i = 0; i < totalCells; i++)
        {
            if (m_cells[i].text.has_value())
            {
                m_cells[i].text.value().setFillColor(m_cells[i].config.fontColor);
                m_cells[i].text.value().setStyle(m_cells[i].config.fontStyle);
            }

            m_cells[i].background.setFillColor(m_cells[i].config.fillCellColor);
        }
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
    if (m_cells[index].disabled)
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
                if (m_cells[index].text.has_value())
                {
                    mutable_string = m_cells[index].text.value().getString().toAnsiString();
                }

                // callback
                m_callback(cellX, cellY, mutable_string);

                SetCellText(cellX, cellY, mutable_string);

                // style
                m_cells[index].text.value().setFillColor(m_cells[index].config.fontColor);
                m_cells[index].text.value().setStyle(m_cells[index].config.fontClickStyle);

                m_cells[index].background.setFillColor(m_cells[index].config.clickCellFillColor);
            }

            m_pressedThisFrame = true;
        }
    }
    else
    {
        m_pressedThisFrame = false;

        // hover style
        if (m_cells[index].text.has_value())
        {
            m_cells[index].text.value().setFillColor(m_cells[index].config.fontColor);
            m_cells[index].text.value().setStyle(m_cells[index].config.fontHoverStyle);
        }

        m_cells[index].background.setFillColor(m_cells[index].config.hoverCellFillColor);

        // reset other cells to normal style
        const size_t totalCells = m_size_x * m_size_y;
        for (size_t i = 0; i < totalCells; i++)
        {
            // ignore this cell
            if (i == index)
                continue;

            if (m_cells[i].text.has_value())
            {
                m_cells[i].text.value().setFillColor(m_cells[i].config.fontColor);
                m_cells[i].text.value().setStyle(m_cells[i].config.fontStyle);
            }

            m_cells[i].background.setFillColor(m_cells[i].config.fillCellColor);
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

    m_cells[getUnwrappedIndex(x, y)].disabled = disabled;
}

void ClickableGridElement::SetCellText(size_t x, size_t y, const std::string &text)
{
    checkOutOfBounds(x, y);

    size_t index = getUnwrappedIndex(x, y);

    // if text not initilized initlize with empty object
    if (!m_cells[index].text.has_value())
        m_cells[index].text = sf::Text(m_font);

    sf::Text &cellText = m_cells[index].text.value();
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

void engine::gui::elements::ClickableGridElement::SetCellConfig(size_t x, size_t y, const ClickableGridElementCellConfig &config)
{
    checkOutOfBounds(x, y);

    size_t index = getUnwrappedIndex(x, y);

    m_cells[index].config = config;

    // background
    sf::RectangleShape &background = m_cells[index].background;
    background.setFillColor(config.fillCellColor);
    background.setOutlineThickness(0);

    // text
    if (m_cells[index].text.has_value())
    {
        sf::Text &cellText = m_cells[index].text.value();
        cellText.setFont(m_font);
        cellText.setCharacterSize(config.fontSize);
        cellText.setFillColor(config.fontColor);
        cellText.setStyle(config.fontStyle);
    }
}

void engine::gui::elements::ClickableGridElement::SetLineConfig(size_t index, const ClickableGridElementLineConfig &config)
{
    if (index >= m_size_x + m_size_y + 2)
        throw std::runtime_error("Line index out of bounds: " + std::to_string(index));

    m_lines[index].config = config;

    // line color
    sf::VertexArray &line = m_lines[index].vertices;
    line[0].color = config.color;
    line[1].color = config.color;
}

void ClickableGridElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (IsHidden())
        return;

    const size_t totalCells = m_size_x * m_size_y;

    for (size_t i = 0; i < totalCells; i++)
    {
        // draw backgrounds
        target.draw(m_cells[i].background, states);

        // draw text
        if (m_cells[i].text.has_value())
            target.draw(m_cells[i].text.value(), states);
    }

    // draw lines
    for (const auto &line : m_lines)
    {
        target.draw(line.vertices, states);
    }
}

sf::VertexArray engine::gui::elements::ClickableGridElement::makeThickLine(const sf::Vector2f a, const sf::Vector2f b, const float thickness, const sf::Color color)
{
    sf::Vector2f direction = b - a;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    sf::VertexArray line(sf::PrimitiveType::Triangles, 6);

    if (length == 0.f)
    {
        // degenerate, but return valid VA
        for (int i = 0; i < 6; i++)
            line[i].color = color;
        return line;
    }

    sf::Vector2f normal{
        -direction.y / length,
        direction.x / length //
    };
    sf::Vector2f offset = normal * (thickness * 0.5f);

    // triangle 1
    line[0].position = a + offset; // top right vertex
    line[1].position = a - offset; // top left vertex
    line[2].position = b - offset; // bottom left vertex

    // triangle 2
    line[3].position = a + offset; // top right vertex
    line[4].position = b - offset; // bottom left vertex
    line[5].position = b + offset; // bottom right vertex

    // set color for all vertices
    for (int i = 0; i < 6; i++)
        line[i].color = color;

    return line;
}
