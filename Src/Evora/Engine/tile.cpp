#include <string>
#include "tile.h"

std::string model::tile_to_string(tile t) {
    const char *names[] = {
        "blue", "yellow", "red", "black", "white", "empty", "starter"
    };

    return names[(int) t];
}
