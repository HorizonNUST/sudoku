#include "MainLayoutGroup.hpp"

MainLayoutGroup::MainLayoutGroup(GameScreen &screen)
    : m_screen(screen)
{
    m_mainMenuLayout = new UILayout(0);
    m_howToPlayLayout = new UILayout(1);
    m_highScoresLayout = new UILayout(2);
    m_creditsLayout = new UILayout(3);

    m_createMainMenuLayout();
    m_createHowToPlayLayout();
    m_createHighScoresLayout();
    m_createCreditsLayout();

    m_goToMainMenu();
}

MainLayoutGroup::~MainLayoutGroup()
{
    delete m_mainMenuLayout;
    delete m_howToPlayLayout;
    delete m_highScoresLayout;
    delete m_creditsLayout;
}

void MainLayoutGroup::m_createMainMenuLayout()
{
    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    // title
    // clang-format off
    m_mainMenuLayout->AddTextElement("Sudoku", {50.f, 50.f}, {
        .fontColor = sf::Color::White, //
        .fontSize = 48, //
        .fontStyle = sf::Text::Style::Bold, //
        .lineHeight = 1.f //
    });
    // clang-format on

    m_mainMenuLayout->AddButtonElement("Start Game", {startPos.x, startPos.y}, [this]() { //
        m_screen.playAudioOneTime("assets/Sound/button.wav");
    });

    m_mainMenuLayout->AddButtonElement("How To Play", {startPos.x, startPos.y + offsetY}, [this]() { //
        m_screen.playAudioOneTime("assets/Sound/button.wav");
        m_goToHowToPlay();
    });

    m_mainMenuLayout->AddButtonElement("High Scores", {startPos.x, startPos.y + 2 * offsetY}, [this]() { //
        m_screen.playAudioOneTime("assets/Sound/button.wav");
        m_goToHighScores();
    });

    m_mainMenuLayout->AddButtonElement("Credits", {startPos.x, startPos.y + 3 * offsetY}, [this]() { //
        m_screen.playAudioOneTime("assets/Sound/button.wav");
        m_goToCredits();
    });

    m_mainMenuLayout->AddButtonElement("Exit Game", {startPos.x, startPos.y + 4 * offsetY}, [this]() { //
        m_screen.playAudioOneTime("assets/Sound/button.wav");
        m_screen.CloseWindow();
    });
}

void MainLayoutGroup::m_createHowToPlayLayout()
{
    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    // title
    // clang-format off
    m_howToPlayLayout->AddTextElement("How To Play", {50.f, 50.f}, {
        .fontSize = 48, //
    });
    // clang-format on

    m_howToPlayLayout->AddButtonElement("Back to Main Menu", {startPos.x, startPos.y + 4 * offsetY}, [this]() { //
        m_screen.playAudioOneTime("assets/Sound/button.wav");
        m_goToMainMenu();
    });
}

void MainLayoutGroup::m_createHighScoresLayout()
{
    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    // title
    // clang-format off
    m_highScoresLayout->AddTextElement("High Scores", {50.f, 50.f}, {
        .fontSize = 48, //
    });
    // clang-format on

    m_highScoresLayout->AddButtonElement("Back to Main Menu", {startPos.x, startPos.y + 4 * offsetY}, [this]() { //
        m_screen.playAudioOneTime("assets/Sound/button.wav");
        m_goToMainMenu();
    });
}

void MainLayoutGroup::m_createCreditsLayout()
{
    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    // title
    // clang-format off
    m_creditsLayout->AddTextElement("Credits", {50.f, 50.f}, {
        .fontSize = 48, //
    });
    // clang-format on

    // show hide button
    m_creditsLayout->AddButtonElement("Show/Hide Text", {startPos.x, startPos.y + offsetY}, [this]() { //
        m_screen.playAudioOneTime("assets/Sound/button.wav");

        auto *element = m_creditsLayout->GetElementById(m_creditsSampleTextID);
        element->SetHidden(!element->IsHidden());
    });

    // show hide text
    m_creditsSampleTextID = m_creditsLayout->AddTextElement("Sample Show Hide Text!", {startPos.x, startPos.y + 2 * offsetY});
    m_creditsLayout->GetElementById(m_creditsSampleTextID)->SetHidden(true);

    m_creditsLayout->AddButtonElement("Back to Main Menu", {startPos.x, startPos.y + 4 * offsetY}, [this]() { //
        m_screen.playAudioOneTime("assets/Sound/button.wav");
        m_goToMainMenu();
    });
}

void MainLayoutGroup::m_goToMainMenu()
{
    m_screen.ChangeUILayout(*m_mainMenuLayout);
}

void MainLayoutGroup::m_goToHowToPlay()
{
    m_screen.ChangeUILayout(*m_howToPlayLayout);
}

void MainLayoutGroup::m_goToHighScores()
{
    m_screen.ChangeUILayout(*m_highScoresLayout);
}

void MainLayoutGroup::m_goToCredits()
{
    m_screen.ChangeUILayout(*m_creditsLayout);
}
