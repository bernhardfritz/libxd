#include <xd/ellipse.hpp>
#include <xd/constants.hpp>
#include <glm/trigonometric.hpp>

#define ELLIPSE_SEGMENTS 64

using namespace std;
using namespace glm;

namespace xd {

Ellipse::Ellipse(int framebufferWidth, int framebufferHeight) {
	Vertex vertices_arr[ELLIPSE_SEGMENTS + 1];

	unsigned short indices_arr[ELLIPSE_SEGMENTS * 3];

	for (int i = 0; i < ELLIPSE_SEGMENTS; i++) {
		Vertex* vertex = vertices_arr + i;
		float a = i * TWO_PI / ELLIPSE_SEGMENTS;
		float c = cosf(a);
		float s = sinf(a);
		vertex->xy = vec2(c * framebufferWidth / 2.0f, s * framebufferHeight / 2.0f);
		vertex->uv = vec2(c, s);
		vertex->excludeEdge = 1.0f;
		indices_arr[i * 3 + 0] = (i + 0) % ELLIPSE_SEGMENTS;
		indices_arr[i * 3 + 1] = (i + 1) % ELLIPSE_SEGMENTS;
		indices_arr[i * 3 + 2] = ELLIPSE_SEGMENTS;
	}

	Vertex* vertex = vertices_arr + ELLIPSE_SEGMENTS;
	vertex->xy = vec2(0.0f, 0.0f);
	vertex->uv = vec2(0.5f, 0.5f);
	vertex->excludeEdge = 0.0f;

	vector<Vertex> vertices(vertices_arr, vertices_arr + sizeof(vertices_arr) / sizeof(vertices_arr[0]));
	vector<unsigned short> indices(indices_arr, indices_arr + sizeof(indices_arr) / sizeof(indices_arr[0]));

	init(vertices, indices);
}

}
