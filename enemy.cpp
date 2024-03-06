#include "Enemy.h"

Enemy::Enemy(int startX, int startY, int startVelX, int startVelY)
    : x(startX),
      y(startY),
      velX(startVelX),
      velY(startVelY) {}

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

void Enemy::move2() {
    x += velX;
    if (x < 0 || x + SQUARE_SIZE > SCREEN_WIDTH) {
        velX = -velX;
    }
}

void Enemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 250, 0, 0, 0);
    SDL_Rect enemyRect = {x, y, SQUARE_SIZE, SQUARE_SIZE};
    SDL_RenderFillRect(renderer, &enemyRect);
}

