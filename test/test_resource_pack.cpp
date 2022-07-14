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

  it("loads a resource pack from file", []() {
    List *activePacks;
    struct resource_pack *pack;

    ResourcePack_Load((char *)"test");

    activePacks = ResourcePack_AllActive();
    expect(activePacks).toBeNotNull();
  });

  it("unloads resource packs by id", []() {
    List *activePacks;
    struct resource_pack *pack;
    ResourcePack_Load((char *)"test");

    ResourcePack_Unload((char *)"test");

    activePacks = ResourcePack_AllActive();
    expect(activePacks).toBeNotNull();
    expect(List_Size(activePacks)).toEqual(0);
  });

  it("contains texture resources", []() {
    List *activePacks;
    struct resource_pack *pack;

    ResourcePack_Load((char *)"test");

    activePacks = ResourcePack_AllActive();
    expect(activePacks).toBeNotNull();
    expect(List_Size(activePacks)).toEqual(1);
  });
});
