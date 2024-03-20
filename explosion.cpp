#include "explosion.h"
Explosion::Explosion(int startX, int startY,string pathExplosion,Uint32 starttime)
    : x(startX),
      y(startY),
      path(pathExplosion),
      explosionTexture(NULL),
      inittime(starttime),
      skillArea({startX - 100, startY - 100, 240, 240}) {}

void Explosion::init(SDL_Renderer* renderer) {
    SDL_Surface* explosionSurface = IMG_Load( path.c_str());
    explosionTexture = SDL_CreateTextureFromSurface( renderer, explosionSurface );
    SDL_FreeSurface(explosionSurface);
}
void Explosion::render(SDL_Renderer* renderer) const {

    Uint32 sprite = (SDL_GetTicks()-inittime)/ 40 % 9;
    SDL_Rect srcexplosionrect = { sprite*238, 0, 237.5, 243 };
    SDL_RenderCopy(renderer, explosionTexture, &srcexplosionrect, &skillArea);
}



