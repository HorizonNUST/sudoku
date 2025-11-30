#include "MainLayoutGroup.hpp"

using namespace engine;
using namespace engine::gui::elements;

MainLayoutGroup::MainLayoutGroup(GameScreen &screen)
    : m_screen(screen)
{
    m_main_menu_layout = new UILayout(0);
    m_start_game_layout = new UILayout(1);
    m_game_layout = new UILayout(2);
    m_how_to_play_layout = new UILayout(3);
    m_high_scores_layout = new UILayout(4);
    m_credits_layout = new UILayout(5);

    createMainMenuLayout();
    createStartGameLayout();
    createGameLayout();
    createHowToPlayLayout();
    createHighScoresLayout();
    createCreditsLayout();

    goToMainMenu();

    updateStartGameLayoutButtonsState();
}

MainLayoutGroup::~MainLayoutGroup()
{
    delete m_main_menu_layout;
    delete m_start_game_layout;
    delete m_game_layout;
    delete m_how_to_play_layout;
    delete m_high_scores_layout;
    delete m_credits_layout;

    delete m_sudoku;
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

    m_main_menu_layout->AddButtonElement("Exit Game", {startPos.x, startPos.y + 7 * offsetY}, [this]() { //
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

    // start button
    m_start_game_layout->AddButtonElement("Start Game", {startPos.x, startPos.y + 0 * offsetY}, [this]() { //
        m_screen.PlayAudioOneTime("assets/Sound/button.wav");
        goToGame();
    });

    // easy button
    m_start_game_easy_button_id = m_start_game_layout->AddButtonElement("Easy", {startPos.x, startPos.y + 1 * offsetY}, [this]() { //
        m_screen.PlayAudioOneTime("assets/Sound/button.wav");
        m_game_config.difficulty = Difficulty::Easy;
        updateStartGameLayoutButtonsState();
    });
    // medium button
    m_start_game_medium_button_id = m_start_game_layout->AddButtonElement("Medium", {startPos.x, startPos.y + 2 * offsetY}, [this]() { //
        m_screen.PlayAudioOneTime("assets/Sound/button.wav");
        m_game_config.difficulty = Difficulty::Medium;
        updateStartGameLayoutButtonsState();
    });
    // hard button
    m_start_game_hard_button_id = m_start_game_layout->AddButtonElement("Hard", {startPos.x, startPos.y + 3 * offsetY}, [this]() { //
        m_screen.PlayAudioOneTime("assets/Sound/button.wav");
        m_game_config.difficulty = Difficulty::Hard;
        updateStartGameLayoutButtonsState();
    });

    // back button
    m_start_game_layout->AddButtonElement("Back to Main Menu", {startPos.x, startPos.y + 7 * offsetY}, [this]() { //
        m_screen.PlayAudioOneTime("assets/Sound/button.wav");
        goToMainMenu();
    });
}

void MainLayoutGroup::createGameLayout()
{
    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    // title
    // clang-format off
    m_game_layout->AddTextElement("How To Play", {50.f, 50.f}, {
        .fontSize = 48, //
    });
    // clang-format on

    // board
    constexpr float CELL_SIZE = 35.f;
    constexpr sf::Vector2f BOARD_SIZE = {
        CELL_SIZE * 9.f,
        CELL_SIZE * 9.f //
    };

    // delete existing sudoku if any
    if (m_sudoku)
        delete m_sudoku;

    m_sudoku = new Sudoku;
    m_sudoku->makePuzzle(m_game_config.difficulty);

    int board[9][9];
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            board[i][j] = m_sudoku->getCell(i, j);
        }
    }

    m_sudoku_grid_element_id = createSudokuBoard(m_game_layout, startPos, BOARD_SIZE, board);

    // show solution button
    m_show_solution_button_id = m_game_layout->AddButtonElement("Show Solution", {startPos.x, startPos.y + 5 * offsetY}, [this, BOARD_SIZE, startPos]() { //
        m_screen.PlayAudioOneTime("assets/Sound/button.wav");
        m_sudoku->autoSolve();

        int board[9][9];
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                board[i][j] = m_sudoku->getCell(i, j);
            }
        }

        // update board
        m_game_layout->RemoveElementById(m_sudoku_grid_element_id);
        m_sudoku_grid_element_id = createSudokuBoard(m_game_layout, startPos, BOARD_SIZE, board);

        // refreshing
        m_last_clicked_cell_x = std::nullopt;
        m_last_clicked_cell_y = std::nullopt;

        // set state
        setGameStatus(State::Lost);
    });

    // game status text
    TextConfig statusTextConfig = {
        .fontSize = 24,
        .fontStyle = sf::Text::Style::Bold,
    };
    m_game_status_text_id = m_game_layout->AddTextElement("Playing", {startPos.x, startPos.y + 6 * offsetY}, statusTextConfig);
    m_game_layout->GetTextElementById(m_game_status_text_id)->SetHidden(true);

    // back button
    m_game_layout->AddButtonElement("Go to Game Menu", {startPos.x, startPos.y + 7 * offsetY}, [this]() { //
        m_screen.PlayAudioOneTime("assets/Sound/button.wav");
        goToStartGame();
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
    m_how_to_play_layout->AddButtonElement("Back to Main Menu", {startPos.x, startPos.y + 7 * offsetY}, [this]() { //
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

    m_high_scores_layout->AddButtonElement("Back to Main Menu", {startPos.x, startPos.y + 7 * offsetY}, [this]() { //
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

    m_credits_layout->AddButtonElement("Back to Main Menu", {startPos.x, startPos.y + 7 * offsetY}, [this]() { //
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

void MainLayoutGroup::goToGame()
{
    if (!m_game_layout)
        return;

    // reset
    m_game_layout->ClearLayout();
    m_last_clicked_cell_x = std::nullopt;
    m_last_clicked_cell_y = std::nullopt;

    // recreate game layout
    createGameLayout();
    m_screen.ChangeUILayout(*m_game_layout);
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

void MainLayoutGroup::updateStartGameLayoutButtonsState()
{
    // highlight selected difficulty
    auto *easyButton = m_start_game_layout->GetButtonElementById(m_start_game_easy_button_id);
    auto *mediumButton = m_start_game_layout->GetButtonElementById(m_start_game_medium_button_id);
    auto *hardButton = m_start_game_layout->GetButtonElementById(m_start_game_hard_button_id);

    easyButton->SetConfig(m_game_config.difficulty == Difficulty::Easy ? SudokuBoardStyles::selectedToggleButtonConfig : SudokuBoardStyles::defaultToggleButtonConfig);
    mediumButton->SetConfig(m_game_config.difficulty == Difficulty::Medium ? SudokuBoardStyles::selectedToggleButtonConfig : SudokuBoardStyles::defaultToggleButtonConfig);
    hardButton->SetConfig(m_game_config.difficulty == Difficulty::Hard ? SudokuBoardStyles::selectedToggleButtonConfig : SudokuBoardStyles::defaultToggleButtonConfig);
}

void MainLayoutGroup::setGameStatus(const State &state)
{
    m_game_state = state;

    // disabled show solution button
    auto *showSolutionButton = m_game_layout->GetButtonElementById(m_show_solution_button_id);
    showSolutionButton->SetDisabled(m_game_state != State::Playing);

    // show status text
    auto *statusTextElement = m_game_layout->GetTextElementById(m_game_status_text_id);
    switch (m_game_state)
    {
    case State::Playing:
        statusTextElement->SetText("Playing");
        statusTextElement->SetHidden(true);
        break;
    case State::Won:
        statusTextElement->SetText("You Won!");
        statusTextElement->SetHidden(false);
        break;
    case State::Lost:
        statusTextElement->SetText("You Lost!");
        statusTextElement->SetHidden(false);
        break;
    }
}

uint16_t MainLayoutGroup::createSudokuBoard(engine::UILayout *layout, const sf::Vector2f &position, const sf::Vector2f &size, int board[9][9])
{
    uint16_t gridID = layout->AddClickableGridElement(position, sf::Vector2f{size.x / 9.f, size.y / 9.f}, 9, 9);
    auto *gridElement = layout->GetClickableGridElementById(gridID);

    DEBUG_PRINT("Created Sudoku Board: " + std::to_string(gridElement->GetSizeX()) + "x" + std::to_string(gridElement->GetSizeY()));

    // init board
    for (size_t row = 0; row < gridElement->GetSizeY(); row++)
    {
        for (size_t col = 0; col < gridElement->GetSizeX(); col++)
        {
            if (board[row][col] != 0)
            {
                gridElement->SetCellText(col, row, std::to_string(board[row][col]));
                gridElement->SetCellDisabled(col, row, true);
                gridElement->SetCellConfig(col, row, SudokuBoardStyles::prefilledCell);
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
        sudokuGridCellClick(x, y, gridElement);
    });

    // update callback to input
    gridElement->AddUpdateCallback([this, gridElement](const GameScreenData &data) { //
        sudokuGridCellUpdate(gridElement);
    });

    return gridID;
}

void MainLayoutGroup::sudokuGridCellClick(size_t x, size_t y, engine::gui::elements::ClickableGridElement *gridElement)
{
    // store last clicked cell
    m_last_clicked_cell_x = x;
    m_last_clicked_cell_y = y;

    highlightSudokuCells(gridElement, x, y);

    // validate
    std::string cellText = gridElement->GetCellText(x, y);
    if (cellText.empty())
        return;

    int cellValue = std::stoi(cellText);

    // check valid using Sudoku class
    bool invalid = false;
    if (!m_sudoku->validMove(static_cast<int>(y), static_cast<int>(x), cellValue))
    {
        invalid = true;
    }

    // check if solved
    bool solved = m_sudoku->win();
    DEBUG_PRINT("Sudoku win: " + std::to_string(solved));
    if (solved)
    {
        DEBUG_PRINT("Sudoku Solved!");
        setGameStatus(State::Won);
    }
}

void MainLayoutGroup::sudokuGridCellUpdate(engine::gui::elements::ClickableGridElement *element)
{
    // if won or lose leave
    if (m_game_state != State::Playing)
        return;

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
            if (!element->IsCellDisabled(*m_last_clicked_cell_x, *m_last_clicked_cell_y))
            {
                element->SetCellText(*m_last_clicked_cell_x, *m_last_clicked_cell_y, std::to_string(num));
                m_sudoku->setCell(static_cast<int>(*m_last_clicked_cell_y), static_cast<int>(*m_last_clicked_cell_x), num);

                bool solved = m_sudoku->win();
                DEBUG_PRINT("Sudoku win: " + std::to_string(solved));
                if (solved)
                {
                    DEBUG_PRINT("Sudoku Solved!");
                    setGameStatus(State::Won);
                }
            }
        }
    }

    // clear previous invalid highlights
    for (size_t row = 0; row < element->GetSizeY(); row++)
    {
        for (size_t col = 0; col < element->GetSizeX(); col++)
        {
            element->SetCellConfig(col, row, SudokuBoardStyles::defaultCell);
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

            // check valid using Sudoku class
            bool invalid = false;
            if (!m_sudoku->validMove(static_cast<int>(row), static_cast<int>(col), cellValue))
            {
                invalid = true;
            }

            // set config
            if (invalid)
            {
                element->SetCellConfig(col, row, SudokuBoardStyles::invalidCell);
            }
        }
    }
}

void MainLayoutGroup::highlightSudokuCells(engine::gui::elements::ClickableGridElement *element, size_t x, size_t y)
{
    // clear all highlights
    for (size_t row = 0; row < element->GetSizeY(); row++)
    {
        for (size_t col = 0; col < element->GetSizeX(); col++)
        {
            element->SetCellConfig(col, row, SudokuBoardStyles::defaultCell);
            // for disabled cells, keep font color yellow
            if (element->IsCellDisabled(col, row))
                element->SetCellConfig(col, row, SudokuBoardStyles::prefilledCell);
        }
    }

    // highlight row
    for (size_t col = 0; col < element->GetSizeX(); col++)
    {
        if (col == static_cast<size_t>(x))
            continue;

        element->SetCellConfig(col, y, SudokuBoardStyles::highlightedCell);
    }

    // highlight column
    for (size_t row = 0; row < element->GetSizeY(); row++)
    {
        if (row == static_cast<size_t>(y))
            continue;

        element->SetCellConfig(x, row, SudokuBoardStyles::highlightedCell);
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

            element->SetCellConfig(col, row, SudokuBoardStyles::highlightedCell);
        }
    }
}
