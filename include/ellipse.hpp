#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include "shape.hpp"

namespace xd {

class Ellipse : public Shape {
public:
	Ellipse(int framebufferWidth, int framebufferHeight);
};

} // namespace xd

#endif /* ELLIPSE_HPP */
