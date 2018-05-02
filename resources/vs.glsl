#version 330 core

uniform mat4 uMVP;

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aUV;
layout(location = 2) in float aExcludeEdge;

out Vertex {
	vec2 uv;
	float excludeEdge;
} vertex;

void main() {
	vertex.uv = aUV;
	vertex.excludeEdge = aExcludeEdge;
	gl_Position = uMVP * vec4(aPosition, 0.0, 1.0);
}
