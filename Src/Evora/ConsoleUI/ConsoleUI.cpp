// ConsoleUI is a testing enviroment for the engine
//

#include <iostream>
#include "Board.h"

int main()
{
    engine::board board(2);
    board.start_game();
    std::cout << "Hello World!\n";
}

