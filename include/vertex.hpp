#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

typedef struct {
	glm::vec2 xy;
	glm::vec2 uv;
	glm::vec3 rgb;
	float excludeEdge;
} Vertex;

#endif /* VERTEX_HPP */
