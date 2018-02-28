#include <xd/settings.hpp>
#include <xd/utils.hpp>

using namespace glm;

namespace xd {

void settings_new(Settings** out) {
	Settings* settings = (Settings*) malloc(sizeof(Settings));
	settings->fillColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	settings->strokeColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	settings->doFill = 1;
	settings->doStroke = 1;
	settings->strokeWeight = 1.0f;
	settings->modelMatrix = mat4(1.0f);
	settings->rectMode = CORNER;
	settings->ellipseMode = CENTER;
	*out = settings;
}

void settings_destroy(Settings* settings) {
	free(settings);
}

} // namespace xd
