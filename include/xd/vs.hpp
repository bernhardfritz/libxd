#ifndef VS_HPP
#define VS_HPP

#include <string>

const std::string vs =
"#version 330 core\n"
"\n"
"uniform mat4 uMVP;\n"
"\n"
"layout(location = 0) in vec2 aPosition;\n"
"layout(location = 1) in vec2 aUV;\n"
"layout(location = 2) in vec3 aColor;\n"
"layout(location = 3) in float aExcludeEdge;\n"
"\n"
"out Vertex {\n"
"	vec2 uv;\n"
"	vec3 color;\n"
"	float excludeEdge;\n"
"} vertex;\n"
"\n"
"void main() {\n"
"	vertex.uv = aUV;\n"
"	vertex.color = aColor;\n"
"	vertex.excludeEdge = aExcludeEdge;\n"
"	gl_Position = uMVP * vec4(aPosition, 0.0, 1.0);\n"
"}\n"
;

#endif /* VS_HPP */
