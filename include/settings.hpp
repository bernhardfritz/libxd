#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "drawmode.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace xd {

typedef struct {
	glm::vec4 fillColor, strokeColor;
	int doFill, doStroke, doTexture;
	float strokeWeight;
	glm::mat4 modelMatrix;
	DrawMode rectMode;
	DrawMode ellipseMode;

} Settings;

void settings_new(Settings** out);
void settings_destroy(Settings* settings);

} // namespace xd

#endif /* SETTINGS_HPP */
