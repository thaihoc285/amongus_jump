#include "skill.h"
const int ITEM_SIZE = 40;
Skill::Skill(int startX, int startY,string pathskill)
    : x(startX),
      y(startY),
      path(pathskill),
      skillTexture(NULL) {}

void Skill::init(SDL_Renderer* renderer) {
    SDL_Surface* loadedSurface = IMG_Load( path.c_str());
    skillTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
    SDL_FreeSurface(loadedSurface);
}
void Skill::render(SDL_Renderer* renderer) const {
    SDL_Rect skillRect = {x, y, ITEM_SIZE, ITEM_SIZE};
    SDL_RenderCopy(renderer, skillTexture, NULL, &skillRect);
}

