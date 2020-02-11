// ConsoleUI is a testing environment for the engine
//

#include <iostream>
#include "game.h"


int main(int argc, const char** argv)
{
    model::game game(2);
    std::vector<int> indices = game.get_score_indices(0, 0, model::tile::blue);
    return 0;
}

