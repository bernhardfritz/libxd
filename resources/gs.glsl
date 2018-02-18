#version 330 core

uniform vec2 uWIN_SCALE;

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in Vertex {
	vec2 uv;
	vec3 color;
	float excludeEdge;
} vertex[];

out vec2 vUV;
out vec3 vColor;
noperspective out vec3 vDist;

const float MEW = 100.0; // max edge width

float cross(vec2 a, vec2 b) {
	return a.x * b.y - a.y * b.x;
}

void main() {
	vec2 v0 = uWIN_SCALE * gl_in[0].gl_Position.xy / gl_in[0].gl_Position.w;
	vec2 v1 = uWIN_SCALE * gl_in[1].gl_Position.xy / gl_in[1].gl_Position.w;
	vec2 v2 = uWIN_SCALE * gl_in[2].gl_Position.xy / gl_in[2].gl_Position.w;
	vec2 e[3];
	e[0] = v2 - v1;
	e[1] = v2 - v0;
	e[2] = v1 - v0;
	float area2 = abs(cross(e[0], e[1]));

	for (int i = 0; i < gl_in.length(); i++) {
		vUV = vertex[i].uv;
		vColor = vertex[i].color;
		vDist = vec3(0.0);
		vDist[i] = area2 / length(e[i]);
		vDist[(i + 1) % gl_in.length()] = vertex[(i + 1) % gl_in.length()].excludeEdge * MEW;
		vDist[(i + 2) % gl_in.length()] = vertex[(i + 2) % gl_in.length()].excludeEdge * MEW;
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
}
