#include <xd/xd.hpp>

using namespace xd;

Image* img;

void setup() {
	size(640, 480);
	img = loadImage("logo.png");
	for (int y = 0; y < img->height; y++) {
		for (int x = 0; x < img->width; x++) {
			vec4 color = img->pixels[y * img->width + x];
            vec4 newColor = color;
            if (y < img->height / 2.0f) {
                if (x < img->width / 2.0f) {
			        newColor = vec4(color.r, 0.0f, 0.0f, color.a);
                } else {
                    newColor = vec4(0.0f, color.g, 0.0f, color.a);
                }
            } else {
                if (x < img->width / 2.0f) {
                    newColor = vec4(0.0f, 0.0f, color.b, color.a);
                }
            }
            img->pixels[y * img->width + x] = newColor;
		}
	}
}

void draw() {
	background(vec4(vec3(0.3f), 1.0f));
	translate(width / 2, height / 2);
	rotate(millis() / 1000.0f);
	image(img, 0.0f, 0.0f, 200.0f, 200.0f);
}

void destroy() {
	delete img;
}
