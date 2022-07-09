#pragma once

struct window_settings {
  int width;
  int height;
};

typedef struct window Window;

Window *Window_Open(struct window_settings settings);

void Window_Close(Window *self);
