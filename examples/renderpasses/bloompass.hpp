#ifndef BLOOMPASS_HPP
#define BLOOMPASS_HPP

#include <xd/passthrough.hpp>

class BloomPass : public xd::Passthrough {
public:
    BloomPass(std::initializer_list<RenderPass*> renderPasses);
protected:
    virtual const std::string getFragmentShaderCode();
    virtual void createUniforms();
};

#endif /* BLOOMPASS_HPP */
