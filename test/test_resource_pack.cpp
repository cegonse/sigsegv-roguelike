#include <cest>
#include <helpers.hpp>

extern "C" {
#include <engine/resource_pack.h>
#include <engine/texture_repository.h>
}

describe("Resource packs", []() {
  beforeEach([]() {
    ResourcePack_Init();
    TextureRepository_Init();
  });

  afterEach([]() {
    ResourcePack_Destroy();
    TextureRepository_Destroy();
  });

  it("loads a resource pack from file", []() {
    char *packId = (char *)"sample";

    ResourcePack_Load(packId);

    expect(ResourcePack_IsActive(packId)).toBeTruthy();

    struct texture2d *texture = TextureRepository_GetById((char *)"first");
    expect(texture).toBeNotNull();
    expect(texture->height).toEqual(4);
    expect(texture->width).toEqual(4);
    expect(texture->color_format).toEqual(kTEXTURE_COLOR_FORMAT_RGBA32);
  });

  it("unloads resource packs by id", []() {
    char *packId = (char *)"sample";
    ResourcePack_Load((char *)"sample");

    ResourcePack_Unload((char *)"sample");

    expect(ResourcePack_IsActive(packId)).toBeFalsy();
    struct texture2d *texture = TextureRepository_GetById((char *)"first");
    expect(texture).toBeNull();
  });
});
