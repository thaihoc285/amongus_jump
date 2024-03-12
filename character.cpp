#include "Character.h"
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 650;
const int SQUARE_SIZE = 50;
Character::Character(int startX, int startY, int startVelX, int startVelY, SDL_Color startColor,string left,string right)
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
      startColor(startColor){}

void Character::handleInput() {
    if (isKeyPressed[SDL_SCANCODE_UP] && !isJumping) {
        velY = -9;
        isJumping = true;
    } else if (isKeyPressed[SDL_SCANCODE_DOWN]) {
        velY = 21;
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
        velY = 21;
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
    if (x + SQUARE_SIZE > SCREEN_WIDTH) {
        x = SCREEN_WIDTH - SQUARE_SIZE;
    }
    if (y < 0) {
        y = 0;
    }
    if (y + SQUARE_SIZE > SCREEN_HEIGHT) {
        y = SCREEN_HEIGHT - SQUARE_SIZE;
    }
}

//void Character::addtexture(string path ,SDL_Renderer* renderer){
//	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
//
//        chTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
//		SDL_FreeSurface( loadedSurface );
//};

void Character::render(SDL_Renderer* renderer) {
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    chTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
    SDL_FreeSurface( loadedSurface );

//    SDL_SetRenderDrawColor(renderer, startColor.r, startColor.g, startColor.b, startColor.a);
    SDL_Rect characterRect = {x, y, SQUARE_SIZE, SQUARE_SIZE};
//    SDL_RenderFillRect(renderer, &characterRect);
    SDL_RenderCopy(renderer, chTexture, NULL, &characterRect);
}
