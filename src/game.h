// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include <limits>

#include "error.h"
#include "font.h"
#include "graphics.h"
#include "level.h"
#include "menu.h"
#include "player.h"
#include "sprite.h"
#include "state.h"

class Game {
 public:
  Game();
  ~Game();

  bool RunCreditsMenuLoop();
  bool RunLevelLoop();
  bool RunMainMenuLoop();
  bool RunPauseMenuLoop();

  State get_state_();

 private:
  Graphics* graphics_;
  Level*    level_;
  State     state_;
};

#endif  // SRC_GAME_H_
