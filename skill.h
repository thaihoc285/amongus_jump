#ifndef SKILL_H
#define SKILL_H

#include <SDL.h>
#include "Character.h"
#include "Enemy.h"

class Skill {
public:
    Skill();
    int x, y;
    Skill(int startX, int startY,string path);
    void render(SDL_Renderer* renderer) const;
    void init(SDL_Renderer* renderer);
    SDL_Texture* skillTexture;
    string path;
//    int skillX, skillY;
//    bool active;
//    int power;

    void handleCollision(Character& player);
};

#endif // SKILL_H
