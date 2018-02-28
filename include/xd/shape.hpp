#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "vertex.hpp"
#include <glad/glad.h>
#include <vector>

namespace xd {

class Shape {
private:
	GLuint vao;
	GLsizei indicesCount;

public:
	~Shape();
	void init(const std::vector<Vertex>& vertices, const std::vector<unsigned short>& indices);
	void draw();
	GLuint getVao();
	GLsizei getIndicesCount();
};

} // namespace xd

#endif /* SHAPE_HPP */
