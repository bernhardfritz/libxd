#include <xd.hpp>

using namespace xd;

vec2 position;
vec2 velocity;
vec2 acceleration;
float throttle = 0.0f;

float angle = -HALF_PI;
float rotationVelocity = 0.0f;
float rotationAcceleration = 0.0f;
float rotationDirection = 0.0f;

void onKeyPressed(int key) {
    switch (key) {
        case KEY_UP:
        case 'W':
            throttle = 1.0f;
            break;
        case KEY_LEFT:
        case 'A':
            rotationDirection = -1.0f;
            break;
        case KEY_RIGHT:
        case 'D':
            rotationDirection = 1.0f;
            break;
    }
}

void onKeyReleased(int key) {
    switch (key) {
        case KEY_UP:
        case 'W':
            throttle = 0.0f;
            break;
        case KEY_LEFT:
        case 'A':
        case KEY_RIGHT:
        case 'D':
            rotationDirection = 0.0f;
            break;
    }
}

void setup() {
    size(640, 480);
    glfwSetInputMode(glfwGetCurrentContext(), GLFW_STICKY_KEYS, GLFW_TRUE);
    keyPressed(onKeyPressed);
    keyReleased(onKeyReleased);
    position = vec2(width / 2 , height / 2);
}

void draw() {
    background(vec4(vec3(0.3f), 1.0f));
    rotationAcceleration = rotationDirection * 0.01f;
    rotationVelocity += rotationAcceleration;
    rotationVelocity *= 0.9f;
    angle += rotationVelocity;
    acceleration = throttle * 0.1f * vec2(cosf(angle), sinf(angle));
    velocity += acceleration;
    velocity *= 0.99f;
    position += velocity;
    if (position.x < 0) {
        position.x = width;
    } else if (position.x > width) {
        position.x = 0;
    }
    if (position.y < 0) {
        position.y = height;
    } else if (position.y > height) {
        position.y = 0;
    }
    translate(position.x, position.y);
    rotate(angle);
    scale(10.0f, 10.0f);
    // draw spaceship
    fill(vec4(1.0f));
    stroke(vec4(vec3(0.0f), 1.0f));
    triangle(
        cosf(0.0f), sinf(0.0f),
        cosf(PI + QUARTER_PI), sinf(PI + QUARTER_PI),
        cosf(PI - QUARTER_PI), sinf(PI - QUARTER_PI)
    );
    // draw flame
    if (throttle > 0.0f) {
        fill(vec4(1.0f, 1.0f, 0.0f, 1.0f));
        stroke(vec4(1.0f, 0.0f, 0.0f, 1.0f));
        triangle(
            cosf(PI), sinf(PI),
            cosf(PI + QUARTER_PI), sinf(PI + QUARTER_PI),
            cosf(PI - QUARTER_PI), sinf(PI - QUARTER_PI)
        );
    }
}

void destroy() {

}