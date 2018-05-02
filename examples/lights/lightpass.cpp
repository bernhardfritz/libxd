#include "lightpass.hpp"

using namespace std;

LightPass::LightPass(initializer_list<RenderPass*> renderPasses) : RenderPass(renderPasses), lights(nullptr) {
    initShaderProgram();
}

void LightPass::setLights(Light* lights) {
    this->lights = lights;
}

const string LightPass::getFragmentShaderCode() {
    return 
        "#version 330 core\n"
        "\n"
        "uniform sampler2D uTexture0;\n"
        "uniform vec2 uResolution;\n"
        "uniform float uSeconds;\n"
        "\n"
        "struct Light {\n"
        "    vec2 lightPos;\n"
        "    vec4 color;\n"
        "    float intensity;\n"
        "};\n"
        "\n"
        "uniform Light lights[3];\n"
        "\n"
        "in vec2 vUV;\n"
        "out vec4 fragColor;\n"
        "\n"
        "vec4 toGamma(vec4 color) {\n"
        "    return pow(color,vec4(1.0/2.2));\n"
        "}\n"
        "\n"
        "vec4 calculateLight(Light light) {\n"
        "    vec2 res = normalize(uResolution);\n"
        "    float dist = distance(vUV.xy * res, light.lightPos * res) / light.intensity;\n"
        "    float lightness = 1.0 / (dist * dist); // inverse square law\n"
        "    return light.color * lightness;\n"
        "}\n"
        "\n"
        "void main(void) {\n"
        "    vec4 color = calculateLight(lights[0]) +\n"
        "                calculateLight(lights[1]) + \n"
        "                calculateLight(lights[2]); \n"
        "\n"
        "    color = toGamma(color);\n"
        "\n"
        "    fragColor = texture(uTexture0, vUV) * color;\n"
        "}\n"
    ;
}

void LightPass::createUniforms() {
    RenderPass::createUniforms();
    for (int i = 0; i < 3; i++) {
        string s = to_string(i);
        shaderProgram->createUniform("lights[" + s + "].lightPos");
        shaderProgram->createUniform("lights[" + s + "].color");
        shaderProgram->createUniform("lights[" + s + "].intensity");
    }
}

void LightPass::updateUniforms() {
    RenderPass::updateUniforms();
    for (int i = 0; i < 3; i++) {
        Light* light = lights + i;
        string s = to_string(i);
        shaderProgram->setUniform("lights[" + s + "].lightPos", light->lightPos);
        shaderProgram->setUniform("lights[" + s + "].color", light->color);
        shaderProgram->setUniform("lights[" + s + "].intensity", light->intensity);
    }
}
