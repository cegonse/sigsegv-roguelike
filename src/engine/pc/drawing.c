#include <raylib/include/raylib.h>
#include <engine/drawing.h>

static Color toRaylibColor(struct rgba8888_color color)
{
  return (Color){
    color.r, color.g, color.b, color.a
  };
}

void Drawing_ClearScreen(struct rgba8888_color color)
{
  BeginDrawing();
  ClearBackground(toRaylibColor(color));
  EndDrawing();
}
