#include "pixels.hpp"
#include "xd.hpp"

using namespace std;
using namespace glm;

Pixels::Pixels() : resizeFlag(true), readFlag(true) {}

Pixels::Proxy::Proxy(Pixels& outer_, int index_) : outer(outer_), index(index_), x(index % (width * displayDensity())), y(index / (width * displayDensity())) {}

void Pixels::Proxy::operator=(vec4 color) {
	if (outer.resizeFlag) {
		outer.resizeFlag = false;
		outer.data.resize(width * displayDensity() * height * displayDensity() * 4);
	}
	outer.data[((height * displayDensity() - (y + 1)) * width * displayDensity() + x) * 4 + 0] = color.b * 255.0f;
	outer.data[((height * displayDensity() - (y + 1)) * width * displayDensity() + x) * 4 + 1] = color.g * 255.0f;
	outer.data[((height * displayDensity() - (y + 1)) * width * displayDensity() + x) * 4 + 2] = color.r * 255.0f;
	outer.data[((height * displayDensity() - (y + 1)) * width * displayDensity() + x) * 4 + 3] = color.a * 255.0f;
	push();
	stroke(color);
	bool tmp = outer.readFlag;
	point(x / displayDensity(), y / displayDensity());
	outer.readFlag = tmp;
	pop();
}

Pixels::Proxy::operator vec4 const &() {
	if (outer.resizeFlag) {
		outer.resizeFlag = false;
		outer.data.resize(width * displayDensity() * height * displayDensity() * 4);
	}
	if (outer.readFlag) {
		outer.readFlag = false;
		glReadPixels(0, 0, width * displayDensity(), height * displayDensity(), GL_BGRA, GL_UNSIGNED_BYTE, &outer.data[0]);
	}
	static vec4 color;
	color = vec4(
		outer.data[((height * displayDensity() - (y + 1)) * width * displayDensity() + x) * 4 + 2] / 255.0f,
		outer.data[((height * displayDensity() - (y + 1)) * width * displayDensity() + x) * 4 + 1] / 255.0f,
		outer.data[((height * displayDensity() - (y + 1)) * width * displayDensity() + x) * 4 + 0] / 255.0f,
		outer.data[((height * displayDensity() - (y + 1)) * width * displayDensity() + x) * 4 + 3] / 255.0f
	);
	return color;
}

Pixels::Proxy Pixels::operator[](int index) {
	return Proxy(*this, index);
}

void Pixels::lazyResize() {
	resizeFlag = true;
}

void Pixels::lazyRead() {
	readFlag = true;
}
