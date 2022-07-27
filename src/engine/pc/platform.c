#include <unistd.h>
#include <engine/file.h>
#include <engine/platform.h>

static char data_path[kMAX_FILE_PATH];

char *Platform_DataPath(void) {
  getcwd(data_path, kMAX_FILE_PATH);
  return data_path;
}
