#include "Character.h"

Character::Character(int startX, int startY, int startVelX, int startVelY, SDL_Color startColor)
    : x(startX),
      y(startY),
      velX(startVelX),
      velY(startVelY),
      aceX(0),
      aceY(0),
      isJumping(false),
      isJumping2(false),
      startColor(startColor) {}

void Character::handleInput() {
    if (isKeyPressed[SDL_SCANCODE_UP] && !isJumping) {
        velY = -9;
        isJumping = true;
    } else if (isKeyPressed[SDL_SCANCODE_DOWN]) {
        velY = 5;
    }
    if (isKeyPressed[SDL_SCANCODE_LEFT]) {
        velX = -5;
    } else if (isKeyPressed[SDL_SCANCODE_RIGHT]) {
        velX = 5;
    } else {
        velX = 0;
    }
}

void Character::handleInput2() {
    if (isKeyPressed[SDL_SCANCODE_W] && !isJumping2) {
        velY = -9;
        isJumping2 = true;
    } else if (isKeyPressed[SDL_SCANCODE_S]) {
        velY = 5;
    }
    if (isKeyPressed[SDL_SCANCODE_A]) {
        velX = -5;
    } else if (isKeyPressed[SDL_SCANCODE_D]) {
        velX = 5;
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

void Character::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, startColor.r, startColor.g, startColor.b, startColor.a);
    SDL_Rect characterRect = {x, y, SQUARE_SIZE, SQUARE_SIZE};
    SDL_RenderFillRect(renderer, &characterRect);
}
