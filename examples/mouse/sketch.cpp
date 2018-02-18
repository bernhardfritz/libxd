#include <xd.hpp>

using namespace xd;

float mouseX;
float mouseY;
vec4 lineColor;
float lineWidth;

void onMouseMoved(float x, float y) {
    mouseX = x;
    mouseY = y;
}

void onMousePressed(int button) {
    if (button == MOUSE_BUTTON_LEFT) {
        lineColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);   
    } else if (button == MOUSE_BUTTON_RIGHT) {
        lineColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
    } else if (button == MOUSE_BUTTON_MIDDLE) {
        lineColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
    }
}

void onMouseReleased(int button) {
    lineColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

void onMouseWheel(float delta) {
    lineWidth += delta;
}

void setup() {
    mouseMoved(onMouseMoved);
    mousePressed(onMousePressed);
    mouseReleased(onMouseReleased);
    mouseWheel(onMouseWheel);
    lineColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    lineWidth = 1.0f;
}

void draw() {
    background(vec4(1.0f));
    stroke(lineColor);
    strokeWeight(lineWidth);
    line(mouseX, 0, mouseX, height);
    line(0, mouseY, width, mouseY);
}

void destroy() {

}
