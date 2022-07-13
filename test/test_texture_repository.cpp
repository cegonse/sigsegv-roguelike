#include <cest>

extern "C" {
#include <engine/texture_repository.h>
}

describe("Texture repository", []() {
  beforeEach([]() {
    TextureRepository_Init();
  });

  afterEach([]() {
    TextureRepository_Destroy();
  });

  it("persists texture2d with an id", []() {
    struct texture2d texture;
    char *id = (char *)"myTexture";

    TextureRepository_Add(id, &texture);

    expect(TextureRepository_GetById(id)).toEqual(&texture);
  });

  it("removes texture2d by id", []() {
    struct texture2d texture;
    char *id = (char *)"myTexture";
    TextureRepository_Add(id, &texture);

    TextureRepository_Remove(id);

    expect(TextureRepository_GetById(id)).toBeNull();
  });
});
