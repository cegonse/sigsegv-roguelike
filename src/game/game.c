#include <engine/window.h>
#include <engine/drawing.h>
#include <engine/input.h>
#include <game/game.h>

static struct vec3 camera_position = { .x = 3.0f, .y = 3.0f, .z = 3.0f};
static struct vec3 camera_target = { .x = 0.0f, .y = 0.0f, .z = 0.0f};

void Game_DrawGui(void) {
  Drawing_DrawTexture("tileset", 0, 0);
}

void Game_Draw3d(float delta_time) {
  if (Input_GetKeyDown(kKEYCODE_F2)) {
    Window_ToggleFullscreen();
  }

  Drawing_ClearScreen((struct rgba8888_color){ 255, 255, 255, 255 });

  Drawing_SetCameraOrtho(camera_position, camera_target, 4.0f);
  camera_position.x += delta_time;
  camera_target.x += delta_time;
  camera_position.z += delta_time;
  camera_target.z += delta_time;

  Drawing_DrawPlane((struct vec3){ 0.0f, 0.0f, 0.0f });
}

void Game_Exit(void) {
}


void Game_Run(void) {
  Window_Open((struct window_settings){
    .width = 320,
    .height = 240,
    .title = "Roguelike",
    .onDrawGui = Game_DrawGui,
    .onDraw3d = Game_Draw3d,
    .onExit = Game_Exit
  });
}
