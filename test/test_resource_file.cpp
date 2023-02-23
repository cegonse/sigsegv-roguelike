#include <cest>

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

describe("Resource file", []() {
  it("can be loaded from a path", []() {
    struct resource_pack *resource_pack;
    char *path = (char *)"test/fake_data/sample.pack";

    resource_pack = ResourceFile_FromPath(path);

    expect(resource_pack).toBeNotNull();
    expect(resource_pack->num_textures).toEqual(2);
    expect(resource_pack->num_objects).toEqual(1);
    expect(resource_pack->textures).toBeNotNull();

    expectResourcePackTextureToContain(
      resource_pack->textures[0],
      "first", 4, 4, kRESOURCE_TEXTURE_FORMAT_RGBA32, 64
    );
    expectResourcePackTextureToContain(
      resource_pack->textures[1],
      "second", 4, 4, kRESOURCE_TEXTURE_FORMAT_RGB24, 48
    );

    expect(resource_pack->objects).toBeNotNull();
    Hashmap *object = (Hashmap *)Hashmap_Get(resource_pack->objects, (char *)"sample");

    expectObjectToContainString(object, "string", "world");
    expectObjectToContainNumber(object, "number", 1.0f);
    expectObjectToContainBoolean(object, "boolean", false);

    ResourceFile_Destroy(resource_pack);
  });
});
