#ifndef LIGHTPASS_HPP
#define LIGHTPASS_HPP

#include <xd/passthrough.hpp>

typedef struct {
	glm::vec2 lightPos;
	glm::vec4 color;
	float intensity;
} Light;

class LightPass : public xd::Passthrough {
private:
    Light* lights;
public:
    LightPass(std::initializer_list<RenderPass*> renderPasses);
    void setLights(Light* lights);
protected:
    virtual const std::string getFragmentShaderCode();
    virtual void createUniforms();
    virtual void updateUniforms();
};

#endif
