#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <xd/image.hpp>

class Sprite {
public:
    xd::Image* img;
    float sx, sy, sWidth, sHeight;

    Sprite(xd::Image* img, float sx, float sy, float sWidth, float sHeight)
        : img(img)
        , sx(sx)
        , sy(sy)
        , sWidth(sWidth)
        , sHeight(sHeight) {
    }

    void draw(float dx, float dy, float dWidth, float dHeight, bool flipHorizontally = false, bool flipVertically = false);
};

#endif /* SPRITE_HPP */