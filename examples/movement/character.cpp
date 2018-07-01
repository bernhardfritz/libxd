#include "character.hpp"
#include <xd/xd.hpp>

using namespace xd;

void Character::draw(float dx,
                     float dy,
                     float dWidth,
                     float dHeight,
                     bool flipHorizontally,
                     bool flipVertically){

    Animation *toUse = down;
    switch(direction){
        case 0:
            // up
            toUse = up;
            break;
        case 1:
            // right
            toUse = right;
            break;
        case 2:
            // down
            toUse = down;
            break;
        case 3:
            // left
            toUse = left;
            break;
        default:
            break;
    }

    toUse->draw(dx, dy, dWidth, dHeight, flipHorizontally, flipVertically);
}

void Character::draw(float dWidth, float dHeight){
    draw(x, y, dWidth, dHeight, false, false);
}

void Character::draw(){
    draw(x, y, width, height, false, false);
}

void Character::changeDirection(int dir){
    direction = dir % 4;
}

void Character::move(){
    switch(direction){
        case 0:
            y -= speed;
            break;
        case 1:
            x += speed;
            break;
        case 2:
            y += speed;
            break;
        case 3:
            x -= speed;
            break;
        default:
            break;
    }
}

void Character::changeSpeed(float newSpeed){
    speed = newSpeed;
}