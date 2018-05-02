#include <xd/shape.hpp>

using namespace std;

namespace xd {

Shape::~Shape() {
	glDeleteVertexArrays(1, &vao);
}

void Shape::init(const vector<Vertex>& vertices, const vector<unsigned short>& indices) {
	indicesCount = indices.size();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

	GLuint aPosition = 0;
	glEnableVertexAttribArray(aPosition);
	glVertexAttribPointer(
		aPosition,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(float) * 5,
		(void*) 0
	);

	GLuint aUV = 1;
	glEnableVertexAttribArray(aUV);
	glVertexAttribPointer(
		aUV,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(float) * 5,
		(void*) (sizeof(float) * 2)
	);

	GLuint aExcludeEdge = 2;
	glEnableVertexAttribArray(aExcludeEdge);
	glVertexAttribPointer(
		aExcludeEdge,
		1,
		GL_FLOAT,
		GL_FALSE,
		sizeof(float) * 5,
		(void*) (sizeof(float) * 4)
	);

	glBindVertexArray(0);

	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Shape::draw() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_CULL_FACE);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_SHORT, (void*) 0);
}

GLuint Shape::getVao() {
	return vao;
}

GLsizei Shape::getIndicesCount() {
	return indicesCount;
}

} // namespace xd
