#include "xy.hpp"

using namespace xd;

void XY::draw(const vec4& color) {
    push();
    stroke(color);
    strokeWeight(3.0f);
    point(x, y);
    pop();
}