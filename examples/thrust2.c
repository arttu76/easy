#include <stdlib.h>

#include "../easy.h"

typedef uint8_t SYMBOL;

const uint8_t bitmaps[][8] = {
	{
		0,
		0,
		0,
		0b00011000,
		0b00011000,
		0,
		0,
		0
	},
	{
		0,
		0,
		0b00011000,
		0b00111100,
		0b00111100,
		0b00011000,
		0,
		0
	},
	{
		0,
		0b00111100,
		0b01111110,
		0b01111110,
		0b01111110,
		0b01111110,
		0b00111100,
		0
	},
	{
		0b01111110,
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111111,
		0b01111110
	},
	{
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111111
	}
};

uint8_t scrollOffset = 0;

SYMBOL chars[][8] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 0, 0, 0 },
	{ 0, 0, 3, 3, 3, 3, 0, 0 },
	{ 0, 4, 4, 4, 4, 4, 4, 0 },
	{ 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 0, 0, 0, 6, 6, 0, 0, 0 },
	{ 0, 0, 0, 7, 7, 0, 0, 0 },
	{ 0, 0, 0, 8, 8, 0, 0, 0 },
	{ 0, 0, 0, 9, 9, 0, 0, 0 }
};

void scrollScreen() {
	scrollOffset++;
	if (scrollOffset & 8) {
		scrollOffset = 0;
		for (uint8_t y = 0; y < 9; y++) {
			for (uint8_t x = 0; x < 8; x++) {
				chars[y][x] = y < 8
				              ? chars[y + 1][x]
				              : rand() % 2
				              ? 0
				              : rand() % 10 + 1;
			}
		}
	}
}

SYMBOL pulseAndGetCurrentSymbol(uint8_t x, uint8_t y) {
	SYMBOL symbol = chars[y][x];

	if (symbol) {
		symbol = (symbol + 1) % 11;
		chars[y][x] = symbol ? symbol : 1;
	}

	return symbol;
}

void drawSymbol(SYMBOL symbol, uint8_t x, uint8_t y) {
	_Bool pixel;
	uint8_t yPos;

	for (uint8_t row = 0; row < 8; row++) {
		yPos = (y << 3) - scrollOffset + row;
		if (yPos < 0 || yPos > 63) {
			continue;
		}

		for (uint8_t bit = 0; bit < 8; bit++) {
			if (symbol == 0) {
				pixel = 0;
			} else if (symbol < 6) {
				pixel = ((bitmaps[symbol - 1][row] >> bit) & 1);
			} else {
				pixel = !(rand() % 5 < (symbol - 5));
			}

			set(
			    x * 8 + bit,
			    yPos,
			    0,
			    pixel * 150,
			    0
			);
		}
	}
}

void draw() {
	scrollScreen();

	for (uint8_t y = 0; y < 9; y++) {
		for (uint8_t x = 0; x < 8; x++) {
			drawSymbol(pulseAndGetCurrentSymbol(x, y), x, y);
		}
	}
}

int main(int argc, char *argv[]) {
	// x, y, width, height, pixel size, draw func, delay, clear between updates
	run(50, 100, 64, 64, 7, draw, 100, 0);
	return 0;
}
