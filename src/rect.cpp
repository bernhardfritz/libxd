#include "rect.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

using namespace std;
using namespace glm;

Rect::Rect(int framebufferWidth, int framebufferHeight) {
	Vertex vertices_arr[] = {
		{ vec2(0.0f, 0.0f), vec2(0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), 1.0f },
		{ vec2(0.0f, framebufferHeight), vec2(0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), 0.0f },
		{ vec2(framebufferWidth, 0.0f), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), 0.0f },
		{ vec2(framebufferWidth, framebufferHeight), vec2(1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f), 1.0f }
	};
	vector<Vertex> vertices(vertices_arr, vertices_arr + sizeof(vertices_arr) / sizeof(vertices_arr[0]));

	unsigned short indices_arr[] = {
		0, 1, 2,
		2, 1, 3
	};
	vector<unsigned short> indices(indices_arr, indices_arr + sizeof(indices_arr) / sizeof(indices_arr[0]));

	init(vertices, indices);
}
