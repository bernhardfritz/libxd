#include <xd/xd.hpp>

using namespace xd;

/*
  The 2D Water algorithm can be found under:
  https://web.archive.org/web/20160418004149/http://freespace.virgin.net/hugo.elias/graphics/x_water.htm
*/

float damping = 0.99999;

const int cols = 640;
const int rows = 480;

int buffer1[cols][rows];
int buffer2[cols][rows];

int maxCounter = 3;
int counter = maxCounter;

// the bigger the value, the stronger/bigger/longer-lasting the ripple
int rippleValue = 1000;

void onMouseMoved(float x, float y) {
	// we create a new wave only every 3rd event fired
	if(counter == maxCounter){
		buffer1[clamp(int(x), 1, cols - 2)][clamp(int(y), 1, rows - 2)] = rippleValue;
		counter = 0;
	}
	counter ++;
}

void setup() {
    size(cols, rows);
	mouseMoved(onMouseMoved);
}

void draw() {
	background(vec4(0));
	stroke(vec4(255));
	for (int x = 1; x < cols - 1; x++) {
		for (int y = 1; y < rows - 1; y++) {
			buffer2[x][y] = 
				(buffer1[x-1][y] +
				buffer1[x+1][y] +
				buffer1[x][y-1] +
				buffer1[x][y+1]) / 2 - buffer2[x][y];

			//buffer2[x][y] = buffer2[x][y] * damping;
			buffer2[x][y] -= buffer2[x][y] >> 2;
			// for performance reasons we only create a point if its value isn't 0 (all white points)
			if(buffer2[x][y] != 0) {	
				point(x, y);
			}
		}
	}

	std::swap(buffer1, buffer2);
}

void destroy() {

}

