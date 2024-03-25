#include "invisible.h"
Invisible::Invisible(Character& playerinvisible,Uint32 starttime)
    : player(&playerinvisible),
    inittime(starttime){}
void Invisible::endtime() {
    player->numlives = 1;
    player->pathleft = playerleft;
    player->pathright = playerright;
}
void Invisible::initplayer(string playerpathleft,string playerpathright) {
    playerleft = playerpathleft;
    playerright = playerpathright;
    player->pathleft="image/ghostleft.png";
    player->pathright="image/ghostright.png";
    player->path = "image/ghostright.png";
}
