#pragma once

#include "Screen.hpp"
#include "UILayout.hpp"

using namespace engine;

class MainLayoutGroup
{
private:
    GameScreen &m_screen;

    UILayout *m_mainMenuLayout = nullptr;
    UILayout *m_howToPlayLayout = nullptr;
    UILayout *m_highScoresLayout = nullptr;
    UILayout *m_creditsLayout = nullptr;

    void m_createMainMenuLayout();
    void m_createHowToPlayLayout();
    void m_createHighScoresLayout();
    void m_createCreditsLayout();

    void m_goToMainMenu();
    void m_goToHowToPlay();
    void m_goToHighScores();
    void m_goToCredits();

    uint16_t m_creditsSampleTextID{};

public:
    MainLayoutGroup() = delete;
    MainLayoutGroup(GameScreen &screen);
    ~MainLayoutGroup();
};
