#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <raylib/include/raylib.h>
#include <engine/log.h>
#include <engine/texture_repository.h>
#include <engine/resource_pack.h>
#include <engine/window.h>

static void logCallback(int logLevel, const char *text, va_list args)
{
  char log[4096];

  vsprintf(log, text, args);
  Log_Info(log);
}

void Window_Open(struct window_settings settings)
{
  SetTraceLogCallback(logCallback);

  InitWindow(settings.width, settings.width, settings.title);
  SetTargetFPS(60);

  TextureRepository_Init();
  ResourcePack_Init();

  ResourcePack_Load("default");

  while (!WindowShouldClose())
  {
    settings.onDraw();
  }

  settings.onExit();
  ResourcePack_Destroy();
  TextureRepository_Destroy();
  CloseWindow();
}
