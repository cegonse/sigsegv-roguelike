#pragma once

struct window_settings {
  int width;
  int height;
  char *title;

  void (*onDraw)(void);
  void (*onExit)(void);
};

typedef struct window Window;

void Window_Open(struct window_settings settings);
