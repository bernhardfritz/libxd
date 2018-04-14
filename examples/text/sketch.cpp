#include <xd/xd.hpp>
#include <xd/opensans.hpp>
#include "indieflower.hpp"

using namespace xd;

void setup() {
    size(640, 480);
    indieflower.init();
}

void draw() {
    background(vec4(0.6f, 0.6f, 0.6f, 1.0f));
    textSize(48.0f);
    fill(vec4(1.0f, 0.0f, 0.0f, 1.0f));
    noStroke();
    text("Hello OpenSans!", 15.0f, 83.0f); // OpenSans is selected by default
    noFill();
    stroke(vec4(0.0f, 0.0f, 0.0f, 1.0f));
    strokeWeight(0.15f); // strokeWeight for fonts should be between 0.0f and 1.0f
    textFont(indieflower);
    text("Hello Indie Flower!", 15.0f, 155.0f);
    fill(vec4(0.0f, 1.0f, 0.0f, 1.0f));
    stroke(vec4(0.0f, 0.0f, 0.0f, 1.0f));
    textFont(opensans); // reset font to OpenSans manually
    text("Hello OpenSans!", 15.0f, 227.0f);
    fill(vec4(0.0f, 0.0f, 1.0f, 0.5f));
    noStroke();
    text("Semitransparent 1", 15.0f, 299.0f);
    noFill();
    stroke(vec4(0.0f, 0.0f, 1.0f, 0.5f));
    text("Semitransparent 2", 15.0f, 371.0f);
    fill(vec4(0.0f, 0.0f, 1.0f, 0.5f));
    stroke(vec4(0.0f, 0.0f, 0.0f, 1.0f)); // alpha of stroke color has no effect if there is a fill color set
    text("Semitransparent 3", 15.0f, 443.0f);
}

void destroy() {

}
