// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "main.h"

// Very ugly SDL2 error fix for "undefined reference to WinMain".
#ifdef main
#undef main
#endif

int main() {
  try {
    Game game_instance;

    for (;;) {
      switch (game_instance.get_state_()) {
      case kCreditsMenu:
        if (!game_instance.RunCreditsMenuLoop()) {
          return -1;
        }
        break;

      case kLevel:
        if (!game_instance.RunLevelLoop()) {
          return -1;
        }
        break;

      case kMainMenu:
        if (!game_instance.RunMainMenuLoop()) {
          return -1;
        }
        break;

      case kPauseMenu:
        if (!game_instance.RunPauseMenuLoop()) {
          return -1;
        }
      }
    }
  } catch (std::runtime_error) {
    return -1;
  }
  return 0;
}
