#ifndef GAME_H
#define GAME_H
#include <iomanip>
#include <algorithm>
#include <thread>
#include <fstream>
#include "gameconstants.h"
#include "Character.h"
#include "Enemy.h"
#include "Skill.h"
#include "monster.h"
#include "explosion.h"
#include "invisible.h"
#include "nogravity.h"
#include "bigenemy.h"
using namespace std;
enum GameState {
        MENU,
        PLAYING,
        GAMEOVER,
        HIGHSCORE
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
    vector<BigE> biges;
    vector<Skill> skills;
    vector<Explosion> explosions;
    vector<Invisible> invisibles;
    vector<Monster> monsters;
    vector<Nogravity> nogravities;
    Uint32 startTime;
    Uint32 lastPlayTime;
    TTF_Font* font;
    SDL_Texture* heartTexture;
    GameState gameState;
    string formatTime(int timeInSeconds);
    void initSDL();
    void logSDLError(std::ostream& os, const std::string &msg, bool fatal);
    void drawMenu();
    void drawGameover();
    void handleMenuInput(SDL_Event& e,bool& quit);
    void handlePlayingInput(SDL_Event& e,bool& quit);
    void handleGameoverInput(SDL_Event& e,bool& quit);
    void handleHighscore(SDL_Event& e,bool& quit);
    void update();
    void render();
    void quitSDL();
    void spawnEnemy();
    void spawnBigE();
    void spawnItem();
    void drawHighscore();
    Uint32 getElapsedTime();
    void waitUntilKeyPressed();
    void initElement();
    bool isCollision( const SDL_Rect& rect1,const SDL_Rect& rect2);
    bool ismulti,player1lose,resultSaved;
    void singerplayer();
    Uint32 frameStart;
    Uint32 lastEnemySpawnTime;
    Uint32 lastItemSpawnTime;
    Uint32 lastBigeSpawnTime;
    int widthbutton1;
    int heightbutton1;
    int widhbutton2;
    int heightbutton2;
    int widthbutton3;
    int heightbutton3;
    TTF_Font* font36 ;
    TTF_Font* font68 ;
    TTF_Font* font28 ;
    TTF_Font* font32 ;
    bool checkPlayerEnemyCollision( Character& player,  Enemy& enemy);
    bool checkPlayerSkillCollision( Character& player,  Skill& skill);
    bool checkPlayerCharacterCollision( Character& player,  Character& player2);
    bool checkPlayerBigeCollision( Character& player,  BigE& bige);
    void buttoncanclick(const string& text, SDL_Color color, int x,int y, TTF_Font* font,int &widthtexture,int &heighttexture);
    void buttoncantclick(const string& text, SDL_Color color, int x,int y, TTF_Font* font);
    void buttonclick(const string& path, SDL_Color color, int x,int y, TTF_Font* font,int &widthtexture,int &heighttexture);
//    bool cmpstringtime(string a,string b);
    float frameTime;

};

#endif // GAME_H
