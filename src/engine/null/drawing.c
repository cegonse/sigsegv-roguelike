#include <stdlib.h>
#include <engine/drawing.h>

void Drawing_ClearScreen(struct rgba8888_color color) {
}

struct texture2d *Drawing_LoadTexture(struct resource_pack_texture *pack_texture) {
  struct texture2d *texture = calloc(1, sizeof(struct texture2d));

  texture->color_format = kTEXTURE_COLOR_FORMAT_RGBA32;
  texture->width = pack_texture->width;
  texture->height = pack_texture->height;
  texture->native_handle = NULL;

  return texture;
}

void Drawing_DrawTexture(char *id, int x, int y) {
}
