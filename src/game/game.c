#include <engine/window.h>
#include <game/game.h>

void Game_Draw(void)
{
}

void Game_Exit(void)
{
}


void Game_Run(void)
{
  Window_Open((struct window_settings){
    width: 800,
    height: 600,
    onDraw: Game_Draw,
    onExit: Game_Exit
  });
}
