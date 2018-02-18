#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

namespace xd {

GLuint createVertexShader(const GLchar** string);
GLuint createGeometryShader(const GLchar** string);
GLuint createFragmentShader(const GLchar** string);
GLuint createProgram(int count, ...);
void destroyProgram(GLuint program);
GLint createUniform(GLuint program, const GLchar* name);

} // namespace xd

#endif /* SHADER_HPP */
