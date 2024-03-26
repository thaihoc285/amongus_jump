#include "invisible.h"
Invisible::Invisible(Character& playerinvisible,Uint32 starttime)
    : player(&playerinvisible),
    inittime(starttime){}
void Invisible::endtime() {
    player->numlives = 1;
    if(player->ismonster){
        player->pathleft = "image/mtblackleft.png";
        player->pathright = "image/mtblackright.png";
        player->playersize = 70;
    }else{
        player->pathleft = playerleft;
        player->pathright = playerright;
    }
    player->path = player->pathright;
    player->isghost = false;
}
void Invisible::initplayer(string playerpathleft,string playerpathright) {
    playerleft = playerpathleft;
    playerright = playerpathright;
    player->numlives = 10000000;
    player->pathleft="image/ghostleft.png";
    player->pathright="image/ghostright.png";
    player->path = player->pathright;
    player->playersize = 50;
    player->isghost = true;
}
