#version 410 core

uniform vec4 uFillColor;
uniform vec4 uStrokeColor;
uniform int uDoFill;
uniform int uDoStroke;
uniform float uStrokeWeight;
uniform sampler2D uTexture;
uniform int uDoTexture;

in vec2 vUV;
in vec3 vColor;
noperspective in vec3 vDist;
out vec4 fragColor;

void main() {
	if (uDoTexture == 1) {
		fragColor = texture(uTexture, vUV);
	} else {
		float d = min(vDist[0], min(vDist[1], vDist[2]));
		d = clamp((d - (uStrokeWeight * 2.0 - 1)), 0, 2);
		float I = uDoStroke == 1 ? exp2(-2.0 * d * d) : 0.0;
		fragColor = mix(uDoFill == 1 ? uFillColor : vec4(0.0), uStrokeColor, I);
	}
}
