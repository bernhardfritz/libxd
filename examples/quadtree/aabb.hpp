#ifndef AABB_HPP
#define AABB_HPP

#include "xy.hpp"
#include <xd/xd.hpp>

class AABB {
public:
    XY center;
    float halfDimension;

    AABB(XY center, float halfDimension)
        : center(center)
        , halfDimension(halfDimension) {
    };

    bool containsPoint(XY& point);
    bool intersectsAABB(AABB& other);

    void draw(const glm::vec4& color);
};

#endif /* AABB_HPP */