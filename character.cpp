#include "Character.h"
Character::Character(int startX, int startY, int startVelX, int startVelY,double grvt,SDL_Color startColor,string left,string right,int heart,int sizep)
    : chTexture(nullptr),
      x(startX),
      y(startY),
      velX(0),
      velY(0),
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
      isgravity(true),
      numlives(heart),
      moveOx(startVelX),
      moveOy(startVelY),
      gravityx(grvt){}

void Character::handleInput() {
    if (isKeyPressed[SDL_SCANCODE_UP] && !isJumping) {
        if(isgravity){
            velY = -9;
            isJumping = true;
        }else y-=(moveOx+2);
    } else if (isKeyPressed[SDL_SCANCODE_DOWN]) {
        if(isgravity)velY = 20;
        else y+=(moveOx+2);
    }
    if (isKeyPressed[SDL_SCANCODE_LEFT]) {
        if(isgravity)velX = -moveOx;
        else x-= (moveOx+1);
        path = pathleft;
    } else if (isKeyPressed[SDL_SCANCODE_RIGHT]) {
        if(isgravity)velX = moveOx;
        else x+=(moveOx+1);
        path = pathright;
    } else {
        velX = 0;
    }
}

void Character::handleInput2() {
    if (isKeyPressed[SDL_SCANCODE_W] && !isJumping2) {
        if(isgravity){
            velY = -9;
            isJumping2 = true;
        }else y-=(moveOx+2);
    } else if (isKeyPressed[SDL_SCANCODE_S]) {
        if(isgravity)velY = 20;
        else y+=(moveOx+2);
    }
    if (isKeyPressed[SDL_SCANCODE_A]) {
        if(isgravity)velX = -moveOx;
        else x-= (moveOx+1);
        path = pathleft;
    } else if (isKeyPressed[SDL_SCANCODE_D]) {
        if(isgravity)velX = moveOx;
        else x+=(moveOx+1);
        path = pathright;
    } else {
        velX = 0;
    }
}

void Character::GravityCalculation() {
    aceY = gravityx;
}

void Character::VelocityCalculation() {
    velY += aceY;
    velX += aceX;
}

void Character::PositionCalculation() {
    if(isgravity){
        x += velX;
        y += velY;
    }
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
