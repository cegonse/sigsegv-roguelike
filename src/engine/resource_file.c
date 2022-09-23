#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <engine/file.h>
#include <engine/log.h>
#include <engine/resource_file.h>

#define kMAGIC_SIZE     7

typedef enum {
  kRESOURCE_OBJECT_TYPE_STRING = 0x01,
  kRESOURCE_OBJECT_TYPE_NUMBER = 0x02,
  kRESOURCE_OBJECT_TYPE_BOOLEAN = 0x03,
  kRESOURCE_OBJECT_TYPE_OBJECT = 0x04,
  kRESOURCE_OBJECT_TYPE_ARRAY = 0x05,
} ResourceObjectType;

typedef union {
  float f;
  uint32_t ul;
} ResourcePackFloat;

static bool verifyMagic(File *file) {
  char magic[kMAGIC_SIZE+1];
  
  File_ReadBytes(file, kMAGIC_SIZE, magic);
  magic[kMAGIC_SIZE] = '\0';

  return strcmp("SIGSEGV", magic) == 0;
}

static uint8_t *readFullPack(File *file) {
  uint8_t *full_pack = NULL;
  uint32_t size = 0;
  
  File_ReadBytes(file, sizeof(uint32_t), &size);
  full_pack = calloc(size, sizeof(uint8_t));
  File_ReadBytes(file, size, full_pack);

  return full_pack;
}

static void parseTextures(uint8_t *full_pack, struct resource_pack *resource_pack) {
  size_t offset = 0;
  uint32_t texture_id_length = 0;
  char *texture_id = NULL;
  uint8_t texture_format = 0;
  uint32_t texture_width = 0;
  uint32_t texture_height = 0;
  uint32_t texture_data_size = 0;
  uint8_t *texture_data = NULL;

  resource_pack->textures = calloc(
    resource_pack->num_textures,
    sizeof(struct resource_pack_texture *)
  );

  for (int i=0; i<resource_pack->num_textures; ++i) {
    resource_pack->textures[i] = calloc(1, sizeof(struct resource_pack_texture));

    memcpy(&texture_id_length, full_pack + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    texture_id = (char *)(full_pack + offset);
    offset += texture_id_length;

    memcpy(&texture_format, full_pack + offset, sizeof(uint8_t));
    offset += sizeof(uint8_t);

    memcpy(&texture_width, full_pack + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    memcpy(&texture_height, full_pack + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    memcpy(&texture_data_size, full_pack + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    texture_data = full_pack + offset;
    offset += texture_data_size;

    resource_pack->textures[i]->id = calloc(texture_id_length + 1, sizeof(char));
    memcpy(resource_pack->textures[i]->id, texture_id, texture_id_length);

    resource_pack->textures[i]->texture_format = texture_format;
    resource_pack->textures[i]->width = texture_width;
    resource_pack->textures[i]->height = texture_height;
    resource_pack->textures[i]->data_size = texture_data_size;
    resource_pack->textures[i]->data = calloc(texture_data_size, sizeof(uint8_t));
    memcpy(resource_pack->textures[i]->data, texture_data, texture_data_size);
  }
}

static void parseObjects(uint8_t *full_pack, struct resource_pack *resource_pack) {
  uint32_t num_entries = 0;
  uint32_t entry_type = 0;
  uint32_t key_length = 0;
  char *key = NULL;
  
  resource_pack->objects = calloc(
    resource_pack->num_objects,
    sizeof(Hashmap *)
  );

  for (int i=0; i<resource_pack->num_objects; ++i) {
    resource_pack->objects[i] = Hashmap_Create();

    num_entries = *((uint32_t *)full_pack);
    full_pack += 2 * sizeof(uint32_t);

    for (int j=0; j<num_entries; ++j) {
      entry_type = *((uint32_t *)full_pack);
      full_pack += sizeof(uint32_t);

      key_length = *((uint32_t *)full_pack);
      full_pack += sizeof(uint32_t);

      key = calloc(key_length + 1, sizeof(char));
      memcpy(key, full_pack, key_length);
      full_pack += key_length;

      if (entry_type == kRESOURCE_OBJECT_TYPE_STRING) {
        char *string_value = NULL;
        uint32_t string_value_length = 0;

        string_value_length = *((uint32_t *)full_pack);
        full_pack += sizeof(uint32_t);

        string_value = calloc(string_value_length + 1, sizeof(char));
        memcpy(string_value, full_pack, string_value_length);
        full_pack += string_value_length;

        Hashmap_Add(resource_pack->objects[i], key, string_value);
      } else if (entry_type == kRESOURCE_OBJECT_TYPE_NUMBER) {
        ResourcePackFloat *number_value = calloc(1, sizeof(ResourcePackFloat));

        number_value->ul = *((uint32_t *)full_pack);
        full_pack += sizeof(uint32_t);

        Hashmap_Add(resource_pack->objects[i], key, number_value);
      } else if (entry_type == kRESOURCE_OBJECT_TYPE_BOOLEAN) {
        bool *boolean_value = calloc(1, sizeof(bool));
        uint8_t integer_boolean = 0;

        integer_boolean = *((uint8_t *)full_pack);
        *boolean_value = (bool)integer_boolean;
        full_pack += sizeof(uint8_t);

        Hashmap_Add(resource_pack->objects[i], key, boolean_value);
      }
    }
  }
}

struct resource_pack *ResourceFile_FromPath(char *path) {
  struct resource_pack *resource_pack = calloc(1, sizeof(struct resource_pack));
  uint32_t texture_chunk_size = 0, object_chunk_size = 0;
  File *file = File_Open(path);
  uint8_t *full_pack = NULL, *pack = NULL;

  if (file == NULL) {
    free(resource_pack);
    Log_Error("Failed to load resource pack %s", path);
    return NULL;
  }

  if (!verifyMagic(file)) {
    free(resource_pack);
    return NULL;
  }

  full_pack = readFullPack(file);
  pack = full_pack;
  
  resource_pack->num_textures = *((uint32_t *)pack);
  pack += sizeof(uint32_t);
  
  resource_pack->num_objects = *((uint32_t *)(pack));
  pack += sizeof(uint32_t);
  
  texture_chunk_size = *((uint32_t *)(pack));
  pack += sizeof(uint32_t);

  object_chunk_size = *((uint32_t *)(pack));
  pack += sizeof(uint32_t);

  parseTextures(pack, resource_pack);
  pack += texture_chunk_size;
  parseObjects(pack, resource_pack);

  Log_Info(
    "Loaded resource pack %s (textures=%d,objects=%d)",
    path,
    resource_pack->num_textures,
    resource_pack->num_objects
  );

  free(full_pack);
  File_Close(file);

  return resource_pack;
}

void ResourceFile_Destroy(struct resource_pack *self) {
  for (int i=0; i<self->num_textures; ++i) {
    free(self->textures[i]->data);
    free(self->textures[i]);
  }

  free(self->textures);
  free(self);
}
