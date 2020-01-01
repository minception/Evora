// ConsoleUI is a testing enviroment for the engine
//

#include <iostream>
#include "Board.h"


int main(int argc, const char** argv)
{
    engine::board board(2);
    board.start_game();
    return 0;
}

