#ifndef PASSTHROUGH_HPP
#define PASSTHROUGH_HPP

#include <xd/renderpass.hpp>
#include <string>

namespace xd {

class Passthrough : virtual public RenderPass {
protected:
    virtual const std::string getVertexShaderCode();
    virtual const std::string getFragmentShaderCode();
public:
    Passthrough();
    void begin();
    void end();
};

} // namespace xd

#endif /* PASSTHROUGH_HPP */
