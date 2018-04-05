#ifndef XY_HPP
#define XY_HPP

#include <xd/xd.hpp>

class XY {
public:
    float x;
    float y;

    XY(float x, float y)
        : x(x)
        , y(y) {
    };

    void draw(const glm::vec4& color);
};

#endif /* XY_HPP */