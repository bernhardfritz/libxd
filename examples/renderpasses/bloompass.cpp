#include "bloompass.hpp"

using namespace xd;
using namespace std;

BloomPass::BloomPass(initializer_list<RenderPass*> renderPasses) : RenderPass(renderPasses) {
    initShaderProgram();
}

const string BloomPass::getFragmentShaderCode() {
    return
        "#version 330 core\n"
        "\n"
        "uniform sampler2D uTexture0;\n"
        "uniform sampler2D uTexture1;\n"
        "uniform vec2 uResolution;\n"
        "uniform float uSeconds;\n"
        "\n"
        "in vec2 vUV;\n"
        "out vec4 fragColor;\n"
        "\n"
        "void main(void) {\n"
        "    vec4 passthroughColor = texture(uTexture0, vUV);\n"
        "    vec4 blurredHighlightColor = texture(uTexture1, vUV);\n"
        "    vec4 color = passthroughColor + blurredHighlightColor;\n"
        "    fragColor = vec4(pow(color.rgb, vec3(1.0 / 2.2)), color.a);\n"
        "}\n"
    ;
}

void BloomPass::createUniforms() {
    RenderPass::createUniforms();
    shaderProgram->createUniform("uTexture1");
}
