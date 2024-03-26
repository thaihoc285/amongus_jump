#include "invisible.h"
Invisible::Invisible(Character& playerinvisible,Uint32 starttime)
    : player(&playerinvisible),
    inittime(starttime),
    ghostmonster(false){}
void Invisible::endtime() {
    player->numlives = 1;
    if(ghostmonster){
        player->pathleft = "image/mtblackleft.png";
        player->pathright = "image/mtblackright.png";
        player->playersize = 70;
        player->ismonster = true;
    }else{
        player->pathleft = playerleft;
        player->pathright = playerright;
    }
    player->path = player->pathright;
}
void Invisible::initplayer(string playerpathleft,string playerpathright) {
    playerleft = playerpathleft;
    playerright = playerpathright;
    player->numlives = 10000000;
    player->pathleft="image/ghostleft.png";
    player->pathright="image/ghostright.png";
    if(player->ismonster)ghostmonster = true;
    player->ismonster =false;
    player->playersize = 50;
    player->path = "image/ghostright.png";
}
