#include "astar.hpp"
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

struct Node {
    int x, y;
    float gScore, hScore;
    Node* cameFrom;

    Node(int x, int y, float gScore, float hScore, Node* cameFrom)
        : x(x)
        , y(y)
        , gScore(gScore)
        , hScore(hScore)
        , cameFrom(cameFrom) {
    }
    bool hasCoords(int x, int y) { return this->x == x && this->y == y; }
};

struct NodeCompare {
    bool operator()(const Node* a, const Node* b) { return a->gScore + a->hScore > b->gScore + b->hScore; }
};

template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>
> struct MyPriorityQueue : std::priority_queue<T, Container, Compare> {
    typename Container::iterator begin() { return std::priority_queue<T, Container, Compare>::c.begin(); }
    typename Container::iterator end() { return std::priority_queue<T, Container, Compare>::c.end(); }
}; // MyPriorityQueue is an extension of std::priority_queue that allows iteration

const float SQUARE_ROOT_OF_TWO = sqrtf(2.0f);

float AStar::heuristic_cost_estimate(int x1, int y1, int x2, int y2) {
    if (moveDiagonally) {
        return sqrtf(powf(x1 - x2, 2.0f) + powf(y1 - y2, 2.0f)); // euclidian distance
    } else {
        return abs(x1 - x2) + abs(y1 - y2); // manhattan distance
    }
}

/*
    Implementation of A* search algorithm based on https://en.wikipedia.org/wiki/A*_search_algorithm
*/
vector<pair<int, int>> AStar::findPath(int x1, int y1, int x2, int y2) {
    vector<pair<int, int>> path;
    if (isCollisionAt(x1, y1) || isCollisionAt(x2, y2)) {
        return path;
    }
    vector<Node*> closedSet;
    MyPriorityQueue<Node*, vector<Node*>, NodeCompare> openSet;
    Node* start = new Node(x1, y1, 0.0f, heuristic_cost_estimate(x1, y1, x2, y2), nullptr);
    openSet.push(start);

    Node* current = nullptr;
    while (!openSet.empty()) {
        current = openSet.top();
        if (current->hasCoords(x2, y2)) {
            break;
        }

        openSet.pop();
        closedSet.push_back(current);

        for (int i = 0; i < (moveDiagonally ? 8 : 4); i++) {
            int x = current->x + directions[i].first;
            int y = current->y + directions[i].second;
            if (x < 0 || x >= cols || y < 0 || y >= rows || isCollisionAt(x, y)) {
                continue;
            }
            bool cont = false;
            for (Node* node : closedSet) {
                if (node->hasCoords(x, y)) {
                    cont = true;
                    break;
                }
            }
            if (cont) {
                continue;
            }

            int tentative_gScore = current->gScore + (i < 4 ? 1.0f : SQUARE_ROOT_OF_TWO);

            Node* neighbor = nullptr;
            for (Node* node : openSet) {
                if (node->hasCoords(x, y)) {
                    neighbor = node;
                    break;
                }
            }
            if (neighbor == nullptr) { // neighbor not in openSet
                neighbor = new Node(x, y, tentative_gScore, heuristic_cost_estimate(x, y, x2, y2), current);
                openSet.push(neighbor);
            } else if (tentative_gScore < neighbor->gScore) {
                neighbor->cameFrom = current;
                neighbor->gScore = tentative_gScore;
            }
        }
    }

    if (current != nullptr && current->hasCoords(x2, y2)) {
        while(current != nullptr) {
            path.push_back({current->x, current->y});
            current = current->cameFrom;
        }
        reverse(path.begin(), path.end());
    }

    return path;
}
