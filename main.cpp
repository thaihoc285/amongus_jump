#include "Game.h"

int main(int argc, char* args[]) {
    Game game;

    if (!game.init()) {
        return 1;
    }

    while (!game.quitRequested()) {
        game.handleEvents();
        game.update();
        game.render();
    }

    game.quit();
    return 0;
}
