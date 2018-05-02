#ifndef BRIGHTPASS_HPP
#define BRIGHTPASS_HPP

#include <xd/passthrough.hpp>

class BrightPass : public xd::Passthrough {
public:
    BrightPass(std::initializer_list<RenderPass*> renderPasses);
protected:
    virtual const std::string getFragmentShaderCode();
};

#endif /* BRIGHTPASS_HPP */
