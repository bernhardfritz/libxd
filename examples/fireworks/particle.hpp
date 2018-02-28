#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <xd/xd.hpp>

class Particle {
public:
    vec2 position;
    vec2 velocity;
    vec2 acceleration;
    int lifespan;
    vec3 color;
    float mass;

    Particle();

    void applyForce(vec2 force);
    void update();
    void draw();
    bool isDead();
};

#endif /* PARTICLE_HPP */
