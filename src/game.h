// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef GAME_H_
#define GAME_H_

#include "./error.h"
#include "./font.h"
#include "./graphics.h"
#include "./level.h"
#include "./menu.h"
#include "./player.h"
#include "./sprite.h"
#include "./state.h"

class Game {
 public:
  Game();
  ~Game();

  State get_state();

  bool level_loop();
  bool main_menu_loop();
  bool credits_menu_loop();
  bool pause_menu_loop();


 private:
  State     _state;
  Graphics* _graphics;
  Level*    _level;
};

#endif  // GAME_H_
