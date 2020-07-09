#include <math.h>

#include "../easy.h"

float travel = 0;

void drawTunnel() {
	travel += 0.2f;
	for (float j = 0; j < 90; j += 3.f) {
		float size = j + fmod(travel, 3.f);
		float color = j * 3.f;
		for (float i = 0; i < M_PI * 2.f; i += 0.1f) {
			set(
			    sin((travel + size) * 0.1) * 20.f + 50 - cos(i)*size,
			    cos((travel + size) * 0.07) * 20.f + 50 - sin(i)*size,
			    0,
			    color * 0.7f,
			    color
			);
		}
	}
}

int main(int argc, char *argv[]) {
	run(
	    100, // window x position
	    300, // window y position
	    100, // width in pixels
	    100, // height in pixels
	    4, // pixel size
	    drawTunnel, // draw logic
	    1000 / 50, // 50 fps
	    1 // clear to black before calling update function
	);
	return 0;
}
