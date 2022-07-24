#pragma once
#include <stdint.h>

typedef enum {
  kTEXTURE_COLOR_FORMAT_RGBA32
} TextureColorFormat;

struct rgba8888_color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

struct texture2d {
  void *nativeHandle;
  TextureColorFormat color_format;
  unsigned int width;
  unsigned int height;
};

void Drawing_ClearScreen(struct rgba8888_color color);
