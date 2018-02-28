#include <xd/utils.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <fstream>
#include <sstream>

using namespace std;
using namespace glm;

namespace xd {

float map(float x, float in_min, float in_max, float out_min, float out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

string readFile(string filename) {
	ifstream ifs(filename.c_str());
	stringstream ss;
	ss << ifs.rdbuf();
	return ss.str();
}

Image* loadImage(const char* filename) {
	Image* img = new Image();
	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(filename, &img->width, &img->height, NULL, 4);
	glGenTextures(1, &img->texture);
	glBindTexture(GL_TEXTURE_2D, img->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return img;
}

} // namespace xd
