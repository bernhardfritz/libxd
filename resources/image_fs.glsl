#version 330 core

uniform sampler2D uTexture;
uniform vec4 uTintColor;
uniform int uDoTint;

in vec2 vUV;
out vec4 fragColor;

void main(void) {
    fragColor = texture(uTexture, vUV);
    if (uDoTint == 1) {
        float grayness = 0.299 * fragColor.r + 0.587 * fragColor.g + 0.114 * fragColor.b; // (fragColor.r + fragColor.g + fragColor.b) / 3.0;
        vec4 grayscale = vec4(grayness, grayness, grayness, 1.0);
        fragColor = fragColor.a > 0 ? grayscale * uTintColor : fragColor;
    }
}
