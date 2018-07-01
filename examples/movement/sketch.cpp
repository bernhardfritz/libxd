#include "spritesheet.hpp"
#include "animation.hpp"
#include "character.hpp"
#include <xd/xd.hpp>

using namespace xd;

Image *img;
Spritesheet *spritesheet;
Animation *up, *right, *down, *left;
Character *character;
int keyActive;

void handleKeyPressed(int key){
    // remember the last pressed movement key
    keyActive = key;
    character->changeSpeed(5);
    switch(key){
        case KEY_UP:
            character->changeDirection(0);
            break;
        case KEY_RIGHT:
            character->changeDirection(1);
            break;
        case KEY_DOWN:
            character->changeDirection(2);
            break;
        case KEY_LEFT:
            character->changeDirection(3);
            break;
        default:
            break;
    }
}

void handleKeyReleased(int key){
    // reset the speed to 0 only when the last active
    // movement key has been pressed
    if(keyActive == key){
        keyActive = -1;
        character->changeSpeed(0);
    }
}

void setup() {
    size(640, 480);
    img = loadImage("movement.png");
    spritesheet = new Spritesheet(img, 4, 4);
    up = new Animation({
        spritesheet->sprites[0],
        spritesheet->sprites[1],
        spritesheet->sprites[2],
        spritesheet->sprites[3],
    }, 17);
    right = new Animation({
        spritesheet->sprites[4],
        spritesheet->sprites[5],
        spritesheet->sprites[6],
        spritesheet->sprites[7],
    }, 17);
    down = new Animation({
        spritesheet->sprites[8],
        spritesheet->sprites[9],
        spritesheet->sprites[10],
        spritesheet->sprites[11],
    }, 17);
    left = new Animation({
        spritesheet->sprites[12],
        spritesheet->sprites[13],
        spritesheet->sprites[14],
        spritesheet->sprites[15],
    }, 17);

    character = new Character(up, right, down, left, 30, 30);

    keyActive = -1;
    keyPressed(handleKeyPressed);
    keyReleased(handleKeyReleased);
}

void draw() {
    background(vec4(vec3(0.3f), 1.0f));
    character->move();
    character->draw();
}

void destroy() {
    delete img;
    delete up;
    delete right;
    delete down;
    delete left;
    delete character;
}
