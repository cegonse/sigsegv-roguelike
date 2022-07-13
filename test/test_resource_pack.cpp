#include <cest>
#include <helpers.hpp>
#include <fake_data.hpp>

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
    FileStub_OnLoadBinary(&test_resource_pack);

    ResourcePack_Load((char *)"test");

    activePacks = ResourcePack_AllActive();
    expect(activePacks).toBeNotNull();

    pack = (struct resource_pack *)List_GetAt(activePacks, 0);
    expect(toString(pack->id)).toEqual("test");
    expect(toString(FileStub_LoadBinary_LastPath())).toEqual("resources/test.pack");
  });

  it("unloads resource packs by id", []() {
    List *activePacks;
    struct resource_pack *pack;
    FileStub_OnLoadBinary(&test_resource_pack);
    ResourcePack_Load((char *)"test");

    ResourcePack_Unload((char *)"test");

    activePacks = ResourcePack_AllActive();
    expect(activePacks).toBeNotNull();
    expect(List_Size(activePacks)).toEqual(0);
  });

  it("contains texture resources", []() {
    List *activePacks;
    struct resource_pack *pack;
    FileStub_OnLoadBinary(&test_resource_pack);

    ResourcePack_Load((char *)"test");

    activePacks = ResourcePack_AllActive();
    pack = (struct resource_pack *)List_GetAt(activePacks, 0);
    expect(toString(pack->id)).toEqual("test");
    expect(toString(pack->textures[0]->id)).toEqual("test");
    expect(toString(pack->textures[0]->path)).toEqual("resources/test.png");
  });
});
