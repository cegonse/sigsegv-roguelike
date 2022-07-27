#include <stdlib.h>
#include <raylib/include/raylib.h>
#include <engine/drawing.h>

static Color toRaylibColor(struct rgba8888_color color) {
  return (Color){
    color.r, color.g, color.b, color.a
  };
}

void Drawing_ClearScreen(struct rgba8888_color color) {
  BeginDrawing();
  ClearBackground(toRaylibColor(color));
  EndDrawing();
}

struct texture2d *Drawing_LoadTexture(struct resource_pack_texture *pack_texture) {
  struct texture2d *texture = calloc(1, sizeof(struct texture2d));

  texture->color_format = kTEXTURE_COLOR_FORMAT_RGBA32;
  texture->width = pack_texture->width;
  texture->height = pack_texture->height;
  texture->native_handle = NULL;

  return texture;
}
