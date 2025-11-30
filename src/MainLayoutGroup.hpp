#pragma once

#include "GameScreen.hpp"
#include "UILayout.hpp"
#include "sudoku.hpp"

#include "utils.hpp"

struct GameConfig
{
    Difficulty difficulty;
};

class MainLayoutGroup
{
private:
    engine::GameScreen &m_screen;

    engine::UILayout *m_main_menu_layout = nullptr;
    engine::UILayout *m_start_game_layout = nullptr;
    engine::UILayout *m_game_layout = nullptr;
    engine::UILayout *m_how_to_play_layout = nullptr;
    engine::UILayout *m_high_scores_layout = nullptr;
    engine::UILayout *m_credits_layout = nullptr;

    void createMainMenuLayout();
    void createStartGameLayout();
    void createGameLayout();
    void createHowToPlayLayout();
    void createHighScoresLayout();
    void createCreditsLayout();

    void goToMainMenu();
    void goToStartGame();
    void goToGame();
    void goToHowToPlay();
    void goToHighScores();
    void goToCredits();

    GameConfig m_game_config{Difficulty::Easy};

    // utils
    bool m_was_key_pressed_last_frame[static_cast<size_t>(sf::Keyboard::KeyCount)] = {false};
    bool isKeyJustPressed(sf::Keyboard::Key key);

    bool inLayout(const engine::UILayout &layout) const;


    // start game
    uint16_t m_start_game_easy_button_id{};
    uint16_t m_start_game_medium_button_id{};
    uint16_t m_start_game_hard_button_id{};

    void updateStartGameLayoutButtonsState();

    // credits
    uint16_t m_credits_sample_text_id{};

    // sudoku
    Sudoku *m_sudoku = nullptr;

    void createSudokuBoard(engine::UILayout *layout, const sf::Vector2f &position, const sf::Vector2f &size, int board[9][9]);

    void sudokuGridCellUpdate(engine::gui::elements::ClickableGridElement *element);

    void highlightSudokuCells(engine::gui::elements::ClickableGridElement *element, size_t x, size_t y);

    std::optional<int> m_last_clicked_cell_x;
    std::optional<int> m_last_clicked_cell_y;

public:
    MainLayoutGroup() = delete;
    MainLayoutGroup(engine::GameScreen &screen);
    ~MainLayoutGroup();

    void Update(const engine::GameScreenData &data);
};
