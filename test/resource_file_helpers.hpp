#pragma once
#include <cest>
#include <string>

extern "C" {
#include <engine/resource_file.h>
#include <engine/hashmap.h>
}

static void expectResourcePackTextureToContain(
  struct resource_pack_texture *texture,
  std::string id,
  int width,
  int height,
  ResourceTextureFormat texture_format,
  int data_size
) {
  expect(texture).toBeNotNull();
  expect(texture->width).toEqual(width);
  expect(texture->height).toEqual(height);
  expect(texture->data_size).toEqual(data_size);
  expect(texture->texture_format).toEqual(texture_format);
  std::string packId = std::string(texture->id);
  expect(packId).toEqual(id);
}

static void expectObjectToContainString(
  Hashmap *object,
  std::string key,
  std::string value
) {
  std::string objectString = std::string((char *)Hashmap_Get(
    object,
    (char *)key.c_str()
  ));
  expect(objectString).toEqual(value);
}

static void expectObjectToContainNumber(
  Hashmap *object,
  std::string key,
  float value
) {
  float objectNumber = *((float *)Hashmap_Get(
    object,
    (char *)key.c_str()
  ));
  expect(objectNumber).toEqual(value);
}

static void expectObjectToContainBoolean(
  Hashmap *object,
  std::string key,
  bool value
) {
  bool objectBoolean = *((bool *)Hashmap_Get(
    object,
    (char *)key.c_str()
  ));
  expect(objectBoolean).toEqual(value);
}
