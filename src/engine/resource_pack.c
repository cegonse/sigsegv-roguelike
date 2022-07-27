#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <engine/file.h>
#include <engine/platform.h>
#include <engine/hashmap.h>
#include <engine/texture_repository.h>
#include <engine/drawing.h>
#include <engine/resource_file.h>
#include <engine/resource_pack.h>

static Hashmap *active_resource_packs;

void ResourcePack_Init(void) {
  active_resource_packs = Hashmap_Create();
}

static void unloadActivePacks(Hashmap *self, void *user, char *key, void *value) {
  ResourcePack_Unload(key);
}

void ResourcePack_Destroy(void) {
  Hashmap_Entries(active_resource_packs, NULL, unloadActivePacks);
  Hashmap_Destroy(active_resource_packs);
}

static void buildPath(char *id, char *path) {
  sprintf(path, "%s/%s.pack", Platform_DataPath(), id);
}

static void loadTextures(struct resource_pack *pack) {
  for (int i=0; i<pack->num_textures; ++i) {
    TextureRepository_Add(
      pack->textures[i]->id,
      Drawing_LoadTexture(pack->textures[i])
    );
  }
}

void ResourcePack_Load(char *id) {
  struct resource_pack *resource_pack;
  char path[kMAX_FILE_PATH];

  buildPath(id, path);
  resource_pack = ResourceFile_FromPath(path);

  loadTextures(resource_pack);

  Hashmap_Add(active_resource_packs, id, resource_pack);
}

void ResourcePack_Unload(char *id) {
  struct resource_pack *resource_pack;

  resource_pack = Hashmap_Get(active_resource_packs, id);
  for (int i=0; i<resource_pack->num_textures; ++i) {
    TextureRepository_Remove(resource_pack->textures[i]->id);
  }

  Hashmap_Remove(active_resource_packs, id);
}

bool ResourcePack_IsActive(char *id) {
  return Hashmap_Get(active_resource_packs, id) != NULL;
}
