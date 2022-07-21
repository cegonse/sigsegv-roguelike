#include <cest>
#include <helpers.hpp>

extern "C" {
#include <engine/resource_pack.h>
}

describe("Resource packs", []() {
  beforeEach([]() {
    ResourcePack_Init();
  });

  afterEach([]() {
    ResourcePack_Destroy();
  });

  xit("loads a resource pack from file", []() {
    List *activePacks;
    char *packId = (char *)"default";
    struct resource_pack *pack;

    ResourcePack_Load(packId);

    expect(ResourcePack_IsActive(packId)).toBeTruthy();
  });

  xit("unloads resource packs by id", []() {
    List *activePacks;
    struct resource_pack *pack;
    ResourcePack_Load((char *)"test");

    ResourcePack_Unload((char *)"test");
  });

  xit("contains texture resources", []() {
    List *activePacks;
    struct resource_pack *pack;

    ResourcePack_Load((char *)"test");
  });
});
