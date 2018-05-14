#include "spritesheet.hpp"

using namespace xd;

Spritesheet::Spritesheet(Image* img, int columns, int rows) : img(img), columns(columns), rows(rows) {
    float sWidth = (float) img->width / columns;
    float sHeight = (float) img->height / rows;
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            sprites.push_back(Sprite(img, column * sWidth, row * sHeight, sWidth, sHeight));
        }
    }
}