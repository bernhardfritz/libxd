#include <xd/passthrough.hpp>

using namespace std;

namespace xd {

Passthrough::Passthrough() : RenderPass() {
    initShaderProgram();
}

const string Passthrough::getVertexShaderCode() {
    return 
        "#version 330 core\n"
        "\n"
        "uniform mat4 uMVP;\n"
        "\n"
        "layout(location = 0) in vec2 aPosition;\n"
        "layout(location = 1) in vec2 aUV;\n"
        "\n"
        "out vec2 vUV;\n"
        "\n"
        "void main() {\n"
        "    vUV = aUV;\n"
        "    gl_Position = uMVP * vec4(aPosition, 0.0, 1.0);\n"
        "}\n"
    ;
}

const string Passthrough::getFragmentShaderCode() {
    return
        "#version 330 core\n"
        "\n"
        "uniform sampler2D uTexture0;\n"
        "uniform vec2 uResolution;\n"
        "uniform float uSeconds;\n"
        "\n"
        "in vec2 vUV;\n"
        "out vec4 fragColor;\n"
        "\n"
        "void main(void) {\n"
        "    fragColor = texture(uTexture0, vUV);\n"
        "}\n"
    ;
}

void Passthrough::begin() {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
}

void Passthrough::end() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} // namespace xd
