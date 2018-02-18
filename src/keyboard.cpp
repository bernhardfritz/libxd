#include "keyboard.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

namespace xd {

static void (*onKeyPressed_)(int) = 0;
static void (*onKeyReleased_)(int) = 0;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (onKeyPressed_) {
            (*onKeyPressed_)(key);
        }
    } else if (action == GLFW_RELEASE) {
        if (onKeyReleased_) {
            (*onKeyReleased_)(key);
        }
    }
}

void keyPressed(void (*onKeyPressed)(int)) { // onKeyPressed(key)
    onKeyPressed_ = onKeyPressed;
    glfwSetKeyCallback(glfwGetCurrentContext(), key_callback);
}

void keyReleased(void (*onKeyReleased)(int)) { // onKeyReleased(key)
    onKeyReleased_ = onKeyReleased;
    glfwSetKeyCallback(glfwGetCurrentContext(), key_callback);
}

} // namespace xd
