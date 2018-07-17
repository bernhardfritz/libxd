#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "drawmode.hpp"
#include <xd/font.hpp>
#include <xd/opensans.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace xd {

class Settings {
public:
    glm::vec4 fillColor, strokeColor, tintColor;
	int doFill, doStroke, doTint;
	float strokeWeight;
	glm::mat4 modelMatrix;
	DrawMode rectMode, ellipseMode, imageMode;
    Font* font;
    float textSize;

    Settings()
        : fillColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
        , strokeColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
        , tintColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
        , doFill(1)
        , doStroke(1)
        , doTint(0)
        , strokeWeight(1.0f)
        , modelMatrix(glm::mat4(1.0f))
        , rectMode(CORNER)
        , ellipseMode(CENTER)
        , imageMode(CORNER)
        , font(&opensans)
        , textSize(12.0f) {
    }
};

} // namespace xd

#endif /* SETTINGS_HPP */
