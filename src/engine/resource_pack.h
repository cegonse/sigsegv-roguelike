#pragma once
#include <engine/list.h>

void ResourcePack_Init(void);

void ResourcePack_Destroy(void);

void ResourcePack_Load(char *id);

void ResourcePack_Unload(char *id);

List *ResourcePack_AllActive(void);
