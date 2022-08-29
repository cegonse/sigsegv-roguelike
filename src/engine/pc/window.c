#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <raylib/include/raylib.h>
#include <engine/log.h>
#include <engine/texture_repository.h>
#include <engine/resource_pack.h>
#include <engine/window.h>

static RenderTexture2D render_texture;

void Drawing_Init(int viewport_width, int viewport_height) {

}

static void logCallback(int logLevel, const char *text, va_list args) {
  char log[4096];

  vsprintf(log, text, args);
  Log_Info(log);
}

void Window_Open(struct window_settings settings) {
  SetTraceLogCallback(logCallback);

  InitWindow(settings.width, settings.height, settings.title);
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  SetWindowMinSize(settings.width, settings.height);
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
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    float scale = 1.0f;

    if (
      screen_height > settings.height ||
      screen_width > settings.width
    ) {
      scale = fmin(
        (float)screen_height / (float)settings.height,
        (float)screen_width / (float)settings.width
      );
    }

    BeginTextureMode(render_texture);
    settings.onDraw();
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);
    DrawTextureEx(
      render_texture.texture,
      (Vector2) {
        screen_width*0.5f - (settings.width * scale * 0.5f),
        screen_height*0.5f - (settings.height * scale * 0.5f)
      },
      0.0f,
      scale,
      RAYWHITE
    );
    EndDrawing();
  }

  settings.onExit();

  ResourcePack_Destroy();
  TextureRepository_Destroy();
  CloseWindow();
}
