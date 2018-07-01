#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "animation.hpp"

class Character {
public:
    Character(Animation *walkingUp,
              Animation *walkingRight,
              Animation *walkingDown,
              Animation *walkingLeft,
              float height,
              float width) :
                    up(walkingUp),
                    right(walkingRight),
                    down(walkingDown),
                    left(walkingLeft),
                    direction(2),
                    speed(0.0f),
                    x(0.0f),
                    y(0.0f),
                    height(height),
                    width(width) {
              }

    // draw the character, but choose its position, scale and mirroring
    void draw(float dx,
              float dy,
              float dWidth,
              float dHeight,
              bool flipHorizontally = false,
              bool flipVertically = false);

    // draw the character, but scale it
    void draw(float dWidth,
              float dHeight);

    // draw the character as it is
    void draw();

    // change the character's direction
    void changeDirection(int direction);

    // change the character's speed
    void changeSpeed(float speed);

    // make the character move (in its direction with its speed)
    void move();

private:
    Animation *up;
    Animation *right;
    Animation *down;
    Animation *left;
    short direction; // 0 = up, 1 = right, 2 = down, 3 = left
    float speed;
    float x, y;
    float height, width;
};

#endif /* CHARACTER_HPP */