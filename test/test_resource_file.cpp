#include <cest>

extern "C" {
#include <engine/resource_file.h>
}

describe("Resource file", []() {
  it("can be loaded from a path", []() {
    struct resource_pack *resource_pack;
    char *path = (char *)"test/fake_data/default.pack";

    resource_pack = ResourceFile_FromPath(path);

    expect(resource_pack->num_resources).toEqual(1);
  });
});
