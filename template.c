#include "./easy.h"

void draw() {
	// x, y, r, g, b
	set(0, 0, 255, 0, 0);
	set(1, 1, 100, 200, 250);
}

int main(int argc, char *argv[]) {
	// x, y, width, height, pixel size, draw func, delay, clear between updates
	run(100, 100, 2, 2, 10, draw, 5000, 0);
	return 0;
}
