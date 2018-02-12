#include "ellipse.hpp"
#include "utils.hpp"
#include "constants.hpp"
#include <glm/trigonometric.hpp>

using namespace std;
using namespace glm;

Ellipse::Ellipse(int framebufferWidth, int framebufferHeight) {
	Vertex vertices_arr[SEGMENTS + 1];

	unsigned short indices_arr[SEGMENTS * 3];

	for (int i = 0; i < SEGMENTS; i++) {
		Vertex* vertex = vertices_arr + i;
		float a = i * TWO_PI / SEGMENTS;
		float c = cosf(a);
		float s = sinf(a);
		vertex->xy = vec2(c * framebufferWidth / 2.0f, s * framebufferHeight / 2.0f);
		vertex->uv = vec2(c, s);
		vertex->rgb = vec3(0.0f, 0.0f, 0.0f);
		vertex->excludeEdge = 1.0f;
		indices_arr[i * 3 + 0] = (i + 0) % SEGMENTS;
		indices_arr[i * 3 + 1] = (i + 1) % SEGMENTS;
		indices_arr[i * 3 + 2] = SEGMENTS;
	}

	Vertex* vertex = vertices_arr + SEGMENTS;
	vertex->xy = vec2(0.0f, 0.0f);
	vertex->uv = vec2(0.5f, 0.5f);
	vertex->rgb = vec3(0.0f, 0.0f, 0.0f);
	vertex->excludeEdge = 0.0f;

	vector<Vertex> vertices(vertices_arr, vertices_arr + sizeof(vertices_arr) / sizeof(vertices_arr[0]));
	vector<unsigned short> indices(indices_arr, indices_arr + sizeof(indices_arr) / sizeof(indices_arr[0]));

	init(vertices, indices);
}
