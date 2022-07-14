#include <memory.h>
#include <stdio.h>
#include <engine/file.h>

struct file {
  FILE *fd;
};

File *File_Open(char *path)
{
}

void File_Close(File *self)
{
}

void File_ReadBytes(File *self, size_t bytes, void *out)
{
}
