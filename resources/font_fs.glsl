#version 330 core

#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D uTexture;
uniform vec4 uFillColor;
uniform vec4 uStrokeColor;
uniform int uDoFill;
uniform int uDoStroke;
uniform float uStrokeWeight;

in vec2 vUV;
out vec4 fragColor;

       vec3 glyph_color    = uFillColor.rgb;
const float glyph_center   = 0.50;
       vec3 outline_color  = uStrokeColor.rgb;
float outline_center = 0.5 + clamp(uStrokeWeight, 0.0, 1.0);
       vec3 glow_color     = vec3(0.0,0.0,0.0);
const float glow_center    = 1.25;

void main(void) {
    vec4  color = texture(uTexture, vUV);
    float dist  = color.r;
    float width = fwidth(dist);
    float alpha = smoothstep(glyph_center - width, glyph_center + width, dist);

    if (uDoFill == 1) {
        if (uDoStroke == 1) {
            float mu = smoothstep(outline_center - width, outline_center + width, dist);
            vec3 rgb = mix(outline_color, glyph_color, mu);
            fragColor = vec4(rgb, max(alpha, mu));
        } else {
            fragColor = vec4(glyph_color, alpha);
        }
        fragColor.a = min(fragColor.a, uFillColor.a);
    } else {
        if (uDoStroke == 1) {
            float mu = smoothstep(outline_center - width, outline_center + width, dist);
            fragColor = mix(vec4(0.0), uStrokeColor, clamp(alpha - mu, 0.0, 1.0));
        } else {
            fragColor = vec4(0.0);
        }
    }

    // Glow
    // vec3 rgb = mix(glow_color, glyph_color, alpha);
    // float mu = smoothstep(glyph_center, glow_center, sqrt(dist));
    // fragColor = vec4(rgb, max(alpha, mu));

    // Glow + outline
    // vec3 rgb = mix(glow_color, glyph_color, alpha);
    // float mu = smoothstep(glyph_center, glow_center, sqrt(dist));
    // color = vec4(rgb, max(alpha, mu));
    // float beta = smoothstep(outline_center - width, outline_center + width, dist);
    // rgb = mix(outline_color, color.rgb, beta);
    // fragColor = vec4(rgb, max(color.a, beta));
}
