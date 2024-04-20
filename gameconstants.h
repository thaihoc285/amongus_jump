#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H
#include<vector>
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 650;
const int SQUARE_SIZE = 50;
const int ITEM_SIZE = 40;
const int BIGE_SIZE = 200;
const int ENEMY_SPAWN_INTERVAL = 5000;
const int ITEM_SPAWN_INTERVAL = 8000;
const int BIGE_SPAWN_INTERVAL = 28000;
const std::string WINDOW_TITLE = "Among us";
const int FPS = 60;
const float FrameDelay = (float)1000 / FPS;
const SDL_Color textColor = {255, 255, 255, 255};
static Mix_Chunk* sound_cls_item[4];
static Mix_Chunk* sound_gameover;
static Mix_Chunk* sound_monstereat;
static Mix_Chunk* sound_mouseclick;
static Mix_Chunk* sound_jump;
static Mix_Chunk* sound_jump2;
static Mix_Chunk* sound_bg[2];
static Mix_Chunk* sound_enemy[2];

#endif // GAME_CONSTANTS_H
