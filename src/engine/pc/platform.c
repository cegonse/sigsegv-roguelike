#include <unistd.h>
#include <stdio.h>
#include <engine/file.h>
#include <engine/platform.h>

static char data_path[kMAX_FILE_PATH];

char *Platform_DataPath(void) {
  char current_path[kMAX_FILE_PATH];
  
  getcwd(current_path, kMAX_FILE_PATH);
  snprintf(data_path, kMAX_FILE_PATH, "%s/resources", current_path);

  return data_path;
}
