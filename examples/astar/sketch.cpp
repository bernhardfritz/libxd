#include <xd/xd.hpp>
#include "astar.hpp"

using namespace xd;

const int rows = 100, cols = 100;
float w, h, wh, hh;
bool collisionGrid[cols * rows] = { false };
int gx = cols - 1, gy = rows - 1;
AStar* astar;
vector<pair<int, int>> path;

int coordsToIndex(int x, int y) {
    return y * cols + x;
}

void initCollisionGrid() {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            collisionGrid[coordsToIndex(x, y)] = random(0.0f, 1.0f) < 0.25f;
        }
    }
    collisionGrid[coordsToIndex(cols / 2, rows / 2)] = false; // ensure there is no collision at the start point
}

void initAStar() {
    delete astar;
    astar = new AStar(collisionGrid, cols, rows, true);
    path = astar->findPath(cols / 2, rows / 2, gx, gy);
}

void onMouseMoved(float x, float y) {
    int prevGx = gx, prevGy = gy;
    gx = glm::clamp<int>(x / w, 0, cols - 1);
    gy = glm::clamp<int>(y / h, 0, rows - 1);
    if (gx != prevGx || gy != prevGy) {
        initAStar();
    }
}

void setup() {
    size(500, 500);
    w = (float) width / cols;
    h = (float) height / rows;
    wh = w / 2.0f;
    hh = h / 2.0f;
    initCollisionGrid();
    initAStar();
    mouseMoved(onMouseMoved);
}

void draw() {
    background(vec4(1.0f));
    ellipseMode(CORNER);
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (collisionGrid[coordsToIndex(x, y)]) {
                fill(vec4(0.0f, 0.0f, 0.0f, 1.0f));
                noStroke();
                ellipse(x * w, y * h, w, h);
            }
        }
    }
    if (path.size() > 1) {
        for (int i = 1; i < path.size(); i++) {
            stroke(vec4(1.0f, 0.0f, 1.0f, 1.0f));
            strokeWeight(wh);
            line(path[i - 1].first * w + wh, path[i - 1].second * h + hh, path[i].first * w + wh, path[i].second * h + hh);
        }
    }
}

void destroy() {
    delete astar;
}
