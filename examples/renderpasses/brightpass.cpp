#include "brightpass.hpp"

using namespace xd;
using namespace std;

BrightPass::BrightPass(initializer_list<RenderPass*> renderPasses) : RenderPass(renderPasses) {
    initShaderProgram();
}

const string BrightPass::getFragmentShaderCode() {
    return
        "#version 330 core\n"
        "\n"
        "uniform sampler2D uTexture0;\n"
        "uniform vec2 uResolution;\n"
        "uniform float uSeconds;\n"
        "\n"
        "in vec2 vUV;\n"
        "out vec4 fragColor;\n"
        "const float threshold = 0.3;\n"
        "\n"
        "void main(void) {\n"
        "    vec4 color = texture(uTexture0, vUV);\n"
        "    float luminance = dot(vec3(0.2126, 0.7152, 0.0722), color.rgb);\n"
        "    luminance = max(0.0, luminance - threshold);\n"
        "    color.xyz *= sign(luminance);\n"
        "    fragColor = color;\n"
        "}\n"
    ;
}
