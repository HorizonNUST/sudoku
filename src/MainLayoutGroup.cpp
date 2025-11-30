#include "MainLayoutGroup.hpp"

using namespace engine;
using namespace engine::gui::elements;

MainLayoutGroup::MainLayoutGroup(GameScreen &screen)
    : m_screen(screen)
{
    m_main_menu_layout = new UILayout(0);
    m_start_game_layout = new UILayout(1);
    m_how_to_play_layout = new UILayout(2);
    m_high_scores_layout = new UILayout(3);
    m_credits_layout = new UILayout(4);

    createMainMenuLayout();
    createStartGameLayout();
    createHowToPlayLayout();
    createHighScoresLayout();
    createCreditsLayout();

    goToMainMenu();
}

MainLayoutGroup::~MainLayoutGroup()
{
    delete m_main_menu_layout;
    delete m_start_game_layout;
    delete m_how_to_play_layout;
    delete m_high_scores_layout;
    delete m_credits_layout;
}

void MainLayoutGroup::Update(const GameScreenData &data)
{
    if (isKeyJustPressed(sf::Keyboard::Key::Escape))
    {
        DEBUG_PRINT("Escape Pressed -> Main Menu");
        goToMainMenu();
    }

    if (isKeyJustPressed(sf::Keyboard::Key::H) && inLayout(*m_credits_layout))
    {
        DEBUG_PRINT("Toggle Credits Text");

        // show hide button in credits layout
        auto *element = m_credits_layout->GetElementById(m_credits_sample_text_id);
        element->SetHidden(!element->IsHidden());
    }
}

void MainLayoutGroup::createMainMenuLayout()
{
    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    // title
    // clang-format off
    m_main_menu_layout->AddTextElement("Sudoku", {50.f, 50.f}, {
        .fontColor = sf::Color::White, //
        .fontSize = 48, //
        .fontStyle = sf::Text::Style::Bold, //
        .lineHeight = 1.f //
    });
    // clang-format on

    m_main_menu_layout->AddButtonElement("Start Game", {startPos.x, startPos.y}, [this]() { //
        m_screen.PlayAudioOneTime("assets/Sound/button.wav");
        goToStartGame();
    });

    m_main_menu_layout->AddButtonElement("How To Play", {startPos.x, startPos.y + offsetY}, [this]() { //
        m_screen.PlayAudioOneTime("assets/Sound/button.wav");
        goToHowToPlay();
    });

    m_main_menu_layout->AddButtonElement("High Scores", {startPos.x, startPos.y + 2 * offsetY}, [this]() { //
        m_screen.PlayAudioOneTime("assets/Sound/button.wav");
        goToHighScores();
    });

    m_main_menu_layout->AddButtonElement("Credits", {startPos.x, startPos.y + 3 * offsetY}, [this]() { //
        m_screen.PlayAudioOneTime("assets/Sound/button.wav");
        goToCredits();
    });

    m_main_menu_layout->AddButtonElement("Exit Game", {startPos.x, startPos.y + 4 * offsetY}, [this]() { //
        m_screen.PlayAudioOneTime("assets/Sound/button.wav");
        m_screen.CloseWindow();
    });
}

void MainLayoutGroup::createStartGameLayout()
{
    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    // title
    // clang-format off
    m_start_game_layout->AddTextElement("Start Game", {50.f, 50.f}, {
        .fontSize = 48, //
    });
    // clang-format on

    constexpr sf::Vector2f boardSize = {300.f, 300.f};

    int sampleBoard[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    createSudokuBoard(m_start_game_layout, {startPos.x, startPos.y}, boardSize, sampleBoard);

    // back button
    m_start_game_layout->AddButtonElement("Back to Main Menu", {startPos.x, startPos.y + 4 * offsetY}, [this]() { //
        m_screen.PlayAudioOneTime("assets/Sound/button.wav");
        goToMainMenu();
    });
}

void MainLayoutGroup::createHowToPlayLayout()
{
    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    // title
    // clang-format off
    m_how_to_play_layout->AddTextElement("How To Play", {50.f, 50.f}, {
        .fontSize = 48, //
    });
    // clang-format on

    // back button
    m_how_to_play_layout->AddButtonElement("Back to Main Menu", {startPos.x, startPos.y + 4 * offsetY}, [this]() { //
        m_screen.PlayAudioOneTime("assets/Sound/button.wav");
        goToMainMenu();
    });
}

void MainLayoutGroup::createHighScoresLayout()
{
    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    // title
    // clang-format off
    m_high_scores_layout->AddTextElement("High Scores", {50.f, 50.f}, {
        .fontSize = 48, //
    });
    // clang-format on

    m_high_scores_layout->AddButtonElement("Back to Main Menu", {startPos.x, startPos.y + 4 * offsetY}, [this]() { //
        m_screen.PlayAudioOneTime("assets/Sound/button.wav");
        goToMainMenu();
    });
}

void MainLayoutGroup::createCreditsLayout()
{
    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    // title
    // clang-format off
    m_credits_layout->AddTextElement("Credits", {50.f, 50.f}, {
        .fontSize = 48, //
    });
    // clang-format on

    // show hide button
    m_credits_layout->AddButtonElement("Show/Hide Text", {startPos.x, startPos.y + offsetY}, [this]() { //
        m_screen.PlayAudioOneTime("assets/Sound/button.wav");

        auto *element = m_credits_layout->GetElementById(m_credits_sample_text_id);
        element->SetHidden(!element->IsHidden());
    });

    // show hide text
    m_credits_sample_text_id = m_credits_layout->AddTextElement("Sample Show Hide Text!", {startPos.x, startPos.y + 2 * offsetY});
    m_credits_layout->GetElementById(m_credits_sample_text_id)->SetHidden(true);

    m_credits_layout->AddButtonElement("Back to Main Menu", {startPos.x, startPos.y + 4 * offsetY}, [this]() { //
        m_screen.PlayAudioOneTime("assets/Sound/button.wav");
        goToMainMenu();
    });
}

void MainLayoutGroup::goToMainMenu()
{
    m_screen.ChangeUILayout(*m_main_menu_layout);
}

void MainLayoutGroup::goToStartGame()
{
    m_screen.ChangeUILayout(*m_start_game_layout);
}

void MainLayoutGroup::goToHowToPlay()
{
    m_screen.ChangeUILayout(*m_how_to_play_layout);
}

void MainLayoutGroup::goToHighScores()
{
    m_screen.ChangeUILayout(*m_high_scores_layout);
}

void MainLayoutGroup::goToCredits()
{
    m_screen.ChangeUILayout(*m_credits_layout);
}

bool MainLayoutGroup::isKeyJustPressed(sf::Keyboard::Key key)
{
    bool isPressedNow = sf::Keyboard::isKeyPressed(key);
    bool wasPressedLastFrame = m_was_key_pressed_last_frame[static_cast<size_t>(key)];

    // update for next frame
    m_was_key_pressed_last_frame[static_cast<size_t>(key)] = isPressedNow;

    return isPressedNow && !wasPressedLastFrame;
}

bool MainLayoutGroup::inLayout(const UILayout &layout) const
{
    return m_screen.GetCurrentUILayoutID() == layout.GetID();
}

void MainLayoutGroup::createSudokuBoard(engine::UILayout *layout, const sf::Vector2f &position, const sf::Vector2f &size, int board[9][9])
{
    uint16_t gridID = layout->AddClickableGridElement(position, {size.x / 9.f, size.y / 9.f}, 9, 9);
    auto *gridElement = layout->GetClickableGridElementById(gridID);

    // init board
    for (size_t row = 0; row < gridElement->GetSizeY(); row++)
    {
        for (size_t col = 0; col < gridElement->GetSizeX(); col++)
        {
            if (board[row][col] != 0)
            {
                gridElement->SetCellText(static_cast<int>(col), static_cast<int>(row), std::to_string(board[row][col]));
            }
        }
    }

    // thicken lines; vertical
    for (size_t i = 0; i < gridElement->GetNumVerticalLines(); i++)
    {
        ClickableGridElementLineConfig lineConfig = gridElement->GetVerticalLineConfig(i);

        lineConfig.color = sf::Color::White;

        if ((i + 1) % 3 == 0)
        {
            lineConfig.color = sf::Color(200, 200, 200);
            lineConfig.thickness = 5.f;
        }

        gridElement->SetVerticalLineConfig(i, lineConfig);
    }

    // thicken lines; horizontal
    for (size_t i = 0; i < gridElement->GetNumHorizontalLines(); i++)
    {
        ClickableGridElementLineConfig lineConfig = gridElement->GetHorizontalLineConfig(i);

        lineConfig.color = sf::Color::White;

        if ((i + 1) % 3 == 0)
        {
            lineConfig.color = sf::Color(200, 200, 200);
            lineConfig.thickness = 5.f;
        }

        gridElement->SetHorizontalLineConfig(i, lineConfig);
    }

    // click callback
    gridElement->SetCellClickCallback([this, gridElement](int x, int y, std::string &cellText) { //
        m_screen.PlayAudioOneTime("assets/Sound/button.wav");

        // store last clicked cell
        m_last_clicked_cell_x = x;
        m_last_clicked_cell_y = y;

        highlightSudokuCells(gridElement, x, y);
    });

    // update callback to input
    gridElement->AddUpdateCallback([this, gridElement](const GameScreenData &data) { //
        sudokuGridCellUpdate(gridElement);
    });
}

void MainLayoutGroup::sudokuGridCellUpdate(engine::gui::elements::ClickableGridElement *element)
{
    // only proceed if a cell was clicked before
    if (!m_last_clicked_cell_x.has_value() || !m_last_clicked_cell_y.has_value())
    {
        return;
    }

    // check for number key presses
    for (int num = 1; num <= 9; num++)
    {
        // for all number keys 1-9
        sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(static_cast<size_t>(sf::Keyboard::Key::Num1) + (num - 1));
        if (isKeyJustPressed(key))
        {
            // set text of selected cell
            element->SetCellText(*m_last_clicked_cell_x, *m_last_clicked_cell_y, std::to_string(num));
        }
    }

    ClickableGridElementCellConfig invalidConfig = element->GetCellConfig(*m_last_clicked_cell_x, *m_last_clicked_cell_y);
    invalidConfig = ClickableGridElementCellConfig{
        .fontColor = sf::Color::Red,
    };

    // clear previous invalid highlights
    for (size_t row = 0; row < element->GetSizeY(); row++)
    {
        for (size_t col = 0; col < element->GetSizeX(); col++)
        {
            ClickableGridElementCellConfig defaultConfig = element->GetCellConfig(col, row);
            defaultConfig.fontColor = sf::Color::White;
            element->SetCellConfig(col, row, defaultConfig);
        }
    }

    highlightSudokuCells(element, *m_last_clicked_cell_x, *m_last_clicked_cell_y);

    // highlight invalid cells
    for (size_t row = 0; row < element->GetSizeY(); row++)
    {
        for (size_t col = 0; col < element->GetSizeX(); col++)
        {
            std::string cellText = element->GetCellText(col, row);
            if (cellText.empty())
                continue;

            int cellValue = std::stoi(cellText);

            // check row
            bool invalid = false;
            for (size_t checkCol = 0; checkCol < element->GetSizeX(); checkCol++)
            {
                if (checkCol == col)
                    continue;

                std::string checkCellText = element->GetCellText(checkCol, row);
                if (!checkCellText.empty() && std::stoi(checkCellText) == cellValue)
                {
                    invalid = true;
                    break;
                }
            }

            // check column
            if (!invalid)
            {
                for (size_t checkRow = 0; checkRow < element->GetSizeY(); checkRow++)
                {
                    if (checkRow == row)
                        continue;

                    std::string checkCellText = element->GetCellText(col, checkRow);
                    if (!checkCellText.empty() && std::stoi(checkCellText) == cellValue)
                    {
                        invalid = true;
                        break;
                    }
                }
            }

            // set config
            if (invalid)
            {
                element->SetCellConfig(col, row, invalidConfig);
            }
        }
    }
}

void MainLayoutGroup::highlightSudokuCells(engine::gui::elements::ClickableGridElement *element, size_t x, size_t y)
{
    ClickableGridElementCellConfig highlightConfig = element->GetCellConfig(x, y);
    highlightConfig = ClickableGridElementCellConfig{
        .fillCellColor = sf::Color(150, 150, 255),
        .hoverCellFillColor = sf::Color(200, 200, 255),
        .clickCellFillColor = sf::Color(255, 255, 255),
    };

    // clear all highlights
    for (size_t row = 0; row < element->GetSizeY(); row++)
    {
        for (size_t col = 0; col < element->GetSizeX(); col++)
        {
            element->SetCellConfig(col, row, ClickableGridElementCellConfig{});
        }
    }

    // highlight row
    for (size_t col = 0; col < element->GetSizeX(); col++)
    {
        if (col == static_cast<size_t>(x))
            continue;

        element->SetCellConfig(col, y, highlightConfig);
    }

    // highlight column
    for (size_t row = 0; row < element->GetSizeY(); row++)
    {
        if (row == static_cast<size_t>(y))
            continue;

        element->SetCellConfig(x, row, highlightConfig);
    }

    // highlight box
    size_t boxStartX = (x / 3) * 3;
    size_t boxStartY = (y / 3) * 3;
    for (size_t row = boxStartY; row < boxStartY + 3; row++)
    {
        for (size_t col = boxStartX; col < boxStartX + 3; col++)
        {
            if (col == static_cast<size_t>(x) || row == static_cast<size_t>(y))
                continue;

            element->SetCellConfig(col, row, highlightConfig);
        }
    }
}
