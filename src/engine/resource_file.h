#pragma once
#include <stddef.h>
#include <stdint.h>

typedef enum {
  kRESOURCE_TEXTURE_FORMAT_RGBA32 = 0x00,
  kRESOURCE_TEXTURE_FORMAT_RGB24 = 0x01
} ResourceTextureFormat;

struct resource_pack_texture {
  char *id;
  uint32_t width;
  uint32_t height;
  uint8_t texture_format;
  size_t data_size;
  uint8_t *data;
};

struct resource_pack {
  int num_textures;
  struct resource_pack_texture **textures;
};

struct resource_pack *ResourceFile_FromPath(char *path);

void ResourceFile_Destroy(struct resource_pack *self);
