#include "firework.hpp"

Firework::Firework(vec2 position) {
    rocket = new Particle();
    rocket->position = position;
    rocket->velocity = vec2(0.0f, random(-12.0f, -13.0f));
    rocket->color = vec3(1.0f, 0.0f, 0.0f);
}

Firework::~Firework() {
    delete rocket;
    for (Particle* particle : particles) {
        delete particle;
    }
}

void Firework::applyForce(vec2 force) {
    if (!exploded) {
        rocket->applyForce(force);
    } else {
        for (Particle* particle : particles) {
            particle->applyForce(force);
        }
    }
}

void Firework::update() {
    if (!exploded) {
        rocket->update();
        if (rocket->velocity.y >= 0.0f) {
            explode();
        }
    } else {
        for (Particle* particle : particles) {
            particle->velocity *= 0.9;
            particle->update();
        }
        vector<Particle*>::iterator it = particles.begin();
        while(it != particles.end()) {
            if ((*it)->isDead()) {
                it = particles.erase(it);
            } else {
                it++;
            }
        }
    }
}

void Firework::explode() {
    vec3 color = vec3(random(0.0f, 1.0f), random(0.0f, 1.0f), random(0.0f, 1.0f));
    for (int i = 0; i < 200; i++) {
        Particle* particle = new Particle();
        particle->position = rocket->position;
        float angle = random(0.0, TWO_PI);
        float magnitude = random(2.0f, 14.0f);
        particle->velocity = vec2(magnitude * cosf(angle), magnitude * sinf(angle));
        particle->lifespan = random(90.0f, 110.0f);
        particle->color = color;
        particles.push_back(particle);
    }
    exploded = true;
}

void Firework::draw() {
    if (!exploded) {
        rocket->draw();
    } else {
        for (Particle* particle : particles) {
            particle->draw();
        }
    }
}

bool Firework::isDone() {
    return exploded && particles.empty();
}
