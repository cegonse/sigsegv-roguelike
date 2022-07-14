#include <stdlib.h>
#pragma once

#define kMAX_FILE_PATH      4096

typedef struct file File;

File *File_Open(char *path);

void File_Close(File *self);

void File_ReadBytes(File *self, size_t bytes, void *out);
