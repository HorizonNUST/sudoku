#pragma once

#include "GameScreen.hpp"
#include "UILayout.hpp"

#include "utils.hpp"

class MainLayoutGroup
{
private:
    engine::GameScreen &m_screen;

    engine::UILayout *m_main_menu_layout = nullptr;
    engine::UILayout *m_how_to_play_layout = nullptr;
    engine::UILayout *m_high_scores_layout = nullptr;
    engine::UILayout *m_credits_layout = nullptr;

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

    bool inLayout(const engine::UILayout &layout) const;

    uint16_t m_credits_sample_text_id{};

    void createSudokuBoard(engine::UILayout *layout, const sf::Vector2f &startPos, float cellSize, int board[9][9]);

public:
    MainLayoutGroup() = delete;
    MainLayoutGroup(engine::GameScreen &screen);
    ~MainLayoutGroup();

    void Update(const engine::GameScreenData &data);
};
