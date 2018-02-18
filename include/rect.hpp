#ifndef RECT_HPP
#define RECT_HPP

#include "shape.hpp"

namespace xd {

class Rect : public Shape {
public:
	Rect(int framebufferWidth, int framebufferHeight);
};

} // namespace xd

#endif /* RECT_HPP */
