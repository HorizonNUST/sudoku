#include "GameScreen.hpp"
#include "UILayout.hpp"
#include "MainLayoutGroup.hpp"

using namespace engine;

int main()
{
    GameScreen screen({800u, 600u});
    MainLayoutGroup mainLayoutGroup{screen};
    screen.AddUpdateCallback([&mainLayoutGroup](const GameScreenData &data) {
        mainLayoutGroup.Update(data);
    });

    screen.StartLoop();

    return 0;
}
