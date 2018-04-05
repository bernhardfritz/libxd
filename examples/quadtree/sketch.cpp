#include "quadtree.hpp"
#include <xd/xd.hpp>

using namespace xd;

const vec4 BLACK = vec4(0.0f, 0.0f, 0.0f, 1.0f);
const vec4 WHITE = vec4(1.0f, 1.0f, 1.0f, 1.0f);
const vec4 GREEN = vec4(0.0f, 1.0f, 0.0f, 1.0f);

QuadTree* quadTree;
AABB aabb(XY(0.0f, 0.0f), 50.0f);

void onMouseMoved(float x, float y) {
    aabb.center = XY(x, y);
}

void setup() {
    size(400, 400);

    quadTree = new QuadTree(AABB(XY(width / 2.0f, height / 2.0f), width / 2.0f));
    for (int i = 0; i < 1000; i++) {
        float r = random(0.0f, width);
        float phi = random(0.0f, TWO_PI);
        vec2 v = vec2(width / 2.0f, height / 2.0f) + r * vec2(cosf(phi), sinf(phi));
        quadTree->insert(XY(v.x, v.y));
    }

    mouseMoved(onMouseMoved);
}

void draw() {
    background(BLACK);
    quadTree->draw(WHITE, WHITE);

    aabb.draw(GREEN);
    for(XY& p : quadTree->queryRange(aabb)) {
        p.draw(GREEN);
    }
}

void destroy() {
    delete quadTree;
}