#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

GLuint createVertexShader(const GLchar** string);
GLuint createGeometryShader(const GLchar** string);
GLuint createFragmentShader(const GLchar** string);
GLuint createProgram(int count, ...);
void destroyProgram(GLuint program);
GLint createUniform(GLuint program, const GLchar* name);

#endif /* SHADER_HPP */
