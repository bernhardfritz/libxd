#include <xd/xd.hpp>
#include "brightpass.hpp"
#include "blurpass.hpp"
#include "bloompass.hpp"

using namespace xd;

BrightPass* brightpass;
BlurPass* horizontalBlurPass;
BlurPass* verticalBlurPass;
BloomPass* bloompass;

void setup() {
    size(640, 480);

    brightpass = new BrightPass({passthrough});
    horizontalBlurPass = new BlurPass({brightpass});
    horizontalBlurPass->setDirection(vec2(1.0, 0.0));
    verticalBlurPass = new BlurPass({horizontalBlurPass});
    verticalBlurPass->setDirection(vec2(0.0, 1.0));
    bloompass = new BloomPass({passthrough, verticalBlurPass});
    renderPass(bloompass);
}

void draw() {
    background(vec4(vec3(0.0f), 1.0f));
    noStroke();
    for (int y = 0; y < height; y += 10) {
        for (int x = 0; x < width; x += 10) {
            vec2 v = vec2((float)x / width, (float)y / height);
            fill(vec4(v.x, v.y, 1.0 - length(v), 1.0f));
            ellipse(x + 5.0f, y + 5.0f, 10.0f, 10.0f);
        }
    }
}

void destroy() {
    delete brightpass;
    delete horizontalBlurPass;
    delete verticalBlurPass;
    delete bloompass;
}
