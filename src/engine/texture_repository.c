#include <stdlib.h>
#include <engine/hashmap.h>
#include <engine/texture_repository.h>

static Hashmap *map;

void TextureRepository_Init(void) {
  map = Hashmap_Create();
}

void TextureRepository_Destroy(void) {
  Hashmap_Destroy(map);
}

void TextureRepository_Add(char *id, struct texture2d *texture) {
  Hashmap_Add(map, id, texture);
}

void TextureRepository_Remove(char *id) {
  Hashmap_Remove(map, id);
}

struct texture2d *TextureRepository_GetById(char *id) {
  return Hashmap_Get(map, id);
}
