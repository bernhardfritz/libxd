#include "blurpass.hpp"
#include <glm/vec2.hpp>

using namespace xd;
using namespace std;
using namespace glm;

BlurPass::BlurPass(initializer_list<RenderPass*> renderPasses) : RenderPass(renderPasses), direction(vec2(1.0, 0.0)) {
    initShaderProgram();
}

void BlurPass::setDirection(vec2 direction) {
    this->direction = direction;
}

const string BlurPass::getFragmentShaderCode() {
    return 
        "#version 330 core\n"
        "\n"
        "uniform sampler2D uTexture0;\n"
        "uniform vec2 uResolution;\n"
        "uniform vec2 uSeconds;\n"
        "uniform vec2 uDirection;\n"
        "\n"
        "in vec2 vUV;\n"
        "out vec4 fragColor;\n"
        "\n"
        "void main() {\n"
        "    vec4 color = vec4(0.0);\n"
        "    vec2 off1 = vec2(1.3846153846) * uDirection;\n"
        "    vec2 off2 = vec2(3.2307692308) * uDirection;\n"
        "    color += texture(uTexture0, vUV) * 0.2270270270;\n"
        "    color += texture(uTexture0, vUV + (off1 / uResolution)) * 0.3162162162;\n"
        "    color += texture(uTexture0, vUV - (off1 / uResolution)) * 0.3162162162;\n"
        "    color += texture(uTexture0, vUV + (off2 / uResolution)) * 0.0702702703;\n"
        "    color += texture(uTexture0, vUV - (off2 / uResolution)) * 0.0702702703;\n"
        "    fragColor = color;\n"
        "}\n"
    ;
}

void BlurPass::createUniforms() {
    RenderPass::createUniforms();
    shaderProgram->createUniform("uDirection");
}

void BlurPass::updateUniforms() {
    RenderPass::updateUniforms();
    shaderProgram->setUniform("uDirection", direction);
}
