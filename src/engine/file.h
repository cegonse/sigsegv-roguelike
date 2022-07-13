#include <stdlib.h>
#pragma once

#define kMAX_FILE_PATH      4096

int File_LoadBinary(char *path, size_t bytes, void *out);
