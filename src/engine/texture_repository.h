#pragma once
#include <engine/drawing.h>

void TextureRepository_Init(void);

void TextureRepository_Destroy(void);

void TextureRepository_Add(char *id, struct texture2d *texture);

void TextureRepository_Remove(char *id);

struct texture2d *TextureRepository_GetById(char *id);
