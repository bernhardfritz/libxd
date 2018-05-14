#version 330 core

uniform mat4 uMVP;
uniform mat4 uTextureMatrix;

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aUV;

out vec2 vUV;

void main() {
    vUV = vec2(uTextureMatrix * vec4(aUV, 0.0, 1.0));
    gl_Position = uMVP * vec4(aPosition, 0.0, 1.0);
}
