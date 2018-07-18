#include <xd/renderpass.hpp>
#include <xd/xd.hpp>
#include <algorithm>

using namespace xd;

vector<RenderPass*> RenderPass::instances;

RenderPass::RenderPass(std::initializer_list<RenderPass*> renderPasses) : renderPasses(renderPasses), texture(nullptr), shaderProgram(nullptr) {
    glGenFramebuffers(1, &framebuffer);
    initFramebufferTexture();
    instances.push_back(self());
}

RenderPass::~RenderPass() {
    delete texture;
    glDeleteFramebuffers(1, &framebuffer);
    instances.erase(std::remove(instances.begin(), instances.end(), self()), instances.end());
}

RenderPass* RenderPass::self() {
    return this;
}

void RenderPass::initShaderProgram() {
    shaderProgram = new ShaderProgram();
    shaderProgram->createVertexShader(getVertexShaderCode());
    shaderProgram->createFragmentShader(getFragmentShaderCode());
    shaderProgram->link();

    createUniforms();    
}

void RenderPass::createUniforms() {
    shaderProgram->createUniform("uMVP");
    shaderProgram->createUniform("uTexture0");
    shaderProgram->createUniform("uResolution");
    shaderProgram->createUniform("uSeconds");
}

void RenderPass::updateUniforms() {
    shaderProgram->setUniform("uResolution", vec2(width * displayDensity(), height * displayDensity()));
    shaderProgram->setUniform("uSeconds", (float)glfwGetTime());
}

void RenderPass::initFramebufferTexture() {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    delete texture;
	texture = new Texture(width * displayDensity(), height * displayDensity(), GL_RGB, nullptr);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->texture, 0);
    background(vec4(vec3(0.3f), 1.0f));
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderPass::render(bool renderToScreen) {
    for (int i = 0; i < renderPasses.size(); i++) {
        renderPasses[i]->render(false);
    }
    if (shaderProgram && !renderPasses.empty()) {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        shaderProgram->bind();
        updateUniforms();
        for (int i = 0; i < renderPasses.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);
            renderPasses[i]->texture->bind();
            shaderProgram->setUniform("uTexture" + to_string(i), i);
        }
        background(vec4(vec3(0.0f), 1.0f));
        rect(0, 0, width, height);
        for (int i = 0; i < renderPasses.size(); i++) {
            renderPasses[i]->texture->unbind();
        }
        shaderProgram->unbind();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    if (renderToScreen) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        passthrough->shaderProgram->bind();
        glActiveTexture(GL_TEXTURE0);
        texture->bind();
        passthrough->shaderProgram->setUniform("uTexture0", 0);
        rect(0, 0, width, height);
        texture->unbind();
        passthrough->shaderProgram->unbind();
    }
}
