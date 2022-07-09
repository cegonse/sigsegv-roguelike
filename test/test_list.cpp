#include <cest>

extern "C"
{
#include <engine/list.h>
}

static List *list;
static std::vector<int> items;

static void forEachIterator(List *self, int index, void *data)
{
  int element = *(int *)data;
  items.push_back(element);
}

static bool sortInts(void *pa, void *pb)
{
  int a = *(int *)pa;
  int b = *(int *)pb;

  return a < b;
}

describe("Lists", []() {
  beforeEach([]() {
    list = List_Create();
  });

  afterEach([]() {
    List_Destroy(list);
  });

  it("can have elements appended", []() {
    int first = 1, second = 2;

    List_Append(list, &first);
    List_Append(list, &second);

    expect(List_Size(list)).toEqual(2);
    expect(List_GetAt(list, 0)).toEqual(&first);
    expect(List_GetAt(list, 1)).toEqual(&second);
  });

  it("can have elements prepended", []() {
    int first = 1, second = 2;

    List_Append(list, &first);
    List_Prepend(list, &second);

    expect(List_Size(list)).toEqual(2);
    expect(List_GetAt(list, 0)).toEqual(&second);
    expect(List_GetAt(list, 1)).toEqual(&first);
  });

  it("can have elements removed", []() {
    int first = 1, second = 2, third = 3;

    List_Append(list, &first);
    List_Append(list, &second);
    List_Append(list, &third);

    List_Remove(list, &second);

    expect(List_Size(list)).toEqual(2);
    expect(List_GetAt(list, 0)).toEqual(&first);
    expect(List_GetAt(list, 1)).toEqual(&third);
  });

  it("supports iterating over elements", []() {
    int first = 1, second = 2, third = 3;

    List_Append(list, &first);
    List_Append(list, &second);
    List_Append(list, &third);

    List_ForEach(list, forEachIterator);

    expect(items).toContain(1);
    expect(items).toContain(2);
    expect(items).toContain(3);
  });

  it("supports sorting its elements", []() {
    const auto sortIntsCb = [](void *pa, void *pb) {
      int a = *(int *)pa;
      int b = *(int *)pb;

      return a < b;
    };
    int first = 1, second = 2, third = 3, fourth = 4;

    List_Append(list, &third);
    List_Append(list, &first);
    List_Append(list, &second);
    List_Append(list, &fourth);

    List_Sort(list, sortInts);

    expect(List_GetAt(list, 0)).toEqual(&first);
    expect(List_GetAt(list, 1)).toEqual(&second);
    expect(List_GetAt(list, 2)).toEqual(&third);
    expect(List_GetAt(list, 3)).toEqual(&fourth);
  });
});
