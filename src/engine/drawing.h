#pragma once
#include <stdint.h>
#include <engine/resource_file.h>

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
  void *native_handle;
  uint8_t *raw_data;
  TextureColorFormat color_format;
  unsigned int width;
  unsigned int height;
};

void Drawing_ClearScreen(struct rgba8888_color color);

struct texture2d *Drawing_LoadTexture(struct resource_pack_texture *pack_texture);

void Drawing_DrawTexture(char *id, int x, int y);
