#include <cest>

extern "C" {
#include <engine/resource_file.h>
#include <engine/hashmap.h>
}

#include <resource_file_helpers.hpp>

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
