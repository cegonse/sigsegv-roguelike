#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <raylib/include/raylib.h>
#include <engine/log.h>
#include <engine/input.h>
#include <engine/texture_repository.h>
#include <engine/resource_pack.h>
#include <engine/pc/shader.h>
#include <engine/window.h>

static RenderTexture2D render_texture;
static bool is_fullscreen = false;
static Shader filter_shader;

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
  SetTextureFilter(render_texture.texture, TEXTURE_FILTER_BILINEAR);

  filter_shader = LoadShaderFromMemory(
    Shader_GetScreenFilterVertexShader(),
    Shader_GetScreenFilterFragmentShader()
    );
  int texels_per_pixel_uniform_location = GetShaderLocation(
    filter_shader,
    "texelsPerPixel"
  );
  int texture_size_uniform_location = GetShaderLocation(
    filter_shader,
    "texSize"
  );

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

    float tex_size[2] = {
      settings.width, settings.height
    };

    BeginShaderMode(filter_shader);
    SetShaderValue(filter_shader,
      texels_per_pixel_uniform_location,
      &scale,
      SHADER_UNIFORM_FLOAT
    );
    SetShaderValue(
      filter_shader,
      texture_size_uniform_location,
      tex_size,
      SHADER_UNIFORM_VEC2
    );

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
    EndShaderMode();

    EndDrawing();
  }

  settings.onExit();

  ResourcePack_Destroy();
  TextureRepository_Destroy();
  CloseWindow();
}

void Window_ToggleFullscreen(void)
{
  if (is_fullscreen) {
    RestoreWindow();
  } else {
    MaximizeWindow();
  }

  is_fullscreen = !is_fullscreen;
}
