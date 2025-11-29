#include "MainLayoutGroup.hpp"

using namespace engine;

MainLayoutGroup::MainLayoutGroup(GameScreen &screen)
    : m_screen(screen)
{
    m_main_menu_layout = new UILayout(0);
    m_how_to_play_layout = new UILayout(1);
    m_high_scores_layout = new UILayout(2);
    m_credits_layout = new UILayout(3);

    createMainMenuLayout();
    createHowToPlayLayout();
    createHighScoresLayout();
    createCreditsLayout();

    goToMainMenu();
}

MainLayoutGroup::~MainLayoutGroup()
{
    delete m_main_menu_layout;
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

    constexpr sf::Vector2f boardSize = {300.f, 300.f};

    // lines
    // for (size_t i = 0; i < 8; i++)
    // {
    //     float lineOffset = (i + 1) * (boardSize.x / 9.f);
    //     engine::gui::elements::LineConfig lineConfig;
    //     // thicker line for 3x3 boxes
    //     if ((i + 1) % 3 == 0)
    //     {
    //         lineConfig.thickness = 4.f;
    //     }

    //     // vertical lines
    //     m_how_to_play_layout->AddLineElement({startPos.x + lineOffset, startPos.y}, {startPos.x + lineOffset, startPos.y + boardSize.y}, lineConfig);
    //     // horizontal lines
    //     m_how_to_play_layout->AddLineElement({startPos.x, startPos.y + lineOffset}, {startPos.x + boardSize.x, startPos.y + lineOffset}, lineConfig);
    // }

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

    // createSudokuBoard(m_how_to_play_layout, {startPos.x, startPos.y}, boardSize.x / 9.f, sampleBoard);
    uint16_t gridID = m_how_to_play_layout->AddClickableGridElement({startPos.x, startPos.y}, {boardSize.x / 9.f, boardSize.y / 9.f});
    auto *gridElement = dynamic_cast<engine::gui::elements::ClickableGridElement *>(m_how_to_play_layout->GetElementById(gridID));

    gridElement->SetCallback([](int x, int y, std::string &cellText) { //
        DEBUG_PRINT("Clicked cell (" + std::to_string(x) + ", " + std::to_string(y) + ")");

        // for demo, just set the cell text to "1" when clicked if empty
        if (cellText.empty())
        {
            cellText = "1";
        }
        else
        {
            cellText.clear();
        }
    });

    for (size_t row = 0; row < 9; row++)
    {
        for (size_t col = 0; col < 9; col++)
        {
            if (sampleBoard[row][col] != 0)
            {
                gridElement->SetCellText(static_cast<int>(col), static_cast<int>(row), std::to_string(sampleBoard[row][col]));
            }
        }
    }

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

void MainLayoutGroup::createSudokuBoard(UILayout *layout, const sf::Vector2f &startPos, float cellSize, int board[9][9])
{

    //     // lines
    //     for (size_t i = 0; i < 8; i++)
    //     {
    //         float lineOffset = (i + 1) * cellSize;
    //         engine::gui::elements::LineConfig lineConfig;
    //         // thicker line for 3x3 boxes
    //         if ((i + 1) % 3 == 0)
    //         {
    //             lineConfig.thickness = 4.f;
    //         }

    //         // vertical lines
    //         layout->AddLineElement({startPos.x + lineOffset, startPos.y}, {startPos.x + lineOffset, startPos.y + 9 * cellSize}, lineConfig);
    //         // horizontal lines
    //         layout->AddLineElement({startPos.x, startPos.y + lineOffset}, {startPos.x + 9 * cellSize, startPos.y + lineOffset}, lineConfig);
    //     }

    //     // numbers
    //     for (size_t row = 0; row < 9; row++)
    //     {
    //         for (size_t col = 0; col < 9; col++)
    //         {
    //             if (board[row][col] != 0)
    //             {
    //                 layout->AddTextElement(std::to_string(board[row][col]),
    //                                        {startPos.x + col * cellSize + cellSize / 3.f, startPos.y + row * cellSize + cellSize / 6.f},
    //                                        {
    //                                            .fontSize = static_cast<unsigned int>(cellSize * 0.6f),
    //                                        });
    //             }
    //         }
    //     }
}
