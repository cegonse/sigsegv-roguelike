#pragma once
#include <stdbool.h>
#include <engine/list.h>

void ResourcePack_Init(void);

void ResourcePack_Destroy(void);

void ResourcePack_Load(char *id);

void ResourcePack_Unload(char *id);

bool ResourcePack_IsActive(char *id);
