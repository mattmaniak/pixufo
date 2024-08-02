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
        if (!Game_instance.RunLevelLoop()) {
          return -1;
        }
        break;

      case main_menu:
        if (!Game_instance.RunMainMenuLoop()) {
          return -1;
        }
        break;

      case credits_menu:
        if (!Game_instance.RunCreditsMenuLoop()) {
          return -1;
        }
        break;

      case pause_menu:
        if (!Game_instance.RunPauseMenuLoop()) {
          return -1;
        }
      }
    }
  } catch (std::runtime_error) {
    return -1;
  }
  return 0;
}
