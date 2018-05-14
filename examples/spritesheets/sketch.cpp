#include "spritesheet.hpp"
#include "animation.hpp"
#include <xd/xd.hpp>

using namespace xd;

Image* img;
Spritesheet* spritesheet;
Animation *animation1, *animation2, *animation3, *animation4;

void setup() {
    size(640, 480);
    img = loadImage("wizard.png");
    spritesheet = new Spritesheet(img, 8, 8);
    animation1 = new Animation({
        spritesheet->sprites[0],
        spritesheet->sprites[1],
        spritesheet->sprites[2],
        spritesheet->sprites[3],
        spritesheet->sprites[8],
        spritesheet->sprites[9],
        spritesheet->sprites[10],
        spritesheet->sprites[11],
        spritesheet->sprites[16],
        spritesheet->sprites[17],
        spritesheet->sprites[18],
        spritesheet->sprites[19],
        spritesheet->sprites[24],
        spritesheet->sprites[25],
        spritesheet->sprites[26],
        spritesheet->sprites[27]
    }, 17);
    animation2 = new Animation({
        spritesheet->sprites[4],
        spritesheet->sprites[5],
        spritesheet->sprites[6],
        spritesheet->sprites[7],
        spritesheet->sprites[12],
        spritesheet->sprites[13],
        spritesheet->sprites[14],
        spritesheet->sprites[15],
        spritesheet->sprites[20],
        spritesheet->sprites[21],
        spritesheet->sprites[22],
        spritesheet->sprites[23],
        spritesheet->sprites[28],
        spritesheet->sprites[29],
        spritesheet->sprites[30],
        spritesheet->sprites[31]
    }, 17);
    animation3 = new Animation({
        spritesheet->sprites[32],
        spritesheet->sprites[33],
        spritesheet->sprites[34],
        spritesheet->sprites[35],
        spritesheet->sprites[40],
        spritesheet->sprites[41],
        spritesheet->sprites[42],
        spritesheet->sprites[43],
        spritesheet->sprites[48],
        spritesheet->sprites[49],
        spritesheet->sprites[50],
        spritesheet->sprites[51],
        spritesheet->sprites[56],
        spritesheet->sprites[57],
        spritesheet->sprites[58],
        spritesheet->sprites[59]
    }, 17);
    animation4 = new Animation({
        spritesheet->sprites[36],
        spritesheet->sprites[37],
        spritesheet->sprites[38],
        spritesheet->sprites[39],
        spritesheet->sprites[44],
        spritesheet->sprites[45],
        spritesheet->sprites[46],
        spritesheet->sprites[47],
        spritesheet->sprites[52],
        spritesheet->sprites[53],
        spritesheet->sprites[54],
        spritesheet->sprites[55],
        spritesheet->sprites[60],
        spritesheet->sprites[61],
        spritesheet->sprites[62],
        spritesheet->sprites[63]
    }, 17);
}

void draw() {
    background(vec4(vec3(0.3f), 1.0f));
    animation1->draw(0.0f, 0.0f, 50.0f, 50.0f);
    animation2->draw(50.0f, 0.0f, 50.0f, 50.0f);
    animation2->draw(100.0f, 0.0f, 50.0f, 50.0f, true);
    animation3->draw(150.0f, 0.0f, 50.0f, 50.0f);
    animation4->draw(200.0f, 0.0f, 50.0f, 50.0f);
    animation4->draw(250.0f, 0.0f, 50.0f, 50.0f, true);
}

void destroy() {
    delete animation1;
    delete animation2;
    delete animation3;
    delete animation4;
    delete spritesheet;
    delete img;
}
