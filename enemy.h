#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>
#include <string>
#include <SDL_image.h>
using namespace std;
class Enemy {
public:
    int x, y;
    double velX, velY;

    Enemy(int startX, int startY, int startVelX, int startVelY,string pathenemy);
    string path;
    void move();
    void move2();
    void render(SDL_Renderer* renderer)const;
};

#endif // ENEMY_H
//
//rendercopy(?,?, &src,&textture);
