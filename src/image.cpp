#include "image.hpp"
#include <glm/vec4.hpp>

using namespace std;
using namespace glm;

Image::Image() : pixels(*this) {}

Image::~Image() {
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &texture);
}

Image::ImagePixels::ImagePixels(Image& image_) : image(image_), downloadFlag(true), uploadFlag(false) {}

Image::ImagePixels::ImageProxy::ImageProxy(ImagePixels& outer_, int index_) : outer(outer_), index(index_), x(index % outer.image.width), y(index / outer.image.width) {}

void Image::ImagePixels::ImageProxy::operator=(vec4 color) {
	if (outer.downloadFlag) {
		outer.downloadFlag = false;
		outer.data.resize(outer.image.width * outer.image.height * 4);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA, GL_UNSIGNED_BYTE, &outer.data[0]);
	}
	outer.data[((outer.image.height - (y + 1)) * outer.image.width + x) * 4 + 0] = color.b * 255.0f;
	outer.data[((outer.image.height - (y + 1)) * outer.image.width + x) * 4 + 1] = color.g * 255.0f;
	outer.data[((outer.image.height - (y + 1)) * outer.image.width + x) * 4 + 2] = color.r * 255.0f;
	outer.data[((outer.image.height - (y + 1)) * outer.image.width + x) * 4 + 3] = color.a * 255.0f;
	outer.uploadFlag = true;
}

Image::ImagePixels::ImageProxy::operator vec4 const &() {
	if (outer.downloadFlag) {
		outer.downloadFlag = false;
		outer.data.resize(outer.image.width * outer.image.height * 4);
		glBindTexture(GL_TEXTURE_2D, outer.image.texture);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA, GL_UNSIGNED_BYTE, &outer.data[0]);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	static vec4 color;
	color = vec4(
		outer.data[((outer.image.height - (y + 1)) * outer.image.width + x) * 4 + 2] / 255.0f,
		outer.data[((outer.image.height - (y + 1)) * outer.image.width + x) * 4 + 1] / 255.0f,
		outer.data[((outer.image.height - (y + 1)) * outer.image.width + x) * 4 + 0] / 255.0f,
		outer.data[((outer.image.height - (y + 1)) * outer.image.width + x) * 4 + 3] / 255.0f
	);
	return color;
}

Image::ImagePixels::ImageProxy Image::ImagePixels::operator[](int index) {
	return ImageProxy(*this, index);
}

void Image::ImagePixels::uploadIfNecessary() {
	if (uploadFlag) {
		uploadFlag = false;
		glBindTexture(GL_TEXTURE_2D, image.texture);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image.width, image.height, GL_BGRA, GL_UNSIGNED_BYTE, &data[0]);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
