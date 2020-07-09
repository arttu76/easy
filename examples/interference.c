#include <math.h>

#include "../easy.h"

#define SIZE 100

float ticks = 0;

void drawEffect() {
	ticks += 0.03f;

	float c1x = SIZE / 2.f + sin(ticks) * SIZE / 2.3f;
	float c1y = SIZE / 2.f + cos(ticks) * SIZE / 2.3f;

	float c2x = SIZE / 2.f + cos(ticks * 1.7) * SIZE / 1.9f;
	float c2y = SIZE / 2.f + sin(ticks * 0.63) * SIZE / 1.9f;

	for (uint8_t y = 0; y < SIZE; y++) {
		for (uint8_t x = 0; x < SIZE; x++) {
			_Bool c1 = fmod(sqrt(pow(c1x - x, 2.f) + pow(c1y - y, 2.f)), 12.f) > 6.f;
			_Bool c2 = fmod(sqrt(pow(c2x - x, 2.f) + pow(c2y - y, 2.f)), 12.f) > 6.f;
			uint8_t color = (c1 ^ c2) * (c1 * 80 + c2 * 170);

			set(
			    x,
			    y,
			    color,
			    color,
			    color
			);
		}
	}
}

int main(int argc, char *argv[]) {
	run(
	    100, // window x position
	    300, // window y position
	    SIZE, // width in pixels
	    SIZE, // height in pixels
	    4, // pixel size
	    drawEffect, // draw logic
	    1000 / 50, // 50 times per second
	    0 // don't needlessly clear canvas between updates
	);
	return 0;
}
