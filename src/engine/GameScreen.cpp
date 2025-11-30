#include "GameScreen.hpp"

#include "GameScreenData.hpp"
#include "utils.hpp"

// since soundBuffer is static
sf::SoundBuffer engine::GameScreen::soundBuffer;

engine::GameScreen::GameScreen(const sf::Vector2u& windowSize)
{
    m_window = sf::RenderWindow(sf::VideoMode(windowSize), "Sudoku", sf::Style::Titlebar | sf::Style::Close);
}

engine::GameScreen::~GameScreen() {}

uint16_t engine::GameScreen::GetCurrentUILayoutID() const
{
    if (m_ui_layout)
        return m_ui_layout->GetID();

    DEBUG_PRINT("No UILayout set");
    throw std::runtime_error("No UILayout set");
}

void engine::GameScreen::ChangeUILayout(UILayout &layout)
{
    if (m_ui_layout)
        if (layout == *m_ui_layout)
        {
            DEBUG_PRINT("SAME LAYOUT");
            return;
        }

    m_data.isClicking = false;
    m_ui_layout = &layout;
}

void engine::GameScreen::StartLoop()
{
    while (m_window.isOpen())
    {
        // poll all events
        while (const std::optional<sf::Event> &event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                m_window.close();
            else if (event->is<sf::Event::MouseButtonPressed>())
                m_data.isClicking = true;
            else if (event->is<sf::Event::MouseButtonReleased>())
                m_data.isClicking = false;
        }

        // get m_data after polling events
        m_data.mousePos = sf::Mouse::getPosition(m_window);

        m_window.clear(CONSTANTS::BACKGROUND_COLOR);

        for (const auto &callback : m_update_callbacks)
        {
            if (callback)
                callback(m_data);
        }

        if (m_ui_layout)
        {
            m_ui_layout->update(m_data);
            m_ui_layout->drawLayout(m_window);
        }

        m_window.display();
    }
}

void engine::GameScreen::SetBackgroundMusic(const std::string &path)
{
    static sf::Music backgroundMusic; // for long background track
    // Load the sound buffer from file
    if (!backgroundMusic.openFromFile(path))
    {
        throw std::runtime_error("Failed to load background music from file: " + path);
    }
    backgroundMusic.setLooping(true);
    backgroundMusic.setVolume(50.f);
    backgroundMusic.play();
}

void engine::GameScreen::PlayAudioOneTime(const std::string_view &path)
{
    static sf::Sound sound(soundBuffer);
    // Load the sound buffer from file
    if (!soundBuffer.loadFromFile(std::string(path)))
    {
        throw std::runtime_error("Failed to load sound buffer from file: " + std::string(path));
    }
    sound.setVolume(80.f);
    sound.play();
}
