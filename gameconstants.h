#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H
#include<vector>
#include <string>
#include <iostream>
#include <SDL.h>
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 650;
const int SQUARE_SIZE = 50;
const int ITEM_SIZE = 40;
const std::string WINDOW_TITLE = "Among us";
const int FPS = 60;
const float FrameDelay = (float)1000 / FPS;
const SDL_Color textColor = {255, 255, 255, 255};
#endif // GAME_CONSTANTS_H
