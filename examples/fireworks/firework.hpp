#ifndef FIREWORK_HPP
#define FIREWORK_HPP

#include "particle.hpp"
#include <iostream>

class Firework {
public:
    Particle* rocket;
    bool exploded;
    vector<Particle*> particles;

    Firework(vec2 position);
    ~Firework();

    void applyForce(vec2 force);
    void update();
    void explode();
    void draw();
    bool isDone();
};

#endif /* FIREWORK_HPP */
