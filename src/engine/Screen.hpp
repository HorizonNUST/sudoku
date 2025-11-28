#pragma once
#include <functional>
#include <vector>
#include <unordered_map>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "UILayout.hpp"
#include "utils.hpp"

namespace engine
{
    class UILayout;

    struct GameState
    {
        bool gameRunning = true;
        size_t inspectionsCount = 0;
    };

    /// @brief Main Screen
    class GameScreen
    {
    private:
        sf::RenderWindow m_window;
        UILayout *m_ui_layout = nullptr;
        GameScreenData m_data;
        GameState m_game_state;

        // music/sound
        static sf::SoundBuffer soundBuffer; // for short sound

    public:
        GameScreen();
        ~GameScreen();

        /// @brief To Change `UILayout` to given layout
        /// @param layout `UILayout&` handle memory yourself
        void ChangeUILayout(UILayout &layout);

        /// @brief To Start the Game Loop
        void StartLoop();

        inline void CloseWindow() { m_window.close(); }

        static void setBackgroundMusic(const std::string &path);
        static void playAudioOneTime(std::string path);
    };
}