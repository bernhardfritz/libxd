#include "aabb.hpp"

using namespace xd;

bool AABB::containsPoint(XY& point) {
    return abs(center.x - point.x) <= halfDimension
        && abs(center.y - point.y) <= halfDimension
    ;
}

bool AABB::intersectsAABB(AABB& other) {
    return abs(center.x - other.center.x) <= halfDimension + other.halfDimension
        || abs(center.y - other.center.y) <= halfDimension + other.halfDimension
    ;
}

void AABB::draw(const vec4& color) {
    push();
    noFill();
    stroke(color);
    rectMode(RADIUS);
    rect(center.x, center.y, halfDimension, halfDimension);
    pop();
}