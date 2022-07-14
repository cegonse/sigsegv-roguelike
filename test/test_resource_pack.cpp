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
    struct resource_pack *pack;

    ResourcePack_Load((char *)"test");

    activePacks = ResourcePack_AllActive();
    expect(activePacks).toBeNotNull();
  });

  xit("unloads resource packs by id", []() {
    List *activePacks;
    struct resource_pack *pack;
    ResourcePack_Load((char *)"test");

    ResourcePack_Unload((char *)"test");

    activePacks = ResourcePack_AllActive();
    expect(activePacks).toBeNotNull();
    expect(List_Size(activePacks)).toEqual(0);
  });

  xit("contains texture resources", []() {
    List *activePacks;
    struct resource_pack *pack;

    ResourcePack_Load((char *)"test");

    activePacks = ResourcePack_AllActive();
    expect(activePacks).toBeNotNull();
    expect(List_Size(activePacks)).toEqual(1);
  });
});
