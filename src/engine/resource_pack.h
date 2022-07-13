#pragma once
#include <engine/list.h>
#include <engine/file.h>

#define kMAX_RESOURCE_PACK_NAME_LENGTH    128
#define kMAX_RESOURCES                    128

struct resource {
  char id[kMAX_RESOURCE_PACK_NAME_LENGTH];
  char path[kMAX_FILE_PATH];
};

struct resource_pack {
  char id[kMAX_RESOURCE_PACK_NAME_LENGTH];
  struct resource textures[kMAX_RESOURCES];
  int num_textures;
};

void ResourcePack_Init(void);

void ResourcePack_Destroy(void);

void ResourcePack_Load(char *id);

void ResourcePack_Unload(char *id);

List *ResourcePack_AllActive(void);
