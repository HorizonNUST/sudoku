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

    /// @brief Main Screen
    class GameScreen
    {
    private:
        sf::RenderWindow m_window;
        UILayout *m_ui_layout = nullptr;
        GameScreenData m_data;
        std::vector<std::function<void(const GameScreenData &)>> m_update_callbacks;

        static sf::SoundBuffer soundBuffer; // for short sound

    public:
        GameScreen();
        ~GameScreen();

        uint16_t GetCurrentUILayoutID() const;

        /// @brief To Change `UILayout` to given layout
        /// @param layout `UILayout&` handle memory yourself
        void ChangeUILayout(UILayout &layout);

        /// @brief To Start the Game Loop
        void StartLoop();

        /// @brief To Close the Window
        inline void CloseWindow() { m_window.close(); }

        /// @brief To set background music from a file path
        /// @param path Path to the music file
        static void SetBackgroundMusic(const std::string &path);

        /// @brief To play an audio file one time from a file path
        /// @param path Path to the audio file
        static void PlayAudioOneTime(const std::string &path);

        /// @brief To add update callback which will be called every frame
        /// @param callback Function to be called every frame with `GameScreenData`
        inline void AddUpdateCallback(std::function<void(const GameScreenData &)> callback)
        {
            m_update_callbacks.push_back(callback);
        }
    };
}