#ifndef BLURPASS_HPP
#define BLURPASS_HPP

#include <xd/passthrough.hpp>

class BlurPass : public xd::Passthrough {
public:
    glm::vec2 direction;
    BlurPass(std::initializer_list<RenderPass*> renderPasses);
    void setDirection(glm::vec2 direction);
protected:
    virtual const std::string getFragmentShaderCode();
    virtual void createUniforms();
    virtual void updateUniforms();
};

#endif /* BLURPASS_HPP */
