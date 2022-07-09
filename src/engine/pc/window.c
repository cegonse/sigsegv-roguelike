#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <raylib/include/raylib.h>
#include <engine/log.h>
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

  while (!WindowShouldClose())
  {
    settings.onDraw();
  }

  settings.onExit();
  CloseWindow();
}
