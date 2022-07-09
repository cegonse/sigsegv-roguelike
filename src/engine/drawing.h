#pragma once
#include <stdint.h>

struct rgba8888_color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

void Drawing_ClearScreen(struct rgba8888_color color);
