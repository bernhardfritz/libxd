#ifndef RENDERPASS_HPP
#define RENDERPASS_HPP

#include <xd/shaderprogram.hpp>
#include <xd/texture.hpp>
#include <glad/glad.h>
#include <vector>

namespace xd {

class RenderPass {
private:
    std::vector<RenderPass*> renderPasses;
    Texture* texture;

public:
    static std::vector<RenderPass*> instances;

protected:
    GLuint framebuffer;
    ShaderProgram* shaderProgram;

    RenderPass(std::initializer_list<RenderPass*> renderPasses);
    RenderPass() : RenderPass({}) {}
    void initShaderProgram();
    virtual const std::string getVertexShaderCode() = 0;
    virtual const std::string getFragmentShaderCode() = 0;
    virtual void createUniforms();
    virtual void updateUniforms();

public:
    ~RenderPass();
    void initFramebufferTexture();
    void render(bool renderToScreen);
    RenderPass* self();
};

} // namespace xd

#endif /* RENDERPASS_HPP */
