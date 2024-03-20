#ifndef GAME_H
#define GAME_H
#include<iostream>
#include<vector>
#include <chrono>
#include <thread>
#include "Character.h"
#include "Enemy.h"
#include "Skill.h"
#include "SDL_ttf.h"
#include "explosion.h"


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
    vector<Enemy> enemies;
    vector<Skill> skills;
    vector<Explosion> explosions;
    Uint32 startTime;
    Uint32 lastPlayTime;
    int numLives;
    TTF_Font* font;
    SDL_Texture* heartTexture;

    int menuWidth, menuHeight,submenuWidth,submenuHeight;
    GameState gameState;

    void initSDL();
    void logSDLError(std::ostream& os, const std::string &msg, bool fatal);
    void drawMenu();
    void drawGameover();
    void handleMenuInput(SDL_Event& e,bool& quit);
    void handlePlayingInput(SDL_Event& e,bool& quit);
    void handleGameoverInput(SDL_Event& e,bool& quit);
    void update();
    void render();
    void quitSDL();
    void spawnEnemy();
    void spawnItem();
    Uint32 getElapsedTime();
    void waitUntilKeyPressed();
    void initElement();
    bool isCollision(const SDL_Rect& rect1, const SDL_Rect& rect2);
    bool ismulti,player1lose;
    void singerplayer();
    Uint32 frameStart;
    Uint32 ENEMY_SPAWN_INTERVAL;
    Uint32 ITEM_SPAWN_INTERVAL;
    Uint32 lastEnemySpawnTime;
    Uint32 lastItemSpawnTime;
    bool checkPlayerEnemyCollision(const Character& player, const Enemy& enemy);
    bool checkPlayerSkillCollision(const Character& player, const Skill& skill);
    float frameTime;

};

#endif // GAME_H
