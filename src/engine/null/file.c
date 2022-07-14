#include <memory.h>
#include <engine/file.h>

static void *load_binary_test_data;
static char *load_binary_last_path;


int File_LoadBinary(char *path, size_t bytes, void *out)
{
  load_binary_last_path = path;
  memcpy(out, load_binary_test_data, bytes);
  return 0;
}
