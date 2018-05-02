#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>

class Texture {
public:
    GLuint texture;

    Texture(GLsizei width, GLsizei height, GLenum format, const GLvoid* data);
    ~Texture();

    void bind();
    void unbind();
};

#endif /* TEXTURE_HPP */
