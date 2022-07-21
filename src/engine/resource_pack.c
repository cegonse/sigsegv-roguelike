#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <engine/file.h>
#include <engine/hashmap.h>
#include <engine/resource_file.h>

static Hashmap *active_resource_packs;

void ResourcePack_Init(void)
{
  active_resource_packs = Hashmap_Create();
}

void ResourcePack_Destroy(void)
{
  Hashmap_Destroy(active_resource_packs);
}

static void buildPath(char *id, char *path)
{
  sprintf(path, "resources/%s.pack", id);
}

void ResourcePack_Load(char *id)
{
  struct resource_pack *resource_pack;
  char path[kMAX_FILE_PATH];

  buildPath(id, path);

  Hashmap_Add(active_resource_packs, id, resource_pack);
}

void ResourcePack_Unload(char *id)
{
}

bool ResourcePack_IsActive(char *id)
{
  return Hashmap_Get(active_resource_packs, id) != NULL;
}
