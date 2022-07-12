#include <stdlib.h>
#include <string.h>
#include <uthash/include/uthash.h>
#include <engine/hashmap.h>

struct hash_key {
    char key[kHASHMAP_MAX_KEY_LENGTH];
    void *value;
    UT_hash_handle hh;
};

struct hashmap {
  struct hash_key *map;
};

Hashmap *Hashmap_Create(void)
{
  return calloc(1, sizeof(Hashmap));
}

void Hashmap_Destroy(Hashmap *self)
{
  free(self);
}

int Hashmap_Add(Hashmap *self, char *key, void *value)
{
  if (strlen(key) >= kHASHMAP_MAX_KEY_LENGTH) {
    return -1;
  }

  struct hash_key *e = calloc(1, sizeof(struct hash_key));
  strcpy(e->key, key);
  e->value = value;

  HASH_ADD_STR(self->map, key, e);

  return 0;
}

void *Hashmap_Get(Hashmap *self, char *key)
{
  struct hash_key *e = NULL;
  HASH_FIND_STR(self->map, key, e);

  if (e == NULL) return NULL;
  return e->value;
}

void Hashmap_Remove(Hashmap *self, char *key)
{
  struct hash_key *e = NULL;
  
  HASH_FIND_STR(self->map, key, e);
  if (e == NULL) return;

  HASH_DEL(self->map, e);
}
