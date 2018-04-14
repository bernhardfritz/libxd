#version 330 core

uniform mat4 uMVP;

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aUV;

out vec2 vUV;

void main() {
    vUV = aUV;
    gl_Position = uMVP * vec4(aPosition, 0.0, 1.0);
}