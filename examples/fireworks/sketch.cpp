#include "firework.hpp"
#include <xd.hpp>

vector<Firework*> fireworks;
vec2 gravity;

void setup() {
    size(640, 480);
    gravity = vec2(0.0f, 0.2f);
    noStroke();
}

void draw() {
    background(vec4(vec3(0.0f), 1.0f));
    if (random(0, 1) < 0.1f) {
        Firework* firework = new Firework(vec2(random(0, width), height));
        fireworks.push_back(firework);
    }
    for (Firework* firework : fireworks) {
        firework->applyForce(gravity);
        firework->update();
        if (firework->isDone()) {
            vector<Firework*>::iterator it = fireworks.begin();
            while(it != fireworks.end()) {
                if ((*it)->isDone()) {
                    it = fireworks.erase(it);
                } else {
                    it++;
                }
            }
        } else {
            firework->draw();
        }
    }
}

void destroy() {
    for (Firework* firework : fireworks) {
        delete firework;
    }
}
