#include <stdlib.h>
#include <stdio.h>
#include <engine/file.h>
#include <engine/resource_file.h>

struct resource_pack *ResourceFile_FromPath(char *path)
{
  char magic[8];
  struct resource_pack *resource_pack = calloc(1, sizeof(struct resource_pack));
  File *file = File_Open(path);

  File_ReadBytes(file, 7, magic);
  magic[7] = 0;
  printf("%s\n", magic);

  File_Close(file);

  return resource_pack;
}

void ResourceFile_Destroy(struct resource_pack *self)
{
  free(self);
}
