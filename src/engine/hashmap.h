#pragma once

#define kHASHMAP_MAX_KEY_LENGTH       128

typedef struct hashmap Hashmap;

Hashmap *Hashmap_Create(void);

void Hashmap_Destroy(Hashmap *self);

int Hashmap_Add(Hashmap *self, char *key, void *value);

void Hashmap_Remove(Hashmap *self, char *key);

void *Hashmap_Get(Hashmap *self, char *key);
