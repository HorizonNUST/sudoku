#pragma once

#include "GameScreen.hpp"
#include "UILayout.hpp"

using namespace engine;

class MainLayoutGroup
{
private:
    GameScreen &m_screen;

    UILayout *m_main_menu_layout = nullptr;
    UILayout *m_how_to_play_layout = nullptr;
    UILayout *m_high_scores_layout = nullptr;
    UILayout *m_credits_layout = nullptr;

    void createMainMenuLayout();
    void createHowToPlayLayout();
    void createHighScoresLayout();
    void createCreditsLayout();

    void goToMainMenu();
    void goToHowToPlay();
    void goToHighScores();
    void goToCredits();

    bool m_was_key_pressed_last_frame[static_cast<size_t>(sf::Keyboard::KeyCount)] = {false};
    bool isKeyJustPressed(sf::Keyboard::Key key);

    bool inLayout(const UILayout &layout) const;

    uint16_t m_credits_sample_text_id{};

public:
    MainLayoutGroup() = delete;
    MainLayoutGroup(GameScreen &screen);
    ~MainLayoutGroup();

    void Update(const GameScreenData &data);
};
