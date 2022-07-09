#include <stdlib.h>
#include <raylib/include/raylib.h>
#include <engine/window.h>

void Window_Open(struct window_settings settings)
{
  InitWindow(settings.width, settings.width, settings.title);
  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    settings.onDraw();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
  }

  settings.onExit();
  CloseWindow();
}
