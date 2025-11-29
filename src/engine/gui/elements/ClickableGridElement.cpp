#include "ClickableGridElement.hpp"

using namespace engine::gui::elements;

ClickableGridElement::ClickableGridElement(uint16_t id, const sf::Vector2f &position, const sf::Vector2f &cellSize, size_t sizeX, size_t sizeY)
    : m_position(position), m_cell_size(cellSize), m_size_x(sizeX), m_size_y(sizeY)
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
    m_cells_config.resize(totalCells);
    m_cells_disabled.resize(totalCells, false);

    m_lines_config.reserve(m_size_x + m_size_y - 2);
    m_lines.reserve(m_size_x + m_size_y - 2);

    // create grid lines
    // vertical lines; skip first and last
    for (size_t x = 1; x < m_size_x; x++)
    {
        sf::VertexArray line;
        ClickableGridElementLineConfig config;

        sf::Vector2f startPoint = sf::Vector2f{
            m_position.x + x * m_cell_size.x,
            m_position.y //
        };
        sf::Vector2f endPoint = sf::Vector2f{
            m_position.x + x * m_cell_size.x,
            m_position.y + m_size_y * m_cell_size.y //
        };
        sf::Vector2f direction = endPoint - startPoint;

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length == 0.f)
            return;

        sf::Vector2f normal = {-direction.y / length, direction.x / length};
        sf::Vector2f offset = normal * (config.thickness * 0.5f);

        line.setPrimitiveType(sf::PrimitiveType::Triangles);
        line.resize(6); // 6 vertices

        // first triangle vertices
        line[0].position = startPoint + offset; // top right vertex
        line[1].position = startPoint - offset; // top left vertex
        line[2].position = endPoint - offset;   // bottom left vertex

        // second triangle vertices
        line[3].position = startPoint + offset; // top right vertex
        line[4].position = endPoint - offset;   // bottom left vertex
        line[5].position = endPoint + offset;   // bottom right vertexs

        // settings color for all vertices
        line[0].color = config.color;
        line[1].color = config.color;
        line[2].color = config.color;
        line[3].color = config.color;
        line[4].color = config.color;
        line[5].color = config.color;

        m_lines.push_back(line);
        m_lines_config.push_back(config);
    }

    // horizontal lines; skip first and last
    for (size_t y = 1; y < m_size_y; y++)
    {
        sf::VertexArray line;
        ClickableGridElementLineConfig config;

        sf::Vector2f startPoint = sf::Vector2f{
            m_position.x,
            m_position.y + y * m_cell_size.y //
        };
        sf::Vector2f endPoint = sf::Vector2f{
            m_position.x + m_size_x * m_cell_size.x,
            m_position.y + y * m_cell_size.y //
        };
        sf::Vector2f direction = endPoint - startPoint;

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length == 0.f)
            return;

        sf::Vector2f normal = {-direction.y / length, direction.x / length};
        sf::Vector2f offset = normal * (config.thickness * 0.5f);

        line.setPrimitiveType(sf::PrimitiveType::Triangles);
        line.resize(6); // 6 vertices

        // first triangle vertices
        line[0].position = startPoint + offset; // top right vertex
        line[1].position = startPoint - offset; // top left vertex
        line[2].position = endPoint - offset;   // bottom left vertex

        // second triangle vertices
        line[3].position = startPoint + offset; // top right vertex
        line[4].position = endPoint - offset;   // bottom left vertex
        line[5].position = endPoint + offset;   // bottom right vertexs

        // settings color for all vertices
        line[0].color = config.color;
        line[1].color = config.color;
        line[2].color = config.color;
        line[3].color = config.color;
        line[4].color = config.color;
        line[5].color = config.color;

        m_lines.push_back(line);
        m_lines_config.push_back(config);
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

            m_cells_background[index] = background;
            m_cells_config[index] = config;

            // text
            sf::Text cellText(m_font);
            cellText.setCharacterSize(config.fontSize);
            cellText.setFillColor(config.fontColor);
            cellText.setStyle(config.fontStyle);
            m_cells_text[index] = cellText;
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
            if (m_cells_text[i].has_value())
            {
                m_cells_text[i].value().setFillColor(m_cells_config[i].fontColor);
                m_cells_text[i].value().setStyle(m_cells_config[i].fontStyle);
            }

            m_cells_background[i].setFillColor(m_cells_config[i].fillCellColor);
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
    ClickableGridElementCellConfig &cellConfig = m_cells_config[index];

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

                // style
                m_cells_text[index].value().setFillColor(cellConfig.fontColor);
                m_cells_text[index].value().setStyle(cellConfig.fontClickStyle);

                m_cells_background[index].setFillColor(cellConfig.clickCellFillColor);
            }

            m_pressedThisFrame = true;
        }
    }
    else
    {
        m_pressedThisFrame = false;

        // hover style
        if (m_cells_text[index].has_value())
        {
            m_cells_text[index].value().setFillColor(cellConfig.fontColor);
            m_cells_text[index].value().setStyle(cellConfig.fontHoverStyle);
        }

        m_cells_background[index].setFillColor(cellConfig.hoverCellFillColor);

        // reset other cells to normal style
        const size_t totalCells = m_size_x * m_size_y;
        for (size_t i = 0; i < totalCells; i++)
        {
            // ignore this cell
            if (i == index)
                continue;

            if (m_cells_text[i].has_value())
            {
                m_cells_text[i].value().setFillColor(m_cells_config[i].fontColor);
                m_cells_text[i].value().setStyle(m_cells_config[i].fontStyle);
            }

            m_cells_background[i].setFillColor(m_cells_config[i].fillCellColor);
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

void engine::gui::elements::ClickableGridElement::SetCellConfig(size_t x, size_t y, const ClickableGridElementCellConfig &config)
{
    checkOutOfBounds(x, y);

    size_t index = getUnwrappedIndex(x, y);

    m_cells_config[index] = config;

    // background
    sf::RectangleShape &background = m_cells_background[index];
    background.setFillColor(config.fillCellColor);
    background.setOutlineThickness(0);

    // text
    if (m_cells_text[index].has_value())
    {
        sf::Text &cellText = m_cells_text[index].value();
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

    m_lines_config[index] = config;

    // line color
    sf::VertexArray &line = m_lines[index];
    line[0].color = config.color;
    line[1].color = config.color;
}

void ClickableGridElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (IsHidden())
        return;

    const size_t totalCells = m_size_x * m_size_y;

    // draw backgrounds
    for (size_t i = 0; i < totalCells; i++)
    {
        target.draw(m_cells_background[i], states);
    }

    // draw lines
    for (const auto &line : m_lines)
    {
        target.draw(line, states);
    }

    // draw texts
    for (size_t i = 0; i < totalCells; i++)
    {
        if (m_cells_text[i].has_value())
            target.draw(m_cells_text[i].value(), states);
    }
}
