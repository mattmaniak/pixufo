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
      case kCreditsMenu:
        if (!Game_instance.RunCreditsMenuLoop()) {
          return -1;
        }
        break;

      case kLevel:
        if (!Game_instance.RunLevelLoop()) {
          return -1;
        }
        break;

      case kMainMenu:
        if (!Game_instance.RunMainMenuLoop()) {
          return -1;
        }
        break;

      case kPauseMenu:
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
