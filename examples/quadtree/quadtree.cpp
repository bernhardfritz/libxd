#include "quadtree.hpp"

using namespace xd;

QuadTree::~QuadTree() {
    delete nw;
    delete ne;
    delete sw;
    delete se;
}

bool QuadTree::insert(XY p) {
    if (!boundary.containsPoint(p)) {
        return false;
    }
    
    if (points.size() < CAPACITY) {
        points.push_back(p);
        return true;
    }

    if (nw == nullptr) {
        subdivide();
    }

    return nw->insert(p) || ne->insert(p) || sw->insert(p) || se->insert(p);
}

template <typename T>
void concat(vector<T>& a, const vector<T>& b) {
    a.insert(end(a), begin(b), end(b));
}

vector<XY> QuadTree::queryRange(AABB& range) {
    vector<XY> pointsInRange;

    if (!boundary.intersectsAABB(range)) {
        return pointsInRange;
    }

    for (XY& p : points) {
        if (range.containsPoint(p)) {
            pointsInRange.push_back(p);
        }
    }

    if (nw == nullptr) {
        return pointsInRange;
    }

    concat(pointsInRange, nw->queryRange(range));
    concat(pointsInRange, ne->queryRange(range));
    concat(pointsInRange, sw->queryRange(range));
    concat(pointsInRange, se->queryRange(range));

    return pointsInRange;
}

void QuadTree::subdivide() {
    float halfDimension = boundary.halfDimension / 2.0f;
    nw = new QuadTree(AABB(XY(boundary.center.x - halfDimension, boundary.center.y - halfDimension), halfDimension));
    ne = new QuadTree(AABB(XY(boundary.center.x + halfDimension, boundary.center.y - halfDimension), halfDimension));
    sw = new QuadTree(AABB(XY(boundary.center.x - halfDimension, boundary.center.y + halfDimension), halfDimension));
    se = new QuadTree(AABB(XY(boundary.center.x + halfDimension, boundary.center.y + halfDimension), halfDimension));

    for (XY& p : points) {
        if (nw->insert(p) || ne->insert(p) || sw->insert(p) || se->insert(p)) {
            continue;
        }
    }   
}

void QuadTree::draw(const vec4& boundaryColor, const vec4& pointColor) {
    boundary.draw(boundaryColor);

    for (XY& p : points) {
        p.draw(pointColor);
    }
    
    if (nw == nullptr) {
        return;
    }

    nw->draw(boundaryColor, pointColor);
    ne->draw(boundaryColor, pointColor);
    sw->draw(boundaryColor, pointColor);
    se->draw(boundaryColor, pointColor);
}