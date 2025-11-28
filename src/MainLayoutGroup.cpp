#include "MainLayoutGroup.hpp"

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
