#include <stdlib.h>
#include <raylib/include/raylib.h>
#include <engine/log.h>
#include <engine/texture_repository.h>
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
  Image image;
  Texture *native_texture = calloc(1, sizeof(Texture));

  texture->color_format = kTEXTURE_COLOR_FORMAT_RGBA32;
  texture->width = pack_texture->width;
  texture->height = pack_texture->height;

  image.width = texture->width;
  image.height = texture->height;
  image.mipmaps = 1;
  image.data = pack_texture->data;

  switch (pack_texture->texture_format) {
    case kRESOURCE_TEXTURE_FORMAT_RGBA32:
      image.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
      break;
    case kRESOURCE_TEXTURE_FORMAT_RGB24:
      image.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8;
      break;
    default:
      image.format = PIXELFORMAT_UNCOMPRESSED_GRAYSCALE;
      break;
  }

  *(native_texture) = LoadTextureFromImage(image);
  texture->native_handle = native_texture;

  return texture;
}

void Drawing_DrawTexture(char *id, int x, int y) {
  struct texture2d *texture = NULL;
  Texture2D native;

  texture = TextureRepository_GetById(id);
  native = (Texture2D)(*(Texture2D *)texture->native_handle);
  DrawTexture(native, x, y, RAYWHITE);
}
