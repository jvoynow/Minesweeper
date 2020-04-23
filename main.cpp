#include "Game.h"
#include "Unselected_tile.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {

    Game game(4,4,10);
    game.initialize();

    Unselected_tile unselected;

    return 0;
}