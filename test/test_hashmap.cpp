#include <cest>

extern "C" {
#include <engine/hashmap.h>
}

Hashmap *map;

static char *aLongKey(void);

describe("Hash map", []() {
  beforeEach([]() {
    map = Hashmap_Create();
  });

  afterEach([]() {
    Hashmap_Destroy(map);
  });

  it("can have objects added using strings as keys", []() {
    char *key = (char *)"hello";
    int value = 100;

    Hashmap_Add(map, key, &value);

    int hashedValue = *((int *)Hashmap_Get(map, key));
    expect(hashedValue).toEqual(value);
  });

  it("can't add objects with a key longer than kHASHMAP_MAX_KEY_LENGTH", []() {
    char *key = aLongKey();
    int value = 100;

    auto result = Hashmap_Add(map, key, &value);

    expect(result).toEqual(-1);
    expect(Hashmap_Get(map, key)).toBeNull();
  });

  it("can have objects removed by key", []() {
    char *key = (char *)"hello";
    int value = 100;
    Hashmap_Add(map, key, &value);

    Hashmap_Remove(map, key);

    expect(Hashmap_Get(map, key)).toBeNull();
  });

  it("has no effect when removing non existing keys", []() {
    char *key = (char *)"hello";

    Hashmap_Remove(map, key);

    expect(Hashmap_Get(map, key)).toBeNull();
  });
});

static char *aLongKey(void)
{
  char *key = new char[1, kHASHMAP_MAX_KEY_LENGTH + 100];

  for (int i=0; i<(kHASHMAP_MAX_KEY_LENGTH + 100)-1; ++i) {
    key[i] = 'x';
  }

  return key;
}
