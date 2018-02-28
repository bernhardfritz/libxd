#include <xd/mouse.hpp>
#include <GLFW/glfw3.h>

namespace xd {

static void (*onMouseMoved_)(float, float) = 0;
static void (*onMousePressed_)(int) = 0;
static void (*onMouseReleased_)(int) = 0;
static void (*onMouseWheel_)(float) = 0;

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    if (onMouseMoved_) {
        (*onMouseMoved_)(xpos, ypos);
    }
}

void mouseMoved(void (*onMouseMoved)(float, float)) { // onMouseMoved(float x, float y)
    onMouseMoved_ = onMouseMoved;
    glfwSetCursorPosCallback(glfwGetCurrentContext(), cursor_pos_callback);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (onMousePressed_) {
            (*onMousePressed_)(button);
        }
    } else if (action == GLFW_RELEASE) {
        if (onMouseReleased_) {
            (*onMouseReleased_)(button);
        }
    }
}

void mousePressed(void (*onMousePressed)(int)) { // onMousePressed(button)
    onMousePressed_ = onMousePressed;
    glfwSetMouseButtonCallback(glfwGetCurrentContext(), mouse_button_callback); 
}

void mouseReleased(void (*onMouseReleased)(int)) { // onMouseReleased(button)
    onMouseReleased_ = onMouseReleased;
    glfwSetMouseButtonCallback(glfwGetCurrentContext(), mouse_button_callback);
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (yoffset < 0.0 || 0.0 < yoffset) {
        if (onMouseWheel_) {
            (*onMouseWheel_)(yoffset);
        }
    }
}

void mouseWheel(void (*onMouseWheel)(float)) { // onMouseWheel(delta)
    onMouseWheel_ = onMouseWheel;
    glfwSetScrollCallback(glfwGetCurrentContext(), scroll_callback);
}

} // namespace xd
