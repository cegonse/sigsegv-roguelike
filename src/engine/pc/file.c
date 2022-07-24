#include <memory.h>
#include <stdio.h>
#include <engine/file.h>

struct file {
  FILE *fd;
};

File *File_Open(char *path)
{
  File *self = calloc(1, sizeof(File));
  self->fd = fopen(path, "rb");

  if (self->fd == NULL) {
    free(self);
    return NULL;
  }

  return self;
}

void File_Close(File *self)
{
  fclose(self->fd);
  free(self);
}

void File_ReadBytes(File *self, size_t bytes, void *out)
{
  fread(out, bytes, 1, self->fd);
}
