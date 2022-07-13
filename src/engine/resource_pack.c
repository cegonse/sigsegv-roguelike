#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <engine/file.h>
#include <engine/list.h>
#include <engine/resource_pack.h>

static List *active_resource_packs;

void ResourcePack_Init(void)
{
  active_resource_packs = List_Create();
}

static void unloadPack(List *list, int index, void *data)
{
  struct resource_pack *pack = data;
  ResourcePack_Unload(pack->id);
}

void ResourcePack_Destroy(void)
{
  List_ForEach(active_resource_packs, unloadPack);
  List_Destroy(active_resource_packs);
}

static void buildPath(char *id, char *path)
{
  sprintf(path, "resources/%s.pack", id);
}

void ResourcePack_Load(char *id)
{
  struct resource_pack *resource_pack;
  char path[kMAX_FILE_PATH];

  resource_pack = calloc(1, sizeof(struct resource_pack));

  buildPath(id, path);
  File_LoadBinary(path, sizeof(struct resource_pack), resource_pack);

  List_Append(active_resource_packs, resource_pack);
}

bool findPackById(void *element, void *user)
{
  struct resource_pack *pack = element;
  char *id = user;

  return strcmp(pack->id, id) == 0;
}

void ResourcePack_Unload(char *id)
{
  struct resource_pack *pack = List_FindFirst(active_resource_packs, id, findPackById);
  List_Remove(active_resource_packs, pack);
  free(pack);
}

List *ResourcePack_AllActive(void)
{
  return active_resource_packs;
}
