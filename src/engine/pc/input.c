#include <raylib/include/raylib.h>
#include <engine/input.h>

static int keycode_to_raylib[kKEYCODE_MAX] = {
  [kKEYCODE_A] = KEY_A,
  [kKEYCODE_B] = KEY_B,
  [kKEYCODE_C] = KEY_C,
  [kKEYCODE_D] = KEY_D,
  [kKEYCODE_E] = KEY_E,
  [kKEYCODE_F] = KEY_F,
  [kKEYCODE_G] = KEY_G,
  [kKEYCODE_H] = KEY_H,
  [kKEYCODE_I] = KEY_I,
  [kKEYCODE_J] = KEY_J,
  [kKEYCODE_K] = KEY_K,
  [kKEYCODE_L] = KEY_L,
  [kKEYCODE_M] = KEY_M,
  [kKEYCODE_N] = KEY_N,
  [kKEYCODE_O] = KEY_O,
  [kKEYCODE_P] = KEY_P,
  [kKEYCODE_Q] = KEY_Q,
  [kKEYCODE_R] = KEY_R,
  [kKEYCODE_S] = KEY_S,
  [kKEYCODE_T] = KEY_T,
  [kKEYCODE_U] = KEY_U,
  [kKEYCODE_V] = KEY_V,
  [kKEYCODE_W] = KEY_W,
  [kKEYCODE_X] = KEY_X,
  [kKEYCODE_Y] = KEY_Y,
  [kKEYCODE_Z] = KEY_Z,
  [kKEYCODE_F1] = KEY_F1,
  [kKEYCODE_F2] = KEY_F2,
  [kKEYCODE_F3] = KEY_F3,
  [kKEYCODE_F4] = KEY_F4,
  [kKEYCODE_F5] = KEY_F5,
  [kKEYCODE_F6] = KEY_F6,
  [kKEYCODE_F7] = KEY_F7,
  [kKEYCODE_F8] = KEY_F8,
  [kKEYCODE_F9] = KEY_F9,
  [kKEYCODE_F10] = KEY_F10,
  [kKEYCODE_F11] = KEY_F11,
  [kKEYCODE_F12] = KEY_F12,
  [kKEYCODE_0] = KEY_ZERO,
  [kKEYCODE_1] = KEY_ONE,
  [kKEYCODE_2] = KEY_TWO,
  [kKEYCODE_3] = KEY_THREE,
  [kKEYCODE_4] = KEY_FOUR,
  [kKEYCODE_5] = KEY_FIVE,
  [kKEYCODE_6] = KEY_SIX,
  [kKEYCODE_7] = KEY_SEVEN,
  [kKEYCODE_8] = KEY_EIGHT,
  [kKEYCODE_9] = KEY_NINE,
  [kKEYCODE_ARROW_LEFT] = KEY_LEFT,
  [kKEYCODE_ARROW_RIGHT] = KEY_RIGHT,
  [kKEYCODE_ARROW_UP] = KEY_UP,
  [kKEYCODE_ARROW_DOWN] = KEY_DOWN,
  [kKEYCODE_TAB] = KEY_TAB
};

bool Input_GetKeyDown(KeyCode keycode) {
  return IsKeyPressed(keycode_to_raylib[keycode]);
}

bool Input_GetKeyUp(KeyCode keycode) {
  return IsKeyReleased(keycode_to_raylib[keycode]);
}

bool Input_GetKey(KeyCode keycode) {
  return IsKeyDown(keycode_to_raylib[keycode]);
}
