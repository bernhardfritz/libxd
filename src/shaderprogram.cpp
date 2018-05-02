#include <xd/shaderprogram.hpp>

using namespace std;
using namespace glm;

namespace xd {

ShaderProgram* ShaderProgram::boundShaderProgram = nullptr;

ShaderProgram::ShaderProgram() {
    program = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    unbind();
    if (program != 0) {
        glDeleteProgram(program);
    }
}

ShaderProgram* ShaderProgram::getBoundShaderProgram() {
    return boundShaderProgram;
}

void validateShader(GLuint& shader) {
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

GLuint ShaderProgram::createShader(GLenum shaderType, const string& shaderCode) {
    GLuint shader = glCreateShader(shaderType);
    const GLchar* c_str = shaderCode.c_str();
    glShaderSource(shader, 1, &c_str, NULL);
    glCompileShader(shader);
    validateShader(shader);
    glAttachShader(program, shader);
    return shader;
}

void ShaderProgram::createVertexShader(const string& shaderCode) {
    vertexShader = createShader(GL_VERTEX_SHADER, shaderCode);
}

void ShaderProgram::createGeometryShader(const string& shaderCode) {
    createShader(GL_GEOMETRY_SHADER, shaderCode);
}

void ShaderProgram::createFragmentShader(const string& shaderCode) {
    createShader(GL_FRAGMENT_SHADER, shaderCode);
}

void ShaderProgram::createUniform(const string& uniformName) {
    uniforms[uniformName] = glGetUniformLocation(program, uniformName.c_str());
}

void ShaderProgram::setUniform(const string& uniformName, const int& i) {
    glUniform1iv(uniforms[uniformName], 1, (const GLint*) &i);
}

void ShaderProgram::setUniform(const string& uniformName, const float& f) {
    glUniform1fv(uniforms[uniformName], 1, (const GLfloat*) &f);
}

void ShaderProgram::setUniform(const string& uniformName, const vec2& v) {
    glUniform2fv(uniforms[uniformName], 1, (const GLfloat*) &v[0]);
}

void ShaderProgram::setUniform(const string& uniformName, const vec3& v) {
    glUniform3fv(uniforms[uniformName], 1, (const GLfloat*) &v[0]);
}

void ShaderProgram::setUniform(const string& uniformName, const vec4& v) {
    glUniform4fv(uniforms[uniformName], 1, (const GLfloat*) &v[0]);
}

void ShaderProgram::setUniform(const string& uniformName, const mat4x4& m) {
    glUniformMatrix4fv(uniforms[uniformName], 1, GL_FALSE, (const GLfloat*) &m[0]);
}

void ShaderProgram::link() {
    glLinkProgram(program);

    if (vertexShader != 0) {
        glDetachShader(program, vertexShader);
    }

    if (geometryShader != 0) {
        glDetachShader(program, geometryShader);
    }

    if (fragmentShader != 0) {
        glDetachShader(program, fragmentShader);
    }
}

void ShaderProgram::bind() {
    glUseProgram(program);
    boundShaderProgram = this;
}

void ShaderProgram::unbind() {
    glUseProgram(0);
    boundShaderProgram = nullptr;
}

} // namespace xd
