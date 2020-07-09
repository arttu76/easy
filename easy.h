#pragma once

#include <stdint.h>
#include <stdbool.h>

void run(
    uint16_t x,
    uint16_t y,
    uint16_t width,
    uint16_t height,
    uint16_t pixelSize,
    void (*updateFunction)(),
    uint16_t updateSpeed,
    _Bool clearBetweenUpdates
);

void set(
    uint16_t x,
    uint16_t y,
    uint8_t r,
    uint8_t g,
    uint8_t b
);
