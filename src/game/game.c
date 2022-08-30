#include <engine/window.h>
#include <engine/drawing.h>
#include <engine/input.h>
#include <game/game.h>

int x=0, y=0;

void Game_Draw(void) {
  if (Input_GetKeyDown(kKEYCODE_F2)) {
    Window_ToggleFullscreen();
  }

  if (Input_GetKey(kKEYCODE_ARROW_DOWN)) {
    y--;
  }
  if (Input_GetKey(kKEYCODE_ARROW_UP)) {
    y++;
  }
  if (Input_GetKey(kKEYCODE_ARROW_LEFT)) {
    x--;
  }
  if (Input_GetKey(kKEYCODE_ARROW_RIGHT)) {
    x++;
  }

  Drawing_DrawTexture("wall", 0, 0);
  Drawing_DrawTexture("wall", 320-64, 0);
  Drawing_DrawTexture("wall", 0, 240-64);
  Drawing_DrawTexture("wall", 320-64, 240-64);

  Drawing_DrawTexture("wall", x, y);

  Drawing_ClearScreen((struct rgba8888_color){
    .r = 255,
    .g = 255,
    .b = 255,
    .a = 255
  });
}

void Game_Exit(void) {
}


void Game_Run(void) {
  Window_Open((struct window_settings){
    .width = 320,
    .height = 240,
    .title = "Roguelike",
    .onDraw = Game_Draw,
    .onExit = Game_Exit
  });
}
