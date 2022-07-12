#pragma once
#include <stdint.h>

struct rgba8888_color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

struct load_texture_options {
  char *resourceId;
  char *filePath;
};

struct texture2d {
  void *nativeHandle;
  unsigned int width;
  unsigned int height;
};

void Drawing_ClearScreen(struct rgba8888_color color);

void Drawing_LoadTexture(struct load_texture_options options);

void Drawing_UnloadTexture(char *id);
