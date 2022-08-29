#include <engine/window.h>
#include <engine/drawing.h>
#include <game/game.h>

void Game_Draw(void) {
  Drawing_DrawTexture("wall", 0, 0);
  Drawing_DrawTexture("wall", 320-64, 0);
  Drawing_DrawTexture("wall", 0, 240-64);
  Drawing_DrawTexture("wall", 320-64, 240-64);

  Drawing_ClearScreen((struct rgba8888_color){
    r: 255,
    g: 255,
    b: 255,
    a: 255
  });
}

void Game_Exit(void) {
}


void Game_Run(void) {
  Window_Open((struct window_settings){
    width: 320,
    height: 240,
    title: "Roguelike",
    onDraw: Game_Draw,
    onExit: Game_Exit
  });
}
