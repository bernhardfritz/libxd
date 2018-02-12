#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include "shape.hpp"

#define SEGMENTS 64

class Ellipse : public Shape {
public:
	Ellipse(int framebufferWidth, int framebufferHeight);
};

#endif /* ELLIPSE_HPP */
