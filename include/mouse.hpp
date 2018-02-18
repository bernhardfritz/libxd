#ifndef MOUSE_HPP
#define MOUSE_HPP

#define MOUSE_BUTTON_LEFT GLFW_MOUSE_BUTTON_LEFT
#define MOUSE_BUTTON_RIGHT GLFW_MOUSE_BUTTON_RIGHT
#define MOUSE_BUTTON_MIDDLE GLFW_MOUSE_BUTTON_MIDDLE

namespace xd {

void mouseMoved(void (*onMouseMoved)(float, float)); // onMouseMoved(x, y)
void mousePressed(void (*onMousePressed)(int));      // onMousePressed(button)
void mouseReleased(void (*onMouseReleased)(int));    // onMouseReleased(button)
void mouseWheel(void (*onMouseWheel)(float));        // onMouseWheel(delta)

} // namespace xd

#endif /* MOUSE_HPP */
