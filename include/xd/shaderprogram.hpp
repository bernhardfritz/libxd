#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <map>
#include <string>

namespace xd {

class ShaderProgram {
private:
    static ShaderProgram* boundShaderProgram;

    GLuint program;
    GLuint vertexShader;
    GLuint geometryShader;
    GLuint fragmentShader;
    std::map<std::string, GLint> uniforms;

    GLuint createShader(GLenum shaderType, const std::string& shaderCode);

public:
    ShaderProgram();
    ~ShaderProgram();
    static ShaderProgram* getBoundShaderProgram();
    void createVertexShader(const std::string& shaderCode);
    void createGeometryShader(const std::string& shaderCode);
    void createFragmentShader(const std::string& shaderCode);
    void createUniform(const std::string& uniformName);
    void setUniform(const std::string& uniformName, const int& i);
    void setUniform(const std::string& uniformName, const float& f);
    void setUniform(const std::string& uniformName, const glm::vec2& v);
    void setUniform(const std::string& uniformName, const glm::vec3& v);
    void setUniform(const std::string& uniformName, const glm::vec4& v);
    void setUniform(const std::string& uniformName, const glm::mat4x4& m);
    void link();
    void bind();
    void unbind();
};

} // namespace xd

#endif /* SHADERPROGRAM_HPP */
