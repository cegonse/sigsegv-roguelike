#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <raylib/include/raylib.h>
#include <engine/log.h>
#include <engine/texture_repository.h>
#include <engine/resource_pack.h>
#include <engine/window.h>

static RenderTexture2D render_texture;

void Drawing_Init(int viewport_width, int viewport_height) {

}

static void logCallback(int logLevel, const char *text, va_list args)
{
  char log[4096];

  vsprintf(log, text, args);
  Log_Info(log);
}

void Window_Open(struct window_settings settings)
{
  SetTraceLogCallback(logCallback);

  InitWindow(settings.width, settings.height, settings.title);
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  SetTargetFPS(
    GetMonitorRefreshRate(GetCurrentMonitor())
  );

  TextureRepository_Init();
  ResourcePack_Init();

  render_texture = LoadRenderTexture(settings.width, settings.height);

  BeginTextureMode(render_texture);
  ClearBackground(RAYWHITE);
  EndTextureMode();

  ResourcePack_Load("default");

  while (!WindowShouldClose()) {
    BeginTextureMode(render_texture);
    settings.onDraw();
    EndTextureMode();

    BeginDrawing();
    DrawTextureRec(
      render_texture.texture,
      (Rectangle) { 0, 0, (float)render_texture.texture.width, (float)-render_texture.texture.height },
      (Vector2) { 0, 0 },
      WHITE
    );
    EndDrawing();
  }

  settings.onExit();

  ResourcePack_Destroy();
  TextureRepository_Destroy();
  CloseWindow();
}
