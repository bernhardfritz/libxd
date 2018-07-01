#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "sprite.hpp"

class Animation {
public:
    std::vector<Sprite> frames;
    int frameDuration; // in ms
    int frameIndex;
    int timestamp; // in ms

    Animation(std::initializer_list<Sprite> frames, int frameDuration)
        : frames(frames)
        , frameDuration(frameDuration)
        , frameIndex(0)
        , timestamp(0) {
    }

    void draw(float dx, float dy, float dWidth, float dHeight, bool flipHorizontally = false, bool flipVertically = false);
};


#endif /* ANIMATION_HPP */