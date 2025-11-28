#include "Screen.hpp"
#include "UILayout.hpp"
#include "MainLayoutGroup.hpp"

using namespace engine;

int main()
{
    GameScreen screen;
    MainLayoutGroup mainLayoutGroup{screen};

    screen.StartLoop();

    return 0;
}
