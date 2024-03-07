#ifndef GAME_H
#define GAME_H
#include<iostream>
#include "Character.h"
#include "Enemy.h"
#include "SDL_ttf.h"
using namespace std;
enum GameState {
        MENU,
        PLAYING,
        GAMEOVER
        // Add more states if needed
    };

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    Character player;
    Character player2;
    Enemy enemy1;
    Enemy enemy2;
    Enemy enemy3;
    Enemy enemy4;

    Uint32 startTime;
    Uint32 lastPlayTime;
    int numLives;
    TTF_Font* font;
    SDL_Texture* heartTexture;

    int menuWidth, menuHeight;
    GameState gameState;

    void initSDL();
    void logSDLError(std::ostream& os, const std::string &msg, bool fatal);
    void drawMenu();
    void drawGameover();
    void handleMenuInput(SDL_Event& e);
    void handlePlayingInput(SDL_Event& e);
    void handleGameoverInput(SDL_Event& e);
    void update();
    void render();
    void quitSDL();
    Uint32 getElapsedTime();
    void waitUntilKeyPressed();
    void initElement();
    bool isCollision(const SDL_Rect& rect1, const SDL_Rect& rect2);
    bool ismulti;
    void singerplayer();
};

#endif // GAME_H
