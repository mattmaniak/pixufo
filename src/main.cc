// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "main.h"

// Very ugly SDL2 error fix for "undefined reference to WinMain".
#ifdef main
#undef main
#endif

int main() {
  try {
    Game Game_instance;

    for (;;) {
      switch (Game_instance.get_state()) {
      case level:
        if (!Game_instance.level_loop()) {
          return -1;
        }
        break;

      case main_menu:
        if (!Game_instance.main_menu_loop()) {
          return -1;
        }
        break;

      case credits_menu:
        if (!Game_instance.credits_menu_loop()) {
          return -1;
        }
        break;

      case pause_menu:
        if (!Game_instance.pause_menu_loop()) {
          return -1;
        }
      }
    }
  } catch (std::runtime_error) {
    return -1;
  }
  return 0;
}
