#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace xd {

typedef struct {
	glm::vec2 xy;
	glm::vec2 uv;
	float excludeEdge;
} Vertex;

} // namespace xd

#endif /* VERTEX_HPP */
