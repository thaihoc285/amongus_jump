#include "../../Headers/characters/ai.h"
#include <algorithm>

AI::AI(int startX, int startY, int startVelX, int startVelY, double gravity, SDL_Color startColor, std::string left, std::string right, int heart, int sizep)
    : Character(startX, startY, startVelX, startVelY, gravity, startColor, left, right, heart, sizep),
      threatThreshold(100){}

double AI::calculateDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void AI::update(const std::vector<Enemy>& enemies, const std::vector<BigE>& biges) {

    int closestThreatDistance = threatThreshold;
    blockedLeft = false;
    blockedRight = false;
    for (const auto& enemy : enemies) {
        double distance = calculateDistance(x, y, enemy.x, enemy.y);
        if (distance < closestThreatDistance) {
            closestThreatDistance = distance;
            if (x < enemy.x&&!(blockedRight)) {
                velX = -moveOx;
                blockedRight = true;
            } else if(!(blockedLeft)&&x>=enemy.x){
                velX = moveOx;
                blockedLeft = true;
            }
            if(y < enemy.y && multiJump <= 10){
                multiJump ++;
                velY = -5;
            }else if(y < enemy.y && multiJump > 12){
                multiJump = 0;
            }else if(y < enemy.y && multiJump > 10)multiJump ++;
            else if(y>enemy.y)velY = 5;
        }
    }


//    for (const auto& bige : biges) {
//        double distance = calculateDistance(x, y, bige.x, bige.y);
//        if (distance < closestThreatDistance+200) {
//            closestThreatDistance = distance;
//            if (x < bige.x) {
//                velX = -moveOx; // Di chuyển về bên trái
//                blockedRight = true;
//            } else {
//                velX = moveOx; // Di chuyển về bên phải
//                blockedLeft = true;
//            }
////            avoidX = true;
////            avoidY = true;
//        }
//    }
//    if (!avoidX) {
////        velX = 0;
//        blockedLeft = blockedRight = false;
//    }
    if(y==0)velY = 9;
    if(x<=SQUARE_SIZE&&x>0){
        velX = moveOx;
        blockedLeft = true;
    }
    else if(x+playersize>=SCREEN_WIDTH-SQUARE_SIZE && x+playersize < SCREEN_WIDTH){
        velX = -moveOx;
        blockedRight = true;
    }

    if (blockedRight && blockedLeft) {
        velY = -9;
    }


}
