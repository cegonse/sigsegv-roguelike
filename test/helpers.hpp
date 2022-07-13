#pragma once
#include <string>

extern "C" {
  void FileStub_OnLoadBinary(void *data);
  char *FileStub_LoadBinary_LastPath(void);
}

std::string toString(char *str)
{
  return std::string(str);
}
