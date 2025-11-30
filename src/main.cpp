#include "GameScreen.hpp"
#include "UILayout.hpp"
#include "MainLayoutGroup.hpp"

using namespace engine;

int main()
{
    GameScreen screen({1024u, 768u});
    MainLayoutGroup mainLayoutGroup{screen};
    screen.AddUpdateCallback([&mainLayoutGroup](const GameScreenData &data) {
        mainLayoutGroup.Update(data);
    });

    screen.StartLoop();

    return 0;
}
