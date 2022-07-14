#pragma once

struct resource_pack_file {
  char *id;
  char *path;
};

struct resource_pack {
  int num_resources;
  struct resource_pack_file **resources;
};

struct resource_pack *ResourceFile_FromPath(char *path);

void ResourceFile_Destroy(struct resource_file *self);
