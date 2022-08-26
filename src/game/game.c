#include <engine/window.h>
#include <engine/drawing.h>
#include <game/game.h>

void Game_Draw(void)
{
  Drawing_DrawTexture("wall", 100, 100);

  Drawing_ClearScreen((struct rgba8888_color){
    r: 255,
    g: 255,
    b: 255,
    a: 255
  });
}

void Game_Exit(void)
{
}


void Game_Run(void)
{
  Window_Open((struct window_settings){
    width: 800,
    height: 600,
    title: "Roguelike",
    onDraw: Game_Draw,
    onExit: Game_Exit
  });
}
