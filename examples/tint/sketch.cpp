#include <xd/xd.hpp>

using namespace xd;

Image* img;

void setup() {
	size(640, 480);
	img = loadImage("logo.png");
}

void draw() {
	background(vec4(vec3(0.3f), 1.0f));
	translate(width / 2, height / 2);
	rotate(millis() / 1000.0f);
    tint(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	image(img, 0.0f, 0.0f, 200.0f, 200.0f);
}

void destroy() {
	delete img;
}
