#include <iostream>
#include "Game.h"
#include "DEFINITIONS.h"
using namespace as;

int main()
{
    std::srand(std::time(nullptr));
    Game(SCREEN_WIDTH,SCREEN_HEIGHT,"Card Hero");

   return EXIT_SUCCESS;
}
