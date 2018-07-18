#include <xd/xd.hpp>
#include "lightpass.hpp"

using namespace xd;

int idx = 0;

LightPass* lightPass;
Light lights[] = {
    {
        vec2(0.25, 0.5),
        vec4(1.0, 0.0, 0.0, 1.0),
        0.05
    },
    {
        vec2(0.5, 0.5),
        vec4(0.0, 1.0, 0.0, 1.0),
        0.05
    },
    {
        vec2(0.75, 0.5),
        vec4(0.0, 0.0, 1.0, 1.0),
        0.05
    }
};

void onMouseMoved(float x, float y) {
    lights[idx].lightPos.x = x / width;
    lights[idx].lightPos.y = 1 - y / height;
}

void onKeyPressed(int key) {
    switch (key) {
        case '1':
            idx = 0;
            break;
        case '2':
            idx = 1;
            break;
        case '3':
            idx = 2;
            break;
    }
}

void setup() {
    size(640, 480);
    lightPass = new LightPass({passthrough});
    lightPass->setLights(lights);
    renderPass(lightPass);
    mouseMoved(onMouseMoved);
    keyPressed(onKeyPressed);
}

void draw() {
    background(vec4(1.0, 1.0, 1.0, 1.0));
}

void destroy() {
    delete lightPass;
}
