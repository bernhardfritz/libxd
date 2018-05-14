#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include "sprite.hpp"
#include <xd/image.hpp>

class Spritesheet {
public:
    xd::Image* img;
    int columns, rows;
    std::vector<Sprite> sprites;

    Spritesheet(xd::Image* img, int columns, int rows);
};

#endif /* SPRITESHEET_HPP */