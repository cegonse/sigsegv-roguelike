#pragma once

struct window_settings {
  int width;
  int height;
  char *title;

  void (*onDrawGui)(void);
  void (*onDraw3d)(float delta_time);
  void (*onExit)(void);
};

typedef struct window Window;

void Window_Open(struct window_settings settings);

void Window_ToggleFullscreen(void);
