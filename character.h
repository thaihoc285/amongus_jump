#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL.h>
#include <string>
#include <SDL_image.h>
using namespace std;
class Character {
public:
    int x, y;
    bool isJumping;
    bool isJumping2;
    double velX, velY;
    double aceX, aceY;
    string path, pathleft ,pathright;
    SDL_Color startColor;
    bool isKeyPressed[SDL_NUM_SCANCODES] = {false};
    SDL_Texture* chTexture;
    Character(int startX, int startY, int startVelX, int startVelY, SDL_Color startColor,string left,string right);
    void handleInput();
    void handleInput2();
    void GravityCalculation();
    void VelocityCalculation();
    void PositionCalculation();
    void render(SDL_Renderer* renderer);
};

#endif // CHARACTER_H
