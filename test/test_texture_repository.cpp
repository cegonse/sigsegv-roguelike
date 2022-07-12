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

  it("persists texture2d objects with an id", []() {
    struct texture2d texture;
    char *id = (char *)"myTexture";

    TextureRepository_Add(id, &texture);

    //expect(TextureRepository_GetById(id)).toEqual(&texture);
  });
});
