#include <xd/shader.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

namespace xd {

void validateShader(GLuint shader) {
	GLint compile_status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
	if (compile_status == GL_FALSE) {
		GLint log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
		char* log_buffer = (char*) malloc(log_length * sizeof(char));
		glGetShaderInfoLog(shader, log_length * sizeof(char), &log_length, log_buffer);
		fprintf(stderr, "%s", log_buffer);
		free(log_buffer);
		exit(EXIT_FAILURE);
	}
}

GLuint createShader(GLenum shaderType, const GLchar** string) {
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, string, NULL);
	glCompileShader(shader);
	validateShader(shader); // TODO remove from prod
	return shader;
}

GLuint createVertexShader(const GLchar** string) {
	return createShader(GL_VERTEX_SHADER, string);
}

GLuint createGeometryShader(const GLchar** string) {
	return createShader(GL_GEOMETRY_SHADER, string);
}

GLuint createFragmentShader(const GLchar** string) {
	return createShader(GL_FRAGMENT_SHADER, string);
}

GLuint createProgram(int count, ...) {
	GLuint program = glCreateProgram();
	va_list args;
	va_start(args, count);
	for (int i = 0; i < count; i++) {
		glAttachShader(program, va_arg(args, GLuint));
	}
	va_end(args);
	glLinkProgram(program);
	return program;
}

void destroyProgram(GLuint program) {
	glDeleteProgram(program);
}

GLint createUniform(GLuint program, const GLchar* name) {
	return glGetUniformLocation(program, name);
}

} // namespace xd
