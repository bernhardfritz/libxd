#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

namespace xd {

class Triangle : public Shape {
public:
	Triangle(int framebufferWidth, int framebufferHeight);
};

} // namespace xd

#endif /* TRIANGLE_HPP */
