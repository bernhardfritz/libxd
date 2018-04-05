#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "aabb.hpp"
#include <xd/xd.hpp>

#define CAPACITY 4

class QuadTree {
private:
    AABB boundary;
    std::vector<XY> points;
    QuadTree *nw, *ne, *sw, *se;

public:
    QuadTree(AABB boundary)
        : boundary(boundary)
        , points({})
        , nw(nullptr)
        , ne(nullptr)
        , sw(nullptr)
        , se(nullptr) {
    }

    ~QuadTree();
    
    bool insert(XY p);
    std::vector<XY> queryRange(AABB& range);

    void draw(const glm::vec4& boundaryColor, const glm::vec4& pointColor);
    
private:
    void subdivide();
};

#endif /* QUADTREE_HPP */