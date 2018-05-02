#version 330 core

uniform sampler2D uTexture;

in vec2 vUV;
out vec4 fragColor;

void main(void) {
    fragColor = texture(uTexture, vUV);
}
