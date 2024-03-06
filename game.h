#ifndef GAME_H
#define GAME_H

#include "character.h"
#include "enemy.h"

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    GameState gameState;
    Uint32 startTime;
    Uint32 lastPlayTime;
    int numLives;

    Character player;
    Character player2;
    Enemy enemy1;
    Enemy enemy2;
    Enemy enemy3;
    Enemy enemy4;

    int menuWidth, menuHeight;

    TTF_Font* font;
    SDL_Texture* heartTexture;

    void logSDLError(std::ostream& os, const std::string& msg, bool fatal);
    void initSDL();
    void drawMenu();
    void drawGameover();
    void quitSDL();
    Uint32 getElapsedTime();
    void initElement();
};

#endif // GAME_H
