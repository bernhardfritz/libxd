#include "particle.hpp"

using namespace xd;

Particle::Particle() {
    lifespan = -1;
    color = vec3(1.0f);
    mass = random(0.7, 1.0);
}

void Particle::applyForce(vec2 force) {
    acceleration += force * mass;
}

void Particle::update() {
    velocity += acceleration;
    position += velocity;
    acceleration = vec2(0);
    if (lifespan > 0) {
        lifespan--;
    }
}

void Particle::draw() {
    stroke(vec4(color, lifespan == -1 ? 1.0f : map(lifespan, 0.0f, 100.0f, 0.0f, 1.0f)));
    strokeWeight(mass * 3.0f);
    point(position.x, position.y);
}

bool Particle::isDead() {
    return lifespan == 0;
}
