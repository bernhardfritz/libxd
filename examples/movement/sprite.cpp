#include "sprite.hpp"
#include <xd/xd.hpp>

using namespace xd;

void Sprite::draw(float dx, float dy, float dWidth, float dHeight, bool flipHorizontally, bool flipVertically) {
    image(img, dx, dy, dWidth, dHeight, sx + (flipHorizontally ? sWidth : 0), sy + (flipVertically ? sHeight : 0), sWidth * (flipHorizontally ? -1 : 1), sHeight * (flipVertically ? -1 : 1));
}