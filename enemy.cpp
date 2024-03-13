#include "Enemy.h"
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 650;
const int SQUARE_SIZE = 50;
Enemy::Enemy(int startX, int startY, int startVelX, int startVelY,string pathenemy)
    : x(startX),
      y(startY),
      velX(startVelX),
      velY(startVelY),
      path(pathenemy) {}

void Enemy::move() {
    x += velX;
    y += velY;

    if (x < 0 || x + SQUARE_SIZE > SCREEN_WIDTH) {
        velX = -velX;
    }
    if (y < 0 || y + SQUARE_SIZE > SCREEN_HEIGHT) {
        velY = -velY;
    }
}

void Enemy::render(SDL_Renderer* renderer) const {
    SDL_Surface* loadedSurface = IMG_Load( path.c_str());
    SDL_Texture* eTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
    SDL_FreeSurface( loadedSurface );
    Uint32 sprite = SDL_GetTicks()/ 1000 % 5;
    SDL_Rect characterRect = {x, y, SQUARE_SIZE, SQUARE_SIZE};
    SDL_Rect srcrect = { 0, sprite * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
    SDL_RenderCopy(renderer, eTexture, &srcrect, &characterRect);
    SDL_DestroyTexture(eTexture);
}

