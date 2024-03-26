#include "Character.h"
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 650;
Character::Character(int startX, int startY, int startVelX, int startVelY, SDL_Color startColor,string left,string right,int heart,int sizep)
    : chTexture(nullptr),
      x(startX),
      y(startY),
      velX(startVelX),
      velY(startVelY),
      aceX(0),
      aceY(0),
      isJumping(false),
      isJumping2(false),
      pathleft(left),
      pathright(right),
      path(right),
      playersize(sizep),
      ismonster(false),
      isghost(false),
      numlives(heart){}

void Character::handleInput() {
    if (isKeyPressed[SDL_SCANCODE_UP] && !isJumping) {
        velY = -9;
        isJumping = true;
    } else if (isKeyPressed[SDL_SCANCODE_DOWN]) {
        velY = 20;
    }
    if (isKeyPressed[SDL_SCANCODE_LEFT]) {
        velX = -5;
        path = pathleft;
    } else if (isKeyPressed[SDL_SCANCODE_RIGHT]) {
        velX = 5;
        path = pathright;
    } else {
        velX = 0;
    }
}

void Character::handleInput2() {
    if (isKeyPressed[SDL_SCANCODE_W] && !isJumping2) {
        velY = -9;
        isJumping2 = true;
    } else if (isKeyPressed[SDL_SCANCODE_S]) {
        velY = 20;
    }
    if (isKeyPressed[SDL_SCANCODE_A]) {
        velX = -5;
        path = pathleft;
    } else if (isKeyPressed[SDL_SCANCODE_D]) {
        velX = 5;
        path = pathright;
    } else {
        velX = 0;
    }
}

void Character::GravityCalculation() {
    aceY = 0.6;
}

void Character::VelocityCalculation() {
    velY += aceY;
    velX += aceX;
}

void Character::PositionCalculation() {
    x += velX;
    y += velY;

    if (x < 0) {
        x = 0;
    }
    if (x + playersize > SCREEN_WIDTH) {
        x = SCREEN_WIDTH - playersize;
    }
    if (y < 0) {
        y = 0;
    }
    if (y + playersize > SCREEN_HEIGHT) {
        y = SCREEN_HEIGHT - playersize;
    }
}

void Character::render(SDL_Renderer* renderer) {
    SDL_Surface* loadedSurface = IMG_Load( path.c_str());
    chTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
    SDL_FreeSurface( loadedSurface );
    SDL_Rect characterRect = {x, y, playersize, playersize};
    SDL_RenderCopy(renderer, chTexture, NULL, &characterRect);
    SDL_DestroyTexture(chTexture);
}
